// Fill out your copyright notice in the Description page of Project Settings.


#include "DragonCharacter.h"

#include "NavigationPath.h"
#include "Camera/CameraComponent.h"
#include "Clotho/Clotho.h"
#include "Clotho/ClothoGameMode.h"
#include "Clotho/ClothoGameState.h"
#include "Clotho/Actor/GridEffectActor.h"
#include "Clotho/Actor/GridEffectManager.h"
#include "Clotho/Pawn/PawnBase.h"
#include "Clotho/Util/ClothoFunctionLibrary.h"
#include "Clotho/Widget/Piece/DragonStateWidget.h"
#include "Components/CapsuleComponent.h"
#include "Components/DecalComponent.h"
#include "Components/WidgetComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Net/UnrealNetwork.h"
#include "Particles/ParticleSystemComponent.h"


ADragonCharacter::ADragonCharacter()
{
	PrimaryActorTick.bCanEverTick = true;	//将该变量设置为true，意味着该角色将每帧都调用Tick（）

	GetCapsuleComponent()->InitCapsuleSize(42.f, 45.f);//设置胶囊大小，宽42，高45

	bUseControllerRotationPitch = false;//设置为false意味着这个角色不会通过控制器进行移动或旋转，pitch为绕x轴旋转
	bUseControllerRotationRoll = false;//roll为绕z轴旋转
	bUseControllerRotationYaw = false;//yaw为绕y轴旋转

	GetCharacterMovement()->bOrientRotationToMovement = true;//角色方向随移动方向自动调整
	GetCharacterMovement()->RotationRate = FRotator(0.f, 720.f, 0.f);//设置旋转速率
	GetCharacterMovement()->bConstrainToPlane = true;
	GetCharacterMovement()->bSnapToPlaneAtStart = true;//// 当开始移动时，限制角色方向，直到停止移动。


	GetMesh()->SetRelativeRotation(FRotator(0.f, -90.f, 0.f));//设置相对于角色的网格旋转
	GetMesh()->SetRelativeLocation(FVector(-10.f, 0.f, -45.f));//设置相对于角色的网格位置
	PlayerIndex = -1;//初始化玩家索引

	HateIndex = -1;//初始化敌人（仇恨目标）索引

	PawnsInBoard.Init(nullptr, 21);//初始化棋盘上的棋子数组
	PawnsInWaiting.Init(nullptr, 8);//初始化等待中的棋子数组

	WidgetComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("Widget"));//创建名为 "Widget" 的 WidgetComponent
	WidgetComponent->SetupAttachment(RootComponent);//将 WidgetComponent 附加到 RootComponent
	WidgetComponent->SetWidgetSpace(EWidgetSpace::Screen);//设置 Widget 在屏幕空间中
	WidgetComponent->SetDrawSize(FVector2D(100, 15));//设置 Widget 绘制的大小

	static ConstructorHelpers::FClassFinder<UUserWidget> StateWidgetClass(TEXT("WidgetBlueprint'/Game/Clotho/UI/Piece/WBP_DragonState.WBP_DragonState_C'"));
	WidgetComponent->SetWidgetClass(StateWidgetClass.Class);//使用类查找器找到指定路径下的 WidgetBlueprint 类，并将其设置为 WidgetComponent 的 WidgetClass

	WidgetComponent->SetRelativeLocation(FVector(0.f, 0.f, 100.f));//将 WidgetComponent 相对于其父组件（在这里是 RootComponent）的位置设置为 (0.f, 0.f, 100.f)

	HealthMax = 100;//设置最大生命值
	Health = HealthMax;
}

void ADragonCharacter::BeginPlay()
{
	Super::BeginPlay();//调用父类的 BeginPlay 函数
	 TArray<AActor*> Outer;
	 UGameplayStatics::GetAllActorsOfClass(this,APawnBase::StaticClass(),Outer);//获取场景中所有 APawnBase 类型的角色
	 for (auto Actor:Outer)
	 {
	 	if (APawnBase* PawnBase = Cast<APawnBase>(Actor))
	 	{
	 		PawnsInBoard.Add(PawnBase);//将获取到的角色添加到棋盘上的棋子数组
	 	}
	 }

	
	Cast<UDragonStateWidget>(WidgetComponent->GetWidget())->SetDragon(this);//设置 Widget 上的 DragonStateWidget 的 Dragon 属性为当前角色
}

void ADragonCharacter::CheckDeath()
{
	if (Health > 0)
	{
		return;
	}


	AClothoPlayerController* ClothoPlayerController = Cast<AClothoPlayerController>(GetController());
	ClothoPlayerController->GetAndShowRankUI();//获取并显示排名 UI
	ClothoPlayerController->SetShopUIPieceVisible(ESlateVisibility::Collapsed);//隐藏死亡者的商店 UI

	ClearEnvironmentPiece();//清除环境棋子
	DestroyPieces();//销毁棋子
	SetStateVisible(false);// 设置状态不可见
	SetActorLocation(FVector(0, 0, -1000));//设置角色位置在不可见的位置
}

void ADragonCharacter::DestroyPieces()
{
	for (auto Piece : PawnsInBoard)
	{
		if (Piece)
		{
			Piece->Destroy();// 销毁棋盘上的棋子
			Piece = nullptr;
		}
	}

	for (auto Piece : PawnsInWaiting)
	{
		if (Piece)
		{
			Piece->Destroy();// 销毁等待中的棋子
			Piece = nullptr;
		}
	}
}

void ADragonCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);//调用父类的 Tick 函数

	

	if (NavigationPath)
	{
		MoveToNextPoint(DeltaTime);//如果存在导航路径，则移动到下一个点
	}
}

// Called to bind functionality to input
void ADragonCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);//调用父类的 SetupPlayerInputComponent 函数
}

void ADragonCharacter::SetPath(UNavigationPath* NewNavigationPath)
{
	NavigationPath = NewNavigationPath;//设置导航路径
	TargetPointIndex = 1;//设置目标点索引
}

void ADragonCharacter::MoveToNextPoint(float DeltaTime)
{
	TArray<FVector> PathPoints = NavigationPath->PathPoints;//获取导航路径的路径点数组

	if (PathPoints.Num() <= TargetPointIndex)
	{
		NavigationPath = nullptr;//如果目标点索引超出路径点数组范围，将导航路径置为空
		return;
	}

	FVector Dist = PathPoints[TargetPointIndex] - GetActorLocation();//计算当前位置到目标点的距离向量
	Dist.Z = 0.f;//将距离向量的 Z 分量置为 0
	FVector TargetDirection = Dist.GetSafeNormal();//获取规范化的方向向量



	if (Dist.IsNearlyZero(0.5))
	{
		++TargetPointIndex;//如果距离足够接近目标点（小于 0.5），则切换到下一个目标点
		MoveToNextPoint(DeltaTime);
	}
	else
	{
		AddMovementInput(TargetDirection, DeltaTime * 500.f);//如果距离不够接近，通过 AddMovementInput 添加移动输入，以朝着目标方向移动
	}
}

void ADragonCharacter::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{//通过调用 DOREPLIFETIME 宏声明了 PlayerIndex、PawnsInBoard、PawnsInWaiting、EnvironmentPieces 和 Health 这些属性支持网络复制
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ADragonCharacter, PlayerIndex)
	DOREPLIFETIME(ADragonCharacter, PawnsInBoard)
	DOREPLIFETIME(ADragonCharacter, PawnsInWaiting)
	DOREPLIFETIME(ADragonCharacter, EnvironmentPieces)
	DOREPLIFETIME(ADragonCharacter, Health)
}

void ADragonCharacter::RunPawnsBehaviourTree()
{
	//遍历 PawnsInBoard 数组，为每个有效的 PawnBase 设置仇恨索引、所有者索引，并运行行为树。
	for (auto PawnBase : PawnsInBoard)
	{
		if (PawnBase)
		{
			PawnBase->SetHateIndex(HateIndex);//设置仇恨索引为当前角色的 HateIndex
			PawnBase->SetOwnerIndex(PlayerIndex);//设置所有者索引为当前角色的 PlayerIndex
			PawnBase->RunBehaviourTree();//运行 PawnBase 的行为树
		}
	}
	//如果 EnvironmentPieces 数组中有环境角色，则同样为它们设置仇恨索引、所有者索引，并运行行为树
	if (EnvironmentPieces.Num() > 0)
	{
		for (auto EnvironmentPiece : EnvironmentPieces)
		{
			if (EnvironmentPiece)
			{
				EnvironmentPiece->SetHateIndex(PlayerIndex);//设置仇恨索引为当前角色的 PlayerIndex
				EnvironmentPiece->SetOwnerIndex(PlayerIndex);//设置所有者索引为当前角色的 PlayerIndex
				EnvironmentPiece->RunBehaviourTree();//运行 EnvironmentPiece 的行为树
			}
		}
	}
}

void ADragonCharacter::StopPawnsBehaviourTree()
{
	//遍历 PawnsInBoard 数组，停止每个有效 PawnBase 的行为树
	for (const auto PawnBase : PawnsInBoard)
	{
		PawnBase->StopBehaviourTree();
	}
}

APawnBase* ADragonCharacter::GetValidatePawnInBoard(const APawnBase* OriginPiece)
{
	//获取原始棋子的位置
	const FVector OriginLocation = OriginPiece->GetActorLocation();
	float MinDistance = 1000000.f; 
	APawnBase* Result = nullptr;
	//遍历 PawnsInBoard 数组，寻找距离原始棋子最近的有效 PawnBase
	for (const auto PawnBase : PawnsInBoard)
	{
		if (PawnBase && PawnBase->Alive())
		{
			//计算当前 PawnBase 与原始棋子的距离
			const float CurrentDistance = FVector::Distance(OriginLocation, PawnBase->GetActorLocation());
			if (CurrentDistance < MinDistance)
			{
				//更新最小距离和结果
				MinDistance = CurrentDistance;
				Result = PawnBase;
			}
		}
	}

	return Result;//返回最近的有效 PawnBase
}

APawnBase* ADragonCharacter::GetValidateEnvironmentPieceInBoard(const APawnBase* OriginPiece)
{
	//获取原始环境棋子的位置
	const FVector OriginLocation = OriginPiece->GetActorLocation();
	float MinDistance = 1000000.f; 
	APawnBase* Result = nullptr;
	//遍历 EnvironmentPieces 数组，寻找距离原始环境棋子最近的有效 PawnBase
	for (const auto PawnBase : EnvironmentPieces)
	{
		if (PawnBase && PawnBase->Alive())
		{
			//计算当前 PawnBase 与原始环境棋子的距离
			const float CurrentDistance = FVector::Distance(OriginLocation, PawnBase->GetActorLocation());
			if (CurrentDistance < MinDistance)
			{
				MinDistance = CurrentDistance;
				Result = PawnBase;
			}
		}
	}

	return Result;//返回最近的有效 PawnBase
}

bool ADragonCharacter::CheckPieceCanDrag(APawnBase* Piece, int32& Index, bool& bIsWaiting)
{
	//如果棋子在等待区（PawnsInWaiting），返回其索引和标记为等待状态
	int32 PieceIndex = PawnsInWaiting.Find(Piece);
	if (PieceIndex != INDEX_NONE)
	{
		Index = PieceIndex;
		bIsWaiting = true;
		return true;
	}
	//如果当前游戏状态是战斗状态（Egs_Fight），返回不可拖拽
	if (UClothoFunctionLibrary::GetCurrentGameState(this) == EGameState::Egs_Fight)
	{
		return false;
	}
	//如果棋子在棋盘区（PawnsInBoard），返回其索引和标记为非等待状态
	PieceIndex = PawnsInBoard.Find(Piece);
	if (PieceIndex != INDEX_NONE)
	{
		Index = PieceIndex;
		bIsWaiting = false;
		return true;
	}
	return false;
}

void ADragonCharacter::BindGridEffectManager_Implementation()
{
	//获取所有的网格效果管理器
	TArray<AActor*> OutActors;
	UGameplayStatics::GetAllActorsOfClass(this, AGridEffectManager::StaticClass(), OutActors);
	//检查当前遍历到的 GridEffectManager_ 的网格索引是否与当前玩家的索引 PlayerIndex 匹配
	for (AActor* Actor : OutActors)
	{
		AGridEffectManager* GridEffectManager_ = Cast<AGridEffectManager>(Actor);
		if (GridEffectManager_->GetGridIndex() == PlayerIndex)//如果匹配，将当前的 GridEffectManager_ 赋值给类成员变量 GridEffectManager，并立即返回函数
		{
			GridEffectManager = GridEffectManager_;
			return;
		}
	}
}

void ADragonCharacter::ShowGridEffect(bool Show, bool bIsSelf)
{
	if (GridEffectManager)
	{
		GridEffectManager->ShowGridEffect(Show, bIsSelf);//通过 GridEffectManager 控制网格效果的显示状态
	}
}

int32 ADragonCharacter::GetPieceIndexInWaiting(FVector& SpawnLocation)
{
	//遍历等待区，找到第一个空槽位，返回其索引和对应的生成位置
	int32 Index;
	for (Index = 0; Index < PawnsInWaiting.Num(); ++Index)
	{
		if (!PawnsInWaiting[Index])
		{
			break;
		}
	}

	SpawnLocation = GridEffectManager->GetGridLocationByIndex(Index);

	return Index;
}

void ADragonCharacter::SetPieceInWaiting(int32 Index, APawnBase* Piece)
{
	//将棋子放置到等待区的指定索引位置
	PawnsInWaiting[Index] = Piece;
	Piece->SetOwnerIndex(GetPlayerIndex());
}

void ADragonCharacter::SetPieceByGrid_Implementation(int32 GridIndex, bool bGridIsWaiting, FVector GridLocation, int32 Index, bool bIsWaiting, FVector OriginPosition)
{
	//根据布尔值 bGridIsWaiting 和 bIsWaiting，选择目标数组和原始数组。这些数组包含等待中的棋子或在棋盘上的棋子
	TArray<APawnBase*>* TargetArray = bGridIsWaiting ? &PawnsInWaiting : &PawnsInBoard;
	TArray<APawnBase*>* OriginArray = bIsWaiting ? &PawnsInWaiting : &PawnsInBoard;

	APawnBase* Piece = (*OriginArray)[Index];//从原始数组中获取索引为 Index 的棋子

	GridLocation.Z += 43.f;
	Piece->SetActorLocation(GridLocation);//将棋子的位置设置为给定的 GridLocation，并在 Z 轴上增加 43.f 的高度为了将棋子放置在棋盘上方的一定高度

	//如果目标数组中的 GridIndex 位置已经有棋子，将该位置的棋子移动到原始位置，并更新原始数组中的相应索引
	if ((*TargetArray)[GridIndex])
	{
		(*TargetArray)[GridIndex]->SetActorLocation(OriginPosition);
		(*OriginArray)[Index] = (*TargetArray)[GridIndex];
	}
	else
	{
		(*OriginArray)[Index] = nullptr;//如果目标数组中的 GridIndex 位置没有棋子，将原始数组中的相应索引设置为 nullptr
	}


	(*TargetArray)[GridIndex] = Piece;//棋子放置到目标数组中的 GridIndex
}

void ADragonCharacter::Server_SetPieceByGrid_Implementation(int32 GridIndex, bool bGridIsWaiting, FVector GridLocation, int32 Index, bool bIsWaiting, FVector OriginPosition)
{
	SetPieceByGrid(GridIndex, bGridIsWaiting, GridLocation, Index, bIsWaiting, OriginPosition);//在服务器端设置棋子的位置。通过调用 SetPieceByGrid 函数，将棋子放置到指定的网格位置
}

int32 ADragonCharacter::GetGridIndex(AGridEffectActor* GridEffectActor, FVector& Location, bool& bGridIsWaiting)
{
	//用于获取网格效果actor（GridEffectActor）在 GridEffectManager 中的索引，以及其的位置和是否在等待区域
	int32 GridIndex = GridEffectManager->GetGridIndex(GridEffectActor, bGridIsWaiting);
	Location = GridEffectActor->GetActorLocation();
	return GridIndex;
}

FVector ADragonCharacter::GetGridLocationByReverseIndex(int32 Index)
{
	//用于获取指定索引对应的网格位置
	return GridEffectManager->GetBoardGridLocationByIndex(MAX_GRID_NUM - Index);
}

void ADragonCharacter::SetEnvironmentPiece(APawnBase* Piece)
{
	//将给定的环境棋子添加到 EnvironmentPieces 数组中，并设置其所有者索引为当前玩家索引
	EnvironmentPieces.Add(Piece);
	Piece->SetOwnerIndex(PlayerIndex);
}

void ADragonCharacter::ClearEnvironmentPiece()
{
	//获取游戏状态的引用
	AClothoGameState* ClothoGameState = Cast<AClothoGameState>(UGameplayStatics::GetGameState(this));
	//遍历环境棋子数组中的每个棋子
	for (auto Piece : EnvironmentPieces)
	{
		Piece->ResetState();//重置棋子状态
		Piece->SetStateVisible(false);//将棋子的可见性设置为隐藏
		Piece->SetActorLocation(FVector(0, 0, -1000));//将棋子移动到地图下方的位置
		ClothoGameState->SetFreePieceByIndex(Piece, Piece->GetSelfIndex());//通知游戏状态该棋子现在是自由的，位于其原始索引位置
	}

	EnvironmentPieces.Empty();//清空EnvironmentPieces数组
}

void ADragonCharacter::ChangeHealth(int32 Value)
{
	if (Value >= 0)
	{
		return;//如果生命值变化为正数或零，不执行任何操作
	}
	//减少生命值指定的数量
	Health += Value;
	//检查角色是否已死亡
	CheckDeath();
}

void ADragonCharacter::ResetPieces()
{
	//根据玩家索引获取Yaw旋转
	float Yaw = UClothoFunctionLibrary::GetYawByBoardIndex(GetPlayerIndex());
	//遍历PawnsInBoard数组中的每个棋子
	for (int32 i = 0; i < PawnsInBoard.Num(); ++i)
	{
		APawnBase* Piece = PawnsInBoard[i];
		if (Piece)
		{
			//将棋子的位置设置为对应的棋盘格位置
			FVector Location = GridEffectManager->GetBoardGridLocationByIndex(i);
			Piece->SetActorLocation(Location);
			Piece->SetActorRotation(FRotator(0, Yaw, 0));//将棋子的旋转设置为与棋盘对齐
			Piece->ResetState();//重置棋子的状态
			Piece->SetStateVisible(true);//将棋子的可见性设置为真
		}
	}
}

void ADragonCharacter::StartRunBehaviourTreeTimer()
{
	//启动运行棋子行为树的定时器，每隔0.3秒执行一次RunPawnsBehaviourTree函数
	GetWorldTimerManager().SetTimer(BehaviourTreeTimerHandle, this, &ADragonCharacter::RunPawnsBehaviourTree, 0.3);
}

void ADragonCharacter::GotoOtherBoard(int32 TargetPlayerIndex)
{
	//获取游戏模式的引用
	AClothoGameMode* ClothoGameMode = Cast<AClothoGameMode>(GetWorld()->GetAuthGameMode());
	//获取目标玩家的控制器和角色
	APlayerController* PlayerController = ClothoGameMode->GetPlayerControllerByIndex(TargetPlayerIndex);
	ADragonCharacter* TargetDragon = Cast<ADragonCharacter>(PlayerController->GetPawn());
	//AGridEffectManager* TargetGridEffectManager = TargetDragon->GetGridEffectManager();
	//获取目标玩家的Yaw旋转
	float Yaw = UClothoFunctionLibrary::GetYawByBoardIndex(TargetPlayerIndex);
	//遍历PawnsInBoard数组中的每个棋子
	for (int32 i = 0; i < PawnsInBoard.Num(); ++i)
	{
		APawnBase* Piece = PawnsInBoard[i];
		if (Piece)
		{
			//获取目标玩家中对应位置的逆向格子位置
			FVector Location = TargetDragon->GetGridLocationByReverseIndex(i);
			//设置棋子的位置和旋转
			Piece->SetActorLocation(Location);
			Piece->SetActorRotation(FRotator(0, Yaw + 180, 0));
		}
	}
	//设置当前玩家的位置和相机
	SetDragonLocationAndCameraByIndex(TargetPlayerIndex);
}

void ADragonCharacter::SetDragonLocationAndCameraByIndex(int32 TargetPlayerIndex)
{
	if (!Alive())
	{
		return;
	}
	//设置当前玩家的位置
	SetDragonLocationByIndex(TargetPlayerIndex);
	//计算目标相机的索引
	int32 TargetCameraIndex = TargetPlayerIndex == PlayerIndex ? TargetPlayerIndex : TargetPlayerIndex + 4;
	//获取玩家控制器的引用，并通过服务端更改相机
	AClothoPlayerController* ClothoPlayerController = Cast<AClothoPlayerController>(GetController());
	ClothoPlayerController->Server_ChangeCamera(TargetCameraIndex);
}

void ADragonCharacter::SetStateVisible_Implementation(bool Visible)
{
	//设置WidgetComponent的可见性
	WidgetComponent->SetVisibility(Visible);
}
