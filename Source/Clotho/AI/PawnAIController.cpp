// Fill out your copyright notice in the Description page of Project Settings.


#include "PawnAIController.h"

#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Clotho/Pawn/PawnBase.h"
#include "Kismet/GameplayStatics.h"

void APawnAIController::RunMyBehaviourTree()
{
	if (APawnBase* PawnBase = Cast<APawnBase>(GetPawn())) //获取角色
	{
		RunBehaviorTree(PawnBase->GetBehaviorTree()); //启动行为树
		GetBlackboardComponent()->SetValueAsInt(TEXT("HatedIndex"), PawnBase->GetHateIndex());
		GetBlackboardComponent()->SetValueAsInt(TEXT("OwnerIndex"),PawnBase->GetOwnerIndex());
		GetBlackboardComponent()->SetValueAsBool(TEXT("HasDied"),false);
		GetBlackboardComponent()->SetValueAsObject(TEXT("SelfActor"), PawnBase);
		GetBlackboardComponent()->SetValueAsObject(TEXT("HatedPawn"),nullptr); //将内容添加至黑板组件
	}
}

void APawnAIController::StopMyBehaviourTree()
{
	if (UBehaviorTreeComponent* BTComp = Cast<UBehaviorTreeComponent>(BrainComponent))
	{
		BTComp->StopTree(); //停止行为树
	}
}
