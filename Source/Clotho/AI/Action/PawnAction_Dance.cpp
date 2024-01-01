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

	if (APawnBase* Piece = Cast<APawnBase>(GetPawn())) //获取棋子
	{
		Piece->Dance(); //舞蹈操作开始
		Duration = Piece->GetDanceMontageDuration(); //获取舞蹈时间
		TimeCount = 0.f;
	}

	return true;
}

void UPawnAction_Dance::Tick(float DeltaTime)
{
	TimeCount += DeltaTime; //时间改变
	if (TimeCount >= Duration)
	{
		Finish(EPawnActionResult::Success);
	}
}
