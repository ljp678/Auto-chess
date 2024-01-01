// Fill out your copyright notice in the Description page of Project Settings.


#include "PawnAction_Dance.h"

#include "Clotho/Pawn/PawnBase.h"

UPawnAction_Dance::UPawnAction_Dance()
{
	bWantsTick = true;
	TimeCount = 0.f;
	Duration = 0.f;
}

bool UPawnAction_Dance::Start()
{
	Super::Start();

	if (APawnBase* Piece = Cast<APawnBase>(GetPawn())) //��ȡ����
	{
		Piece->Dance(); //�赸������ʼ
		Duration = Piece->GetDanceMontageDuration(); //��ȡ�赸ʱ��
		TimeCount = 0.f;
	}

	return true;
}

void UPawnAction_Dance::Tick(float DeltaTime)
{
	TimeCount += DeltaTime; //ʱ��ı�
	if (TimeCount >= Duration)
	{
		Finish(EPawnActionResult::Success);
	}
}
