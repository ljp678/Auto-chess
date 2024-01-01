// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTaskNode_GetHatedPawn.h"

#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Int.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Object.h"
#include "Clotho/Clotho.h"
#include "Clotho/ClothoGameMode.h"
#include "Clotho/ClothoGameState.h"
#include "Clotho/ClothoPlayerController.h"
#include "Clotho/Pawn/PawnBase.h"
#include "Clotho/Player/DragonCharacter.h"
#include "Clotho/Util/ClothoFunctionLibrary.h"
#include "Kismet/GameplayStatics.h"

UBTTaskNode_GetHatedPawn::UBTTaskNode_GetHatedPawn()
{
	NodeName = TEXT("Find An antagonistic Pawn");

	HatedIndexKey.AddIntFilter(this,TEXT("HatedIndexKey"));
	OwnerIndexKey.AddIntFilter(this,TEXT("OwnerIndexKey"));
	HatedPawnKey.AddObjectFilter(this,TEXT("HatedPawnKey"), AActor::StaticClass());
	SelfActorKey.AddObjectFilter(this,TEXT("SelfActorKey"),AActor::StaticClass());
}

EBTNodeResult::Type UBTTaskNode_GetHatedPawn::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AClothoGameMode* ClothoGameMode = Cast<AClothoGameMode>(GetWorld()->GetAuthGameMode()); //获取游戏模式
	if (!ClothoGameMode)
	{
		UE_LOG(LogTemp, Warning, TEXT("No Game Mode"))
		return EBTNodeResult::Failed;
	}

	int32 HatedIndex = OwnerComp.GetBlackboardComponent()->GetValue<UBlackboardKeyType_Int>(
		HatedIndexKey.GetSelectedKeyID()); //获取仇恨值
	int32 OwnerIndex = OwnerComp.GetBlackboardComponent()->GetValue<UBlackboardKeyType_Int>(OwnerIndexKey.GetSelectedKeyID()); //获取玩家索引


	
	int32 ControllerIndex = (HatedIndex == ENVIRONMENT_HATE_INDEX) ? OwnerIndex : HatedIndex; //根据仇恨值选择控制器


	APlayerController* PlayerController = ClothoGameMode->GetPlayerControllerByIndex(ControllerIndex); //获取玩家控制器
	ADragonCharacter* DragonCharacter = Cast<ADragonCharacter>(PlayerController->GetPawn()); //获取小龙
	if (!DragonCharacter)
	{
		UE_LOG(LogTemp, Warning, TEXT("No Dragon Character"))
		return EBTNodeResult::Failed;
	}
	
	APawnBase* HatedPawn; //仇恨目标
	APawnBase* SelfActor = Cast<APawnBase>(OwnerComp.GetBlackboardComponent()->GetValue<UBlackboardKeyType_Object>(SelfActorKey.GetSelectedKeyID()));//根据索引寻找角色
	if (HatedIndex == ENVIRONMENT_HATE_INDEX)
	{
		HatedPawn = DragonCharacter->GetValidateEnvironmentPieceInBoard(SelfActor); //选取环境的仇恨对象
	}
	else
	{
		HatedPawn = DragonCharacter->GetValidatePawnInBoard(SelfActor); //根据棋子选取仇恨对象
	}
	if (HatedPawn) //如果找到了仇恨对象
	{
		OwnerComp.GetBlackboardComponent()->SetValue<UBlackboardKeyType_Object>(
			HatedPawnKey.GetSelectedKeyID(), HatedPawn); //更新黑板的值
		return EBTNodeResult::Succeeded;
	}


	OwnerComp.GetBlackboardComponent()->SetValue<UBlackboardKeyType_Int>(HatedIndexKey.GetSelectedKeyID(), -1); //未找到，则设为异常值

	// Set Summary Data
	AClothoGameState* ClothoGameState = Cast<AClothoGameState>(UGameplayStatics::GetGameState(this)); //获取游戏状态
	ClothoGameState->SetSummaryData(OwnerIndex,0); //玩家索引设置为0
	
	//may has a bug here? 
	if (HatedIndex != ENVIRONMENT_HATE_INDEX) //如果不是环境索引
	{
		ClothoGameState->SetSummaryData(HatedIndex,-40); //设置为-40
	}


	
	return EBTNodeResult::Succeeded;
}

void UBTTaskNode_GetHatedPawn::InitializeFromAsset(UBehaviorTree& Asset)
{
	Super::InitializeFromAsset(Asset);

	UBlackboardData* BBData = GetBlackboardAsset(); //获取数据

	if (BBData)
	{
		HatedIndexKey.ResolveSelectedKey(*BBData); //解析
		HatedPawnKey.ResolveSelectedKey(*BBData);
		OwnerIndexKey.ResolveSelectedKey(*BBData);
		SelfActorKey.ResolveSelectedKey(*BBData);
	}
}
