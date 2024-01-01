// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTDecorator.h"
#include "BTDecorator_IsDied.generated.h"

/**
 * 
 */
UCLASS()
class CLOTHO_API UBTDecorator_IsDied : public UBTDecorator
{
	GENERATED_BODY()

protected:
	//计算死亡条件是否满足
	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;
	
	virtual void InitializeFromAsset(UBehaviorTree& Asset) override; //初始化装饰器

protected:

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	FBlackboardKeySelector CheckSelfActor; //自身的Blackboard
};
