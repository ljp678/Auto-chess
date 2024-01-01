// Fill out your copyright notice in the Description page of Project Settings.


#include "BTDecorator_IsNoHate.h"

#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Int.h"

bool UBTDecorator_IsNoHate::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{

	int32 HateIndex = OwnerComp.GetBlackboardComponent()->GetValue<UBlackboardKeyType_Int>(CheckHateIndex.GetSelectedKeyID());

	return HateIndex < 0;
	
}

void UBTDecorator_IsNoHate::InitializeFromAsset(UBehaviorTree& Asset)
{
	Super::InitializeFromAsset(Asset);//�����ʼ��

	UBlackboardData* BBData = GetBlackboardAsset(); //��ȡ�ڰ�����

	if (BBData)
	{
		CheckHateIndex.ResolveSelectedKey(*BBData);//�����ڰ�key
	}
	
}
