// Fill out your copyright notice in the Description page of Project Settings.


#include "BTDecorator_IsDied.h"

#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Object.h"
#include "Clotho/Pawn/PawnBase.h"

bool UBTDecorator_IsDied::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	//获取自身Acotr
	APawnBase* SelfActor = Cast<APawnBase>(OwnerComp.GetBlackboardComponent()->GetValue<UBlackboardKeyType_Object>(CheckSelfActor.GetSelectedKeyID()));
	//检查是否死亡
	return SelfActor->GetHealth() <= 0;
	
}

void UBTDecorator_IsDied::InitializeFromAsset(UBehaviorTree& Asset)
{
	Super::InitializeFromAsset(Asset); //初始化基类

	UBlackboardData* BBData = GetBlackboardAsset(); //获取黑板数据

	if (BBData)
	{
		CheckSelfActor.ResolveSelectedKey(*BBData); //关联黑板的Key和自身的角色
	}
}
