// Fill out your copyright notice in the Description page of Project Settings.


#include "PawnAIController.h"

#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Clotho/Pawn/PawnBase.h"
#include "Kismet/GameplayStatics.h"

void APawnAIController::RunMyBehaviourTree()
{
	if (APawnBase* PawnBase = Cast<APawnBase>(GetPawn())) //��ȡ��ɫ
	{
		RunBehaviorTree(PawnBase->GetBehaviorTree()); //������Ϊ��
		GetBlackboardComponent()->SetValueAsInt(TEXT("HatedIndex"), PawnBase->GetHateIndex());
		GetBlackboardComponent()->SetValueAsInt(TEXT("OwnerIndex"),PawnBase->GetOwnerIndex());
		GetBlackboardComponent()->SetValueAsBool(TEXT("HasDied"),false);
		GetBlackboardComponent()->SetValueAsObject(TEXT("SelfActor"), PawnBase);
		GetBlackboardComponent()->SetValueAsObject(TEXT("HatedPawn"),nullptr); //������������ڰ����
	}
}

void APawnAIController::StopMyBehaviourTree()
{
	if (UBehaviorTreeComponent* BTComp = Cast<UBehaviorTreeComponent>(BrainComponent))
	{
		BTComp->StopTree(); //ֹͣ��Ϊ��
	}
}
