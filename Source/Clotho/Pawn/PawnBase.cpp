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

	GetMesh()->SetRelativeLocation(FVector(0.f, 0.f, -46.f));  //���ý�ɫ�������������
	GetMesh()->SetRelativeRotation(FRotator(0.f, -90.f, 0.f)); 
	GetMesh()->SetRelativeScale3D(FVector(0.65f));

	AIControllerClass = APawnAIController::StaticClass(); //ȷ��ʹ��APawnAIController���ƽ�ɫ

	static ConstructorHelpers::FObjectFinder<UBehaviorTree> BehaviourTreeClass(
		TEXT("BehaviorTree'/Game/Clotho/AI/BT_Pawn.BT_Pawn'"));//������Ϊ����Դ
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

	NavModifierComponent = CreateDefaultSubobject<UNavModifierComponent>(TEXT("NavModifier")); //�����������
	NavModifierComponent->bIncludeAgentHeight = false; //�޸ĵ�������ʱ��������ɫ�ĸ߶�
	NavModifierComponent->AreaClass = UNavArea_Default::StaticClass(); //���õ�������Ĭ����

	WidgetComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("Widget")); //��3D�ռ���ʾ2D UI���
	WidgetComponent->SetupAttachment(RootComponent); //������ӵ��������
	WidgetComponent->SetWidgetSpace(EWidgetSpace::Screen); //����UI�Ŀռ�����ϵΪ��Ļ����ϵ
	WidgetComponent->SetDrawSize(FVector2D(100, 20)); //UI�ĳߴ�

	static ConstructorHelpers::FClassFinder<UUserWidget> StateWidgetClass(
		TEXT("WidgetBlueprint'/Game/Clotho/UI/Piece/WBP_PieceState.WBP_PieceState_C'")); //����UI��ͼ����
	WidgetComponent->SetWidgetClass(StateWidgetClass.Class); //����UI�����ȷ����ʾ����ͼ

	WidgetComponent->SetRelativeLocation(FVector(0.f, 0.f, 100.f)); //��������ڸ��ڵ��δ֪
}

void APawnBase::BeginPlay()
{
	Super::BeginPlay(); //ִ�и���ĳ�ʼ��

	GetMesh()->OnBeginCursorOver.AddDynamic(this, &APawnBase::OnBeginCursorOverEvent); //�����ͣʱ�Ĳ���
	GetMesh()->OnEndCursorOver.AddDynamic(this, &APawnBase::OnEndCursorOverEvent); //��겻����ͣ�Ĳ���
	GetMesh()->OnClicked.AddDynamic(this, &APawnBase::OnMeshClickedEvent); //������Ĳ���

	BindPieceFigure(); //��ʼ����ɫ������

	Cast<UPieceStateWidget>(WidgetComponent->GetWidget())->SetPiece(this); //����ɫʵ������UI����ʵ�ֽ���
}

void APawnBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime); //����ĳ�ʼ��

	if (TimeCount <= TimelineMax) //ʱ����δ����
	{
		TimeCount += DeltaTime; //ʱ������
		const float Value = FMath::Clamp<float>((TimelineMax - TimeCount) / TimelineMax, 0, 1); //�����ֵϵ������ǰʱ�������ʱ��Ľ��ȣ�
		Difference *= Value; //ʵ��ƽ���ĸı䣬��Сdifference��Ӱ��
	}

	if (bFollow)
	{
		SetActorLocation(FollowPosition + Difference); //���ø��棬��ı��ɫλ��
	}
}

void APawnBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent); //Ϊ��ɫ���������
}

void APawnBase::RunBehaviourTree()
{
	if (APawnAIController* PawnAIController = Cast<APawnAIController>(UAIBlueprintHelperLibrary::GetAIController(this)))
	{ //����ɫ�Ƿ���APawnAIController����
		PawnAIController->RunMyBehaviourTree(); //����ǵĻ�����������Ϊ��
	}
}

void APawnBase::StopBehaviourTree()
{
	if (!GetController()) //����Ƿ���AI������
	{
		UE_LOG(LogTemp, Warning, TEXT("no AI Controller"))
		return;
	}
	if (APawnAIController* PawnAIController = Cast<APawnAIController>(GetController()))
	{ //ת���ɹ����������ɫ��APawnAIController����
		PawnAIController->StopMyBehaviourTree(); //ֹͣ��Ϊ��
	}
}

void APawnBase::SetFollow(bool Follow_) //�����Ƿ����
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
		Difference = GetActorLocation() - FollowPosition; //���㵱ǰλ����Ŀ��λ�õĲ���
		StartInterpTimeline(); //ƽ�����ɲ���
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
	if (AttackMontage) //��������˹�������
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

		WidgetComponent->SetVisibility(false); //����Ļ�������ɫ
	}
}

void APawnBase::SetNavNull(bool bNull) const
{
	if (bNull)
	{
		NavModifierComponent->AreaClass = UNavArea_Null::StaticClass(); //����ͨ��
	}
	else
	{
		NavModifierComponent->AreaClass = UNavArea_Default::StaticClass(); //����ͨ��
	}
}

void APawnBase::OnGetDamage(float Damage)
{
	Health -= Damage * (100 - Defence) / 100; //����˺�
}

void APawnBase::OnBeginCursorOverEvent(UPrimitiveComponent* TouchedComponent)
{
	TArray<UActorComponent*> Components;
	GetComponents(UPrimitiveComponent::StaticClass(), Components); //��ȡ��ɫ��ײ�����

	for (const auto ActorComponent : Components)
	{
		Cast<UPrimitiveComponent>(ActorComponent)->SetRenderCustomDepth(true); //������Ϊ�����Ⱦ
	}
}

void APawnBase::OnEndCursorOverEvent(UPrimitiveComponent* TouchedComponent)
{

	TArray<UActorComponent*> Components;
	GetComponents(UPrimitiveComponent::StaticClass(), Components); //��ȡ��ɫ��ײ�����

	for (const auto ActorComponent : Components)
	{
		Cast<UPrimitiveComponent>(ActorComponent)->SetRenderCustomDepth(false); //��ԭ
	}
}

void APawnBase::OnMeshClickedEvent(UPrimitiveComponent* TouchedComponent, FKey ButtonPressed)
{
	if (ButtonPressed.GetFName().IsEqual(FName(TEXT("LeftMouseButton")))) //���
	{
		AClothoPlayerController* PlayerController = UClothoFunctionLibrary::GetClothoPlayerController(this);
		if (!PlayerController->ControllerHasFocusPiece()) //�����ǰû�п����κ�����
		{
			PlayerController->SetFocusPiece(this); //�����������
		}
	}
	else if (ButtonPressed.GetFName().IsEqual(FName(TEXT("RightMouseButton")))) //�һ�
	{
		UPieceInfoWidget* PieceInfoWidget = UClothoFunctionLibrary::GetPieceInfoWidget(this); //��ȡ��Ϣ����
		PieceInfoWidget->SetPiece(this); //�����ӵ���Ϣ���������
	}
}

void APawnBase::StartInterpTimeline()
{
	TimeCount = 0.f; //���ÿ�ʼʱ��Ϊ0
}

void APawnBase::BindPieceFigure()
{
	FPieceFigureConfig* FigureConfig = UClothoFunctionLibrary::GetPieceInfoManager(this)->
		GetPieceFigureConfigByID(SelfIndex); //�����Լ���������ȡ��Ϣ

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

	GetCharacterMovement()->MaxWalkSpeed = MoveSpeed; //����������Ϣ�ĸ���
}

void APawnBase::OnDeathMontageFinished()
{
	SetActorLocation(FVector(0,0,-1000)); //����λ�õ�����֮��
}

void APawnBase::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const //��������ͬ�����ԣ�ȷ����ҿ�������ͬ
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
	Health = MaxHealth; //����Ѫ
	Magic = 0.f;
	StopBehaviourTree(); //ֹͣ��Ϊ��
}

void APawnBase::SetStateVisible_Implementation(bool Visible)
{
	WidgetComponent->SetVisibility(Visible); //��������ʵ��ͬ���Ŀ��ӻ�
}