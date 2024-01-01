// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimNotify_Damage.h"

#include "BehaviorTree/BlackboardComponent.h"
#include "Clotho/AI/PawnAIController.h"
#include "Clotho/Pawn/PawnBase.h"

void UAnimNotify_Damage::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::Notify(MeshComp, Animation);

	const APawnBase* SelfActor = Cast<APawnBase>(MeshComp->GetOwner()); //获取角色信息
	if (!SelfActor)
	{
		return;
	}
	AController* Controller = SelfActor->GetController(); //获取角色的控制器
	if (!Controller)
	{
		return;
	}
	
	APawnAIController* AIController = Cast<APawnAIController>(SelfActor->GetController()); //获取AI控制器
	APawnBase* HatedPawn = Cast<APawnBase>(AIController->GetBlackboardComponent()->GetValueAsObject(TEXT("HatedPawn"))); //寻找仇恨对象
	
	if (HatedPawn && HatedPawn->Alive())
	{
		HatedPawn->OnGetDamage(SelfActor->GetAttack()); //对敌人造成伤害
	}
}
