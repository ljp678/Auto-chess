// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTDecorator.h"
#include "BTDecorator_IsNoHate.generated.h"

/**
 * 
 */
UCLASS()
class CLOTHO_API UBTDecorator_IsNoHate : public UBTDecorator
{
	GENERATED_BODY()

protected:
	//计算逻辑，返回仇恨指数异常
	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;

	virtual void InitializeFromAsset(UBehaviorTree& Asset) override; //初始化

	
	
protected:

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	FBlackboardKeySelector CheckHateIndex; //仇恨指数
	
	
};
