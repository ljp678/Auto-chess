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
	return IsHatedPawnValidate(OwnerComp); //返回仇恨目标是否有效

}

void UBTDecorator_IsHatedPawnValidate::InitializeFromAsset(UBehaviorTree& Asset)
{
	Super::InitializeFromAsset(Asset); //初始化父类

	UBlackboardData* Data = GetBlackboardAsset(); //获取选定的键

	if (Data)
	{
		HatedPawn.ResolveSelectedKey(*Data);//解析选定的键
	}
}

void UBTDecorator_IsHatedPawnValidate::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory,
	float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	if (!IsHatedPawnValidate(OwnerComp))//如果仇恨目标无效
	{
		ConditionalFlowAbort(OwnerComp,EBTDecoratorAbortRequest::ConditionPassing);//中断执行
	}
}

bool UBTDecorator_IsHatedPawnValidate::IsHatedPawnValidate(UBehaviorTreeComponent& OwnerComp) const
{
	APawnBase* PawnBase = Cast<APawnBase>(OwnerComp.GetBlackboardComponent()->GetValue<UBlackboardKeyType_Object>(HatedPawn.GetSelectedKeyID()));//获取仇恨对象
	if (!PawnBase)
	{
		return false;
	}

	return PawnBase->Alive(); //如果有效，则返回true
}

