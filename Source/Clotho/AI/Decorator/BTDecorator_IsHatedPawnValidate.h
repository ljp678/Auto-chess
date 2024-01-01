// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTDecorator.h"
#include "BTDecorator_IsHatedPawnValidate.generated.h"

/**
 * 
 */
UCLASS()
class CLOTHO_API UBTDecorator_IsHatedPawnValidate : public UBTDecorator
{
	GENERATED_BODY()

	UBTDecorator_IsHatedPawnValidate();
protected:
	//计算逻辑，返回仇恨目标是否有效
	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;

	virtual void InitializeFromAsset(UBehaviorTree& Asset) override; //初始化装饰器

	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override; //处理每帧的逻辑

	bool IsHatedPawnValidate(UBehaviorTreeComponent& OwnerComp) const; //判断仇恨目标是否有效
	
protected:

	UPROPERTY(EditAnywhere)
	FBlackboardKeySelector HatedPawn; //将黑板的Key与仇恨目标关联
};
