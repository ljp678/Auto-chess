// Fill out your copyright notice in the Description page of Project Settings.


#include "BTDecorator_IsHatedPawnValidate.h"

#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Object.h"
#include "Clotho/Pawn/PawnBase.h"

UBTDecorator_IsHatedPawnValidate::UBTDecorator_IsHatedPawnValidate()
{
	NodeName = TEXT("IsHatedPawnValidate");

	HatedPawn.AddObjectFilter(this,TEXT("HatedPawn"),AActor::StaticClass());

	bNotifyTick = true;
}

bool UBTDecorator_IsHatedPawnValidate::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp,
                                                                  uint8* NodeMemory) const
{
	return IsHatedPawnValidate(OwnerComp); //���س��Ŀ���Ƿ���Ч

}

void UBTDecorator_IsHatedPawnValidate::InitializeFromAsset(UBehaviorTree& Asset)
{
	Super::InitializeFromAsset(Asset); //��ʼ������

	UBlackboardData* Data = GetBlackboardAsset(); //��ȡѡ���ļ�

	if (Data)
	{
		HatedPawn.ResolveSelectedKey(*Data);//����ѡ���ļ�
	}
}

void UBTDecorator_IsHatedPawnValidate::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory,
	float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	if (!IsHatedPawnValidate(OwnerComp))//������Ŀ����Ч
	{
		ConditionalFlowAbort(OwnerComp,EBTDecoratorAbortRequest::ConditionPassing);//�ж�ִ��
	}
}

bool UBTDecorator_IsHatedPawnValidate::IsHatedPawnValidate(UBehaviorTreeComponent& OwnerComp) const
{
	APawnBase* PawnBase = Cast<APawnBase>(OwnerComp.GetBlackboardComponent()->GetValue<UBlackboardKeyType_Object>(HatedPawn.GetSelectedKeyID()));//��ȡ��޶���
	if (!PawnBase)
	{
		return false;
	}

	return PawnBase->Alive(); //�����Ч���򷵻�true
}

