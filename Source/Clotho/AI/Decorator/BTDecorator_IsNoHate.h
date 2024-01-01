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
	//�����߼������س��ָ���쳣
	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;

	virtual void InitializeFromAsset(UBehaviorTree& Asset) override; //��ʼ��

	
	
protected:

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	FBlackboardKeySelector CheckHateIndex; //���ָ��
	
	
};
