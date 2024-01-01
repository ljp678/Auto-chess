// Fill out your copyright notice in the Description page of Project Settings.


#include "ClothoPlayerController.h"

#include "ClothoGameMode.h"
#include "ClothoGameState.h"
#include "ClothoPlayerState.h"
#include "NavigationSystem.h"
#include "Actor/CameraDirector.h"
#include "Actor/GridEffectActor.h"
#include "Actor/MouseClickActor.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "Components/CapsuleComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Manager/PieceInfoManager.h"
#include "Pawn/PawnBase.h"
#include "Player/DragonCharacter.h"
#include "Util/ClothoFunctionLibrary.h"
#include "Widget/Main/MapWidget.h"
#include "Widget/Main/PieceInfoWidget.h"
#include "Widget/Main/ShopWidget.h"


AClothoPlayerController::AClothoPlayerController()
{
	bShowMouseCursor = true;// 显示鼠标光标
	bEnableClickEvents = true;// 启用鼠标点击事件
	bEnableMouseOverEvents = true;// 启用鼠标悬停事件
	bAutoManageActiveCameraTarget = false;// 不自动管理激活的摄像机目标

	bHaveSpawnedActor = false;// 用于控制是否生成了Actor
}
// 被踢下线时的实现
void AClothoPlayerController::ClientWasKicked_Implementation(const FText& KickReason)
{
}
// 设置商店UI棋子的可见性
void AClothoPlayerController::SetShopUIPieceVisible_Implementation(ESlateVisibility SlateVisibility)
{
	UShopWidget* ShopWidget = UClothoFunctionLibrary::GetShopWidget(this);
	ShopWidget->SetPiecesVisibility(SlateVisibility);
}
// 检查是否有焦点棋子
bool AClothoPlayerController::ControllerHasFocusPiece() const
{
	return FocusPiece != nullptr;
}
// 生成环境棋子
void AClothoPlayerController::SpawnEnvironmentPieces(FPieceCoor PieceCoor)
{
	// 获取当前玩家的角色和游戏状态
	ADragonCharacter* DragonCharacter = Cast<ADragonCharacter>(GetPawn());
	AClothoGameState* ClothoGameState = Cast<AClothoGameState>(UGameplayStatics::GetGameState(this));
	// 计算旋转角度
	float Yaw = UClothoFunctionLibrary::GetYawByBoardIndex(DragonCharacter->GetPlayerIndex());

	// 在游戏中生成并放置环境棋子
	FPieceCoor* PieceCoorPtr = &PieceCoor;
	while (PieceCoorPtr)
	{
		FVector Location = DragonCharacter->GetGridLocationByReverseIndex(PieceCoorPtr->Coordinate);
		APawnBase* Piece = ClothoGameState->GetFreePieceByIndex(PieceCoorPtr->PieceIndex);
		Piece->SetActorLocation(Location);
		Piece->SetActorRotation(FRotator(0, Yaw + 180, 0));
		Piece->SetStateVisible(true);
		DragonCharacter->SetEnvironmentPiece(Piece);
		PieceCoorPtr = PieceCoorPtr->Next;
	}
}
//将目标玩家的棋子按照其在棋盘上的位置信息生成并放置到当前玩家角色的环境棋子数组中
void AClothoPlayerController::SpawnPlayerPiecesAsEnvironmentPieces(int32 TargetPlayerIndex)
{
	// 获取游戏状态
	AClothoGameState* ClothoGameState = Cast<AClothoGameState>(UGameplayStatics::GetGameState(this));
	// 当前玩家角色，游戏模式,目标玩家的控制器和角色
	ADragonCharacter* DragonCharacter = Cast<ADragonCharacter>(GetPawn());
	AClothoGameMode* ClothoGameMode = Cast<AClothoGameMode>(GetWorld()->GetAuthGameMode());
	APlayerController* PlayerController = ClothoGameMode->GetPlayerControllerByIndex(TargetPlayerIndex);
	ADragonCharacter* TargetDragon = Cast<ADragonCharacter>(PlayerController->GetPawn());
	// 目标玩家角色的棋子数组和当前玩家的旋转角度
	TArray<APawnBase*> TargetPiece = TargetDragon->GetPiecesInBoard();
	float Yaw = UClothoFunctionLibrary::GetYawByBoardIndex(DragonCharacter->GetPlayerIndex());
	// 遍历目标玩家的棋子数组
	for (int32 i = 0; i < TargetPiece.Num(); ++i)
	{
		APawnBase* Piece = TargetPiece[i];
		if (Piece)
		{
			FVector Location = DragonCharacter->GetGridLocationByReverseIndex(i);// 获取当前玩家角色的棋盘格位置
			// 获取一个空闲的棋子，并设置位置、旋转及可见状态
			APawnBase* NewPiece = ClothoGameState->GetFreePieceByIndex(Piece->GetSelfIndex());
			NewPiece->SetActorLocation(Location);
			NewPiece->SetActorRotation(FRotator(0, Yaw + 180, 0));
			NewPiece->SetStateVisible(true);
			DragonCharacter->SetEnvironmentPiece(NewPiece);// 将生成的棋子添加到当前玩家角色的环境棋子数组中
		}
	}
}
// 获取并显示玩家的排名UI
void AClothoPlayerController::GetAndShowRankUI()
{
	AClothoGameMode* ClothoGameMode = Cast<AClothoGameMode>(GetWorld()->GetAuthGameMode());
	int32 Rank = ClothoGameMode->GetAndChangeRank();// 获取并改变排名
	ShowRankUI(Rank);// 显示排名UI
}
// 在玩家控制器上开始战斗倒计时UI
void AClothoPlayerController::StartFightCountDownUI_Implementation()
{
	UGameStateWidget* GameStateWidget = UClothoFunctionLibrary::GetGameStateWidget(this);
	GameStateWidget->StartFightCountDown();
}
// 在玩家控制器上开始部署倒计时UI
void AClothoPlayerController::StartDeployCountDownUI_Implementation()
{
	UGameStateWidget* GameStateWidget = UClothoFunctionLibrary::GetGameStateWidget(this);
	GameStateWidget->StartDeployCountDown();
}
// 玩家购买棋子的实现，包括生成棋子，设置位置等
void AClothoPlayerController::UserBuyPiece_Implementation(int32 PieceIndex)
{
	// 获取玩家角色
	ADragonCharacter* DragonCharacter = Cast<ADragonCharacter>(GetPawn());
	FVector Location;
	// 获取等待区域的位置和索引
	int32 GridIndex = DragonCharacter->GetPieceIndexInWaiting(Location);
	// 获取棋子数据
	FPieceData* Data = UClothoFunctionLibrary::GetPieceInfoManager(this)->GetPieceDataByID(PieceIndex);
	TSubclassOf<APawnBase> PieceClass = Data->PieceClass;// 获取棋子类

	Location.Z += 43.f;// 调整生成位置
	float Yaw = UClothoFunctionLibrary::GetYawByBoardIndex(DragonCharacter->GetPlayerIndex());// 获取玩家在棋盘上的朝向
	FTransform Transform;// 生成棋子的变换信息
	APawnBase* Piece = GetWorld()->SpawnActorDeferred<APawnBase>(PieceClass, Transform);// 在世界中生成棋子
	Piece->SetSelfIndex(PieceIndex);// 设置棋子的索引
	Piece->FinishSpawning(FTransform(FRotator(0, Yaw, 0), Location), false);// 完成生成
	DragonCharacter->SetPieceInWaiting(GridIndex, Piece);// 将棋子放入等待区域
}
// 校验玩家购买棋子的有效性
bool AClothoPlayerController::UserBuyPiece_Validate(int32 PieceIndex)
{
	FPieceData* Data = UClothoFunctionLibrary::GetPieceInfoManager(this)->GetPieceDataByID(PieceIndex);
	if (Data)
	{
		//todo 检测金币是否够用

		//todo 检测数组已满
		return true;
	}
	return false;
}
// 刷新商店中棋子的索引信息
void AClothoPlayerController::RefreshShopPiece_Implementation()
{
	AClothoPlayerState* ClothoPlayerState = GetPlayerState<AClothoPlayerState>();
	ClothoPlayerState->RefreshShopPieceIndex();// 调用玩家状态对象的函数，刷新商店中棋子的索引信息
}
// 在每帧检查玩家的鼠标点击位置，根据需要移动或处理焦点棋子的落子位置
void AClothoPlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);

	if (!(bMoveToMouseCursor || FocusPiece))
	{
		return;
	}

	FHitResult Hit;
	GetHitResultUnderCursor(ECC_Visibility, false, Hit);
	if (bMoveToMouseCursor)
	{
		MoveToMouseCursor(Hit);// 根据鼠标点击位置移动玩家角色
	}

	if (FocusPiece)
	{
		CheckPieceDropPos(Hit);// 检查焦点棋子的落子位置
	}
}
// 设置输入组件，绑定操作
void AClothoPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	InputComponent->BindAction("SetDestination", IE_Pressed, this, &AClothoPlayerController::OnSetDestinationPressed);
	InputComponent->BindAction("SetDestination", IE_Released, this, &AClothoPlayerController::OnSetDestinationReleased);
	InputComponent->BindAction("LeftMouseClick", IE_Released, this, &AClothoPlayerController::OnLeftMouseClickPressed);
}
// 控制器开始占用角色
void AClothoPlayerController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);


	ADragonCharacter* DragonCharacter = Cast<ADragonCharacter>(InPawn);
	ChangeCamera(DragonCharacter->GetPlayerIndex());// 切换相机到指定玩家的视角

}
// 根据鼠标点击的结果，决定是否移动到点击位置，并执行相应的操作
void AClothoPlayerController::MoveToMouseCursor(FHitResult Hit)
{
	
	if (Hit.bBlockingHit)
	{

		// 如果点击到的是棋子，则不执行移动操作
		if (Cast<APawnBase>(Hit.Actor))
		{
			return;
		}

		// 计算当前玩家角色与点击位置的距离
		FVector ActorLocation = GetPawn()->GetActorLocation();
		FVector Distance = Hit.Location - ActorLocation;
		// 如果距离小于阈值，表示在同一棋盘内，执行移动操作
		if (Distance.Size2D() < 2500)
		{
			// 寻找路径并设置玩家角色移动路径
			UNavigationPath* NavigationPath = UNavigationSystemV1::FindPathToLocationSynchronously(
				GetWorld(), GetPawn()->GetActorLocation(), Hit.Location);
			Cast<ADragonCharacter>(GetPawn())->SetPath(NavigationPath);
		}

		// 如果之前没有生成鼠标点击特效，生成鼠标点击特效
		if (!bHaveSpawnedActor)
		{
			bHaveSpawnedActor = true;
			SpawnMouseClickDecal(Hit);
		}
	}
}
// 检查棋子放置位置，并更新相应的特效和状态
void AClothoPlayerController::CheckPieceDropPos(FHitResult HitResult)
{
	if (HitResult.bBlockingHit)
	{
		// 将目标位置提升，以适应棋子的高度
		FVector TargetPosition = HitResult.Location + FVector(0.f, 0.f, 60.f);
		if (FocusPiece)
		{
			FocusPiece->SetFollowPosition(TargetPosition);// 设置被拖动的棋子跟随鼠标移动
		}

		// 获取鼠标下方的碰撞信息，主要检测是否在特效格子上
		FHitResult Hit;
		GetHitResultUnderCursor(COLLISION_GRID, false, Hit);
		AGridEffectActor* GridEffectActor = Cast<AGridEffectActor>(Hit.Actor);
		// 如果鼠标下方是有效的特效格子
		if (GridEffectActor && GridEffectActor->GetIsVisible())
		{
			// 如果之前有焦点格子，并且新的格子不同，则还原之前格子的特效颜色
			if (FocusGrid && GridEffectActor != FocusGrid)
			{
				FocusGrid->SetEffectColor(EGridColor::Egc_Blue);
			}
			// 更新焦点格子，并改变其特效颜色
			FocusGrid = GridEffectActor;
			FocusGrid->SetEffectColor(EGridColor::Egc_Yellow);
		}
		// 如果之前有焦点格子，但新的格子无效，则还原之前格子的特效颜色
		else if (FocusGrid)
		{
			FocusGrid->SetEffectColor(EGridColor::Egc_Blue);
			FocusGrid = nullptr;
		}
	}
}
// 设置新的移动目标位置，通过简单的移动到指定位置的命令实现
void AClothoPlayerController::SetNewMoveDestination(const FVector DestLocation)
{
	APawn* const MyPawn = GetPawn();
	if (MyPawn)
	{
		const float Distance = FVector::Dist(DestLocation, MyPawn->GetActorLocation());

		UAIBlueprintHelperLibrary::SimpleMoveToLocation(this, DestLocation);

		UE_LOG(LogTemp, Warning, TEXT("=========================="))

	}
}
// 当按下设置目标位置的按钮时，标记开始移动到鼠标光标位置
void AClothoPlayerController::OnSetDestinationPressed()
{
	bMoveToMouseCursor = true;
}
// 当释放设置目标位置的按钮时，标记停止移动到鼠标光标位置，并重置生成的演员的标志
void AClothoPlayerController::OnSetDestinationReleased()
{
	bMoveToMouseCursor = false;
	bHaveSpawnedActor = false;
}
// 当左键点击时执行的操作，用于处理拖动棋子等行为
void AClothoPlayerController::OnLeftMouseClickPressed()
{
	// 设置棋子信息面板不激活
	UClothoFunctionLibrary::GetPieceInfoWidget(this)->SetActivate(false);
	// 如果没有焦点棋子，则直接返回
	if (!FocusPiece)
	{
		return;
	}

	ADragonCharacter* DragonCharacter = Cast<ADragonCharacter>(GetPawn());
	// 如果已经拖动了棋子
	if (bHasDragPiece)
	{
		// 如果有焦点格子
		if (FocusGrid)
		{
			bool bGridIsWaiting;
			FVector Location;
			int32 GridIndex = DragonCharacter->GetGridIndex(FocusGrid, Location, bGridIsWaiting);

			// 根据权限调用相应的函数来设置棋子的位置和状态
			if (GetLocalRole() == ROLE_Authority)
			{
				DragonCharacter->SetPieceByGrid(GridIndex, bGridIsWaiting, Location, FocusPieceIndex, bFocusPieceIsWaiting, PieceOriginLocation);
			}
			else
			{
				DragonCharacter->Server_SetPieceByGrid(GridIndex, bGridIsWaiting, Location, FocusPieceIndex, bFocusPieceIsWaiting, PieceOriginLocation);
			}
		}
		else
		{
			FocusPiece->SetActorLocation(PieceOriginLocation);// 如果没有焦点格子，则还原棋子的位置
		}

		// 结束棋子的拖动状态，还原碰撞属性和显示格子特效
		FocusPiece->SetFollow(false);
		FocusPiece->GetCapsuleComponent()->SetCollisionProfileName(TEXT("ChessPiece"));
		FocusPiece->GetMesh()->SetCollisionProfileName(TEXT("PieceMesh"));
		DragonCharacter->ShowGridEffect(false);
		FocusPiece = nullptr;
	}
	else
	{
		// 如果没有拖动棋子，记录棋子的初始位置，并设置棋子为拖动状态
		PieceOriginLocation = FocusPiece->GetActorLocation();
		FocusPiece->SetFollow(true);
		FocusPiece->GetCapsuleComponent()->SetCollisionProfileName(TEXT("ChessPieceHold"));
		FocusPiece->GetMesh()->SetCollisionProfileName(TEXT("ChessPieceHold"));
		DragonCharacter->ShowGridEffect(true);
	}

	bHasDragPiece = !bHasDragPiece;// 切换拖动状态标志
}
// 在鼠标点击位置生成鼠标点击效果
void AClothoPlayerController::SpawnMouseClickDecal(FHitResult HitResult)
{
	FVector CursorFV = HitResult.ImpactNormal;
	FRotator CursorR = CursorFV.Rotation();
	// 通过蓝图类生成鼠标点击效果的实例
	TSubclassOf<AMouseClickActor> MoveToMouseCursorClass = LoadClass<AMouseClickActor>(
		nullptr,TEXT("Blueprint'/Game/Clotho/Actors/BP_MouseClickActor.BP_MouseClickActor_C'"));


	FTransform Transform(CursorR, HitResult.Location);
	AMouseClickActor* MouseClickActor = GetWorld()->SpawnActorDeferred<AMouseClickActor>(
		MoveToMouseCursorClass, Transform);
	MouseClickActor->FinishSpawning(Transform);
}
// 检查是否移动到目标位置
void AClothoPlayerController::CheckToMove(const FVector DestLocation)
{
	if (GetLocalRole() == ROLE_Authority)
	{
		SetNewMoveDestination(DestLocation);// 设置新的移动目标位置
		return;
		return;
	}

	Server_SetNewMoveDestination(DestLocation);// 在服务器上设置新的移动目标位置

}

// 在服务端执行切换相机的操作，通过调用ChangeCamera函数实现
void AClothoPlayerController::Server_ChangeCamera_Implementation(int32 Index)
{
	ChangeCamera(Index);
}
// 获取相机总监对象，如果不存在，则从世界中获取并缓存
ACameraDirector* AClothoPlayerController::GetCameraDirector()
{
	if (!CameraDirector)
	{
		TArray<AActor*> CameraDirectors;

		UGameplayStatics::GetAllActorsOfClass(this, ACameraDirector::StaticClass(), CameraDirectors);

		if (CameraDirectors.Num() <= 0)
		{
			return nullptr;
		}
		CameraDirector = Cast<ACameraDirector>(CameraDirectors[0]);
	}

	return CameraDirector;
}
// 在服务端执行开始游戏的操作，调用StartGame函数
void AClothoPlayerController::Server_StartGame_Implementation()
{
	StartGame();
}
// 开始游戏的函数，包括初始化商店和排行榜等操作
void AClothoPlayerController::StartGame()
{
	UE_LOG(LogTemp, Warning, TEXT("Start Game"))



	// 测试 商店生成棋子
	if (AClothoGameMode* ClothoGameMode = Cast<AClothoGameMode>(GetWorld()->GetAuthGameMode()))
	{
		ClothoGameMode->BindGridEffectManager();
		ClothoGameMode->InitRank();
	}


	ToggleState();
}
// 在服务端执行切换状态的操作，调用ToggleState函数
void AClothoPlayerController::Server_ToggleState_Implementation()
{
	ToggleState();
}


// 刷新商店UI的实现，通过获取玩家状态对象获取商店棋子信息并更新UI
void AClothoPlayerController::RefreshShopUI_Implementation()
{
	AClothoPlayerState* ClothoPlayerState = GetPlayerState<AClothoPlayerState>();

	UShopWidget* ShopWidget = UClothoFunctionLibrary::GetShopWidget(this);
	ShopWidget->RefreshShopPieceIndex(ClothoPlayerState->GetShopPieceIndex());
	ShopWidget->RefreshShopUI();
}
// 切换状态的函数，通过调用GameMode的ToggleState函数实现
void AClothoPlayerController::ToggleState()
{
	UE_LOG(LogTemp, Warning, TEXT("ToggleState"))

	if (AClothoGameMode* ClothoGameMode = Cast<AClothoGameMode>(GetWorld()->GetAuthGameMode()))
	{
		ClothoGameMode->ToggleState();
	}
}
// 在服务端执行显示排名UI的操作，调用BlueprintShowRankUI函数
void AClothoPlayerController::ShowRankUI_Implementation(int32 Rank)
{
	BlueprintShowRankUI(Rank);
}
// 改变相机的函数，通过调用ChangeCamera函数实现
void AClothoPlayerController::ChangeCamera(int32 Index)
{
	ACameraDirector* Director = GetCameraDirector();
	if (!Director)
	{
		UE_LOG(LogTemp, Warning, TEXT("No Camera Director"))
		return;
	}
	SetViewTarget(Director->GetCameraByIndex(Index));
}
// 在点击开始游戏按钮时执行的操作，如果是服务端则直接调用StartGame，否则调用服务端函数Server_StartGame
void AClothoPlayerController::OnClickedStartGame()
{
	if (GetLocalRole() == ROLE_Authority)
	{
		StartGame();
		return;
	}

	Server_StartGame();
}
// 设置焦点棋子的函数，用于记录当前焦点棋子的信息
void AClothoPlayerController::SetFocusPiece(APawnBase* _FocusPiece)
{
	ADragonCharacter* DragonCharacter = Cast<ADragonCharacter>(GetPawn());
	bool bIsWaiting;
	int32 Index;
	if (!DragonCharacter->CheckPieceCanDrag(_FocusPiece, Index, bIsWaiting))
	{
		return;
	}

	FocusPiece = _FocusPiece;
	FocusPieceIndex = Index;
	bFocusPieceIsWaiting = bIsWaiting;
}
// 在点击切换状态按钮时执行的操作，如果是服务端则直接调用ToggleState，否则调用服务端函数Server_ToggleState
void AClothoPlayerController::OnClickedToggleState()
{
	if (GetLocalRole() == ROLE_Authority)
	{
		ToggleState();
		return;
	}

	Server_ToggleState();
}

// 在服务端执行设置新移动目标位置的操作，调用SetNewMoveDestination函数
void AClothoPlayerController::Server_SetNewMoveDestination_Implementation(const FVector DestLocation)
{
	SetNewMoveDestination(DestLocation);
}
