// Fill out your copyright notice in the Description page of Project Settings.


#include "BTDecorator_IsDied.h"

#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Object.h"
#include "Clotho/Pawn/PawnBase.h"

bool UBTDecorator_IsDied::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	//��ȡ����Acotr
	APawnBase* SelfActor = Cast<APawnBase>(OwnerComp.GetBlackboardComponent()->GetValue<UBlackboardKeyType_Object>(CheckSelfActor.GetSelectedKeyID()));
	//����Ƿ�����
	return SelfActor->GetHealth() <= 0;
	
}

void UBTDecorator_IsDied::InitializeFromAsset(UBehaviorTree& Asset)
{
	Super::InitializeFromAsset(Asset); //��ʼ������

	UBlackboardData* BBData = GetBlackboardAsset(); //��ȡ�ڰ�����

	if (BBData)
	{
		CheckSelfActor.ResolveSelectedKey(*BBData); //�����ڰ��Key������Ľ�ɫ
	}
}
