// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimNotify_Damage.h"

#include "BehaviorTree/BlackboardComponent.h"
#include "Clotho/AI/PawnAIController.h"
#include "Clotho/Pawn/PawnBase.h"

void UAnimNotify_Damage::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::Notify(MeshComp, Animation);

	const APawnBase* SelfActor = Cast<APawnBase>(MeshComp->GetOwner()); //��ȡ��ɫ��Ϣ
	if (!SelfActor)
	{
		return;
	}
	AController* Controller = SelfActor->GetController(); //��ȡ��ɫ�Ŀ�����
	if (!Controller)
	{
		return;
	}
	
	APawnAIController* AIController = Cast<APawnAIController>(SelfActor->GetController()); //��ȡAI������
	APawnBase* HatedPawn = Cast<APawnBase>(AIController->GetBlackboardComponent()->GetValueAsObject(TEXT("HatedPawn"))); //Ѱ�ҳ�޶���
	
	if (HatedPawn && HatedPawn->Alive())
	{
		HatedPawn->OnGetDamage(SelfActor->GetAttack()); //�Ե�������˺�
	}
}
