// Fill out your copyright notice in the Description page of Project Settings.


#include "PawnBase.h"

#include "NavModifierComponent.h"
#include "BehaviorTree/BehaviorTree.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "Clotho/ClothoPlayerController.h"
#include "Clotho/AI/PawnAIController.h"
#include "Clotho/Manager/PieceInfoManager.h"
#include "Clotho/Player/DragonCharacter.h"
#include "Clotho/Util/ClothoFunctionLibrary.h"
#include "Clotho/Widget/Main/PieceInfoWidget.h"
#include "Clotho/Widget/Piece/PieceStateWidget.h"
#include "Components/CapsuleComponent.h"
#include "Components/WidgetComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "NavAreas/NavArea_Default.h"
#include "NavAreas/NavArea_Null.h"
#include "Net/UnrealNetwork.h"


APawnBase::APawnBase()
{
	PrimaryActorTick.bCanEverTick = true;

	MaxHealth = 100.f;
	Health = MaxHealth;

	MaxMagic = 0.f;
	Magic = 0.f;
	MagicIncrease = 0.f;
	MagicPower = 0.f;

	Attack = 10.f;

	AttackSpeedBase = 1.f;
	AttackSpeedCoefficient = 0.f;
	AttackSpeedIncrease = 0.f;
	AttackSpeed = AttackSpeedBase + AttackSpeedCoefficient * AttackSpeedIncrease;

	AttackDistance = 100.f;

	Defence = 0.f;
	MagicDefence = 0.f;

	MoveSpeed = 300.f;

	Level = 0;

	GetCapsuleComponent()->SetCapsuleHalfHeight(44.f);
	GetCapsuleComponent()->SetCapsuleRadius(35.f);

	GetMesh()->SetRelativeLocation(FVector(0.f, 0.f, -46.f));  //设置角色骨骼网络的属性
	GetMesh()->SetRelativeRotation(FRotator(0.f, -90.f, 0.f)); 
	GetMesh()->SetRelativeScale3D(FVector(0.65f));

	AIControllerClass = APawnAIController::StaticClass(); //确保使用APawnAIController控制角色

	static ConstructorHelpers::FObjectFinder<UBehaviorTree> BehaviourTreeClass(
		TEXT("BehaviorTree'/Game/Clotho/AI/BT_Pawn.BT_Pawn'"));//加载行为树资源
	if (BehaviourTreeClass.Succeeded())
	{
		BehaviorTree = BehaviourTreeClass.Object;
	}


	HateIndex = -1;

	GetCapsuleComponent()->SetCollisionProfileName(TEXT("ChessPiece"));
	GetMesh()->SetCollisionProfileName(TEXT("PieceMesh"));

	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
	OwnerIndex = -1;
	SelfIndex = -1;

	DanceMontageDuration = 0.f;

	TimelineMax = 0.8f;
	TimeCount = 0.f;

	NavModifierComponent = CreateDefaultSubobject<UNavModifierComponent>(TEXT("NavModifier")); //创建导航组件
	NavModifierComponent->bIncludeAgentHeight = false; //修改导航区域时不包括角色的高度
	NavModifierComponent->AreaClass = UNavArea_Default::StaticClass(); //设置导航区的默认类

	WidgetComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("Widget")); //在3D空间显示2D UI组件
	WidgetComponent->SetupAttachment(RootComponent); //将其添加到父级组件
	WidgetComponent->SetWidgetSpace(EWidgetSpace::Screen); //设置UI的空间坐标系为屏幕坐标系
	WidgetComponent->SetDrawSize(FVector2D(100, 20)); //UI的尺寸

	static ConstructorHelpers::FClassFinder<UUserWidget> StateWidgetClass(
		TEXT("WidgetBlueprint'/Game/Clotho/UI/Piece/WBP_PieceState.WBP_PieceState_C'")); //查找UI蓝图的类
	WidgetComponent->SetWidgetClass(StateWidgetClass.Class); //设置UI组件，确定显示的蓝图

	WidgetComponent->SetRelativeLocation(FVector(0.f, 0.f, 100.f)); //设置相对于父节点的未知
}

void APawnBase::BeginPlay()
{
	Super::BeginPlay(); //执行父类的初始化

	GetMesh()->OnBeginCursorOver.AddDynamic(this, &APawnBase::OnBeginCursorOverEvent); //鼠标悬停时的操作
	GetMesh()->OnEndCursorOver.AddDynamic(this, &APawnBase::OnEndCursorOverEvent); //鼠标不再悬停的操作
	GetMesh()->OnClicked.AddDynamic(this, &APawnBase::OnMeshClickedEvent); //鼠标点击的操作

	BindPieceFigure(); //初始化角色的属性

	Cast<UPieceStateWidget>(WidgetComponent->GetWidget())->SetPiece(this); //将角色实例传给UI，以实现交互
}

void APawnBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime); //父类的初始化

	if (TimeCount <= TimelineMax) //时间线未结束
	{
		TimeCount += DeltaTime; //时间流逝
		const float Value = FMath::Clamp<float>((TimelineMax - TimeCount) / TimelineMax, 0, 1); //计算插值系数（当前时间对于总时间的进度）
		Difference *= Value; //实现平滑的改变，减小difference的影响
	}

	if (bFollow)
	{
		SetActorLocation(FollowPosition + Difference); //启用跟随，则改变角色位置
	}
}

void APawnBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent); //为角色绑定玩家输入
}

void APawnBase::RunBehaviourTree()
{
	if (APawnAIController* PawnAIController = Cast<APawnAIController>(UAIBlueprintHelperLibrary::GetAIController(this)))
	{ //检查角色是否由APawnAIController控制
		PawnAIController->RunMyBehaviourTree(); //如果是的话，就运行行为树
	}
}

void APawnBase::StopBehaviourTree()
{
	if (!GetController()) //检查是否有AI控制器
	{
		UE_LOG(LogTemp, Warning, TEXT("no AI Controller"))
		return;
	}
	if (APawnAIController* PawnAIController = Cast<APawnAIController>(GetController()))
	{ //转换成功，则表明角色由APawnAIController控制
		PawnAIController->StopMyBehaviourTree(); //停止行为树
	}
}

void APawnBase::SetFollow(bool Follow_) //设置是否跟随
{
	bFollow = Follow_;
	if (bFollow)
	{
		bIsSetDifference = false;
	}
}

void APawnBase::SetFollowPosition(FVector FollowPosition_)
{
	FollowPosition = FollowPosition_;
	if (!bIsSetDifference)
	{
		bIsSetDifference = true;
		Difference = GetActorLocation() - FollowPosition; //计算当前位置与目标位置的差异
		StartInterpTimeline(); //平滑过渡差异
	}
}

void APawnBase::Dance_Implementation()
{
	if (DanceMontage)
	{
		DanceMontageDuration = PlayAnimMontage(DanceMontage);
	}
}

void APawnBase::DoAttack_Implementation()
{
	if (AttackMontage) //如果设置了攻击动画
	{
		AttackMontageDuration = PlayAnimMontage(AttackMontage);

	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("no Attack"))
	}
}

void APawnBase::DoDeath_Implementation()
{
	if (DeathMontage)
	{
		GetCapsuleComponent()->SetCollisionProfileName(TEXT("ChessPieceDied"));
		DeathMontageDuration = PlayAnimMontage(DeathMontage);

		WidgetComponent->SetVisibility(false); //在屏幕上清除角色
	}
}

void APawnBase::SetNavNull(bool bNull) const
{
	if (bNull)
	{
		NavModifierComponent->AreaClass = UNavArea_Null::StaticClass(); //不可通行
	}
	else
	{
		NavModifierComponent->AreaClass = UNavArea_Default::StaticClass(); //运行通行
	}
}

void APawnBase::OnGetDamage(float Damage)
{
	Health -= Damage * (100 - Defence) / 100; //造成伤害
}

void APawnBase::OnBeginCursorOverEvent(UPrimitiveComponent* TouchedComponent)
{
	TArray<UActorComponent*> Components;
	GetComponents(UPrimitiveComponent::StaticClass(), Components); //获取角色碰撞体组件

	for (const auto ActorComponent : Components)
	{
		Cast<UPrimitiveComponent>(ActorComponent)->SetRenderCustomDepth(true); //均设置为深度渲染
	}
}

void APawnBase::OnEndCursorOverEvent(UPrimitiveComponent* TouchedComponent)
{

	TArray<UActorComponent*> Components;
	GetComponents(UPrimitiveComponent::StaticClass(), Components); //获取角色碰撞体组件

	for (const auto ActorComponent : Components)
	{
		Cast<UPrimitiveComponent>(ActorComponent)->SetRenderCustomDepth(false); //复原
	}
}

void APawnBase::OnMeshClickedEvent(UPrimitiveComponent* TouchedComponent, FKey ButtonPressed)
{
	if (ButtonPressed.GetFName().IsEqual(FName(TEXT("LeftMouseButton")))) //左击
	{
		AClothoPlayerController* PlayerController = UClothoFunctionLibrary::GetClothoPlayerController(this);
		if (!PlayerController->ControllerHasFocusPiece()) //如果当前没有控制任何棋子
		{
			PlayerController->SetFocusPiece(this); //控制这个棋子
		}
	}
	else if (ButtonPressed.GetFName().IsEqual(FName(TEXT("RightMouseButton")))) //右击
	{
		UPieceInfoWidget* PieceInfoWidget = UClothoFunctionLibrary::GetPieceInfoWidget(this); //获取信息窗口
		PieceInfoWidget->SetPiece(this); //将棋子的信息输出至窗口
	}
}

void APawnBase::StartInterpTimeline()
{
	TimeCount = 0.f; //设置开始时间为0
}

void APawnBase::BindPieceFigure()
{
	FPieceFigureConfig* FigureConfig = UClothoFunctionLibrary::GetPieceInfoManager(this)->
		GetPieceFigureConfigByID(SelfIndex); //根据自己的索引获取信息

	MaxHealth = FigureConfig->MaxHealth;
	Health = MaxHealth;

	//minion has no Magic or skill
	MaxMagic = FigureConfig->MaxMagic;
	Magic = 0.f;
	MagicIncrease = FigureConfig->MagicIncrease;
	MagicPower = FigureConfig->MagicPower;

	Attack = FigureConfig->Attack;

	AttackSpeedBase = FigureConfig->AttackSpeedBase;
	AttackSpeedCoefficient = FigureConfig->AttackSpeedCoefficient;
	AttackSpeedIncrease = 0.f;
	AttackSpeed = AttackSpeedBase + AttackSpeedCoefficient * AttackSpeedIncrease;

	AttackDistance = FigureConfig->AttackDistance;

	Defence = FigureConfig->Defence;
	MagicDefence = FigureConfig->MagicDefence;

	MoveSpeed = FigureConfig->MoveSpeed; 

	GetCharacterMovement()->MaxWalkSpeed = MoveSpeed; //以上做出信息的更新
}

void APawnBase::OnDeathMontageFinished()
{
	SetActorLocation(FVector(0,0,-1000)); //更改位置到地面之下
}

void APawnBase::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const //定义网络同步属性，确保玩家看到的相同
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(APawnBase,SelfIndex)
	DOREPLIFETIME(APawnBase,OwnerIndex)
	DOREPLIFETIME(APawnBase,Health)
	DOREPLIFETIME(APawnBase,Magic)
}

void APawnBase::ResetState()
{
	GetCapsuleComponent()->SetCollisionProfileName(TEXT("ChessPiece"));
	Health = MaxHealth; //回满血
	Magic = 0.f;
	StopBehaviourTree(); //停止行为树
}

void APawnBase::SetStateVisible_Implementation(bool Visible)
{
	WidgetComponent->SetVisibility(Visible); //在网络上实现同步的可视化
}