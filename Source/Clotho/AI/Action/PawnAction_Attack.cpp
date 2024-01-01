// Fill out your copyright notice in the Description page of Project Settings.


#include "PawnAction_Attack.h"

#include "Clotho/Pawn/PawnBase.h"

UPawnAction_Attack::UPawnAction_Attack()
{
	bWantsTick = true;
	TimeCount = 0.f;
	Duration = 0.f;
}

bool UPawnAction_Attack::Start()
{
	Super::Start(); //�����ʼ��
	if (APawnBase* Piece = Cast<APawnBase>(GetPawn())) //��ȡ����
	{
		Piece->DoAttack(); //���й���
		Duration = Piece->GetAttackMontageDuration(); //��ȡ��������ʱ��
		TimeCount = 0.f; //��ʼ��Ŀǰ�Ĺ���ʱ��
		return Duration > 0.f;
	}

	Finish(EPawnActionResult::Failed);//����ִ��ʧ��
	return false;
}

void UPawnAction_Attack::Tick(float DeltaTime)
{
	TimeCount += DeltaTime; //ʱ�����ӣ���������ͼʵ��
	if (TimeCount >= Duration)
	{
		Finish(EPawnActionResult::Success); //��������
	}
}
