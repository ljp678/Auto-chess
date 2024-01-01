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
	//�����߼������س��Ŀ���Ƿ���Ч
	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;

	virtual void InitializeFromAsset(UBehaviorTree& Asset) override; //��ʼ��װ����

	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override; //����ÿ֡���߼�

	bool IsHatedPawnValidate(UBehaviorTreeComponent& OwnerComp) const; //�жϳ��Ŀ���Ƿ���Ч
	
protected:

	UPROPERTY(EditAnywhere)
	FBlackboardKeySelector HatedPawn; //���ڰ��Key����Ŀ�����
};
