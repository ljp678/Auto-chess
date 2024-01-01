// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTaskNode_GetHatedPawn.generated.h"

/**
 * 
 */
UCLASS()
class CLOTHO_API UBTTaskNode_GetHatedPawn : public UBTTaskNode
{
	GENERATED_BODY()

	UBTTaskNode_GetHatedPawn();

protected:

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

	virtual void InitializeFromAsset(UBehaviorTree& Asset) override;


protected:
	UPROPERTY(EditAnywhere)
	FBlackboardKeySelector HatedIndexKey;
	UPROPERTY(EditAnywhere)
	FBlackboardKeySelector HatedPawnKey;
	UPROPERTY(EditAnywhere)
	FBlackboardKeySelector OwnerIndexKey;
	UPROPERTY(EditAnywhere)
	FBlackboardKeySelector SelfActorKey;
};