// Fill out your copyright notice in the Description page of Project Settings.


#include "PawnAction_Die.h"

#include "BehaviorTree/BlackboardComponent.h"
#include "Clotho/AI/PawnAIController.h"
#include "Clotho/Pawn/PawnBase.h"

UPawnAction_Die::UPawnAction_Die()
{
	bWantsTick = true;
	TimeCount = 0.f;
	Duration = 0.f;
}

bool UPawnAction_Die::Start()
{
	Super::Start();
	if (APawnBase* Piece = Cast<APawnBase>(GetPawn()))//��ȡ����
	{
		Piece->DoDeath(); //����������ʼ
		Duration = Piece->GetDeathMontageDuration(); //��ȡʱ��
		TimeCount = 0.f;
		return Duration > 0.f;
	}

	Finish(EPawnActionResult::Failed);
	return false;
}

void UPawnAction_Die::Tick(float DeltaTime)
{
	TimeCount += DeltaTime; //ʱ��ı�
	if (TimeCount >= Duration)
	{
		APawnBase* Piece = Cast<APawnBase>(GetPawn());
		Piece->OnDeathMontageFinished(); //��������������Ĳ���
		AController* Controller = Piece->GetController(); //��ȡ������
		if (Controller)
		{
			APawnAIController* PawnAIController = Cast<APawnAIController>(Controller);
			PawnAIController->GetBlackboardComponent()->SetValueAsBool(TEXT("HasDied"),true); //����Ϊ���б������
		}
		
		Finish(EPawnActionResult::Success);
	}

}
