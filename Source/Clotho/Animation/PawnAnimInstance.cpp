// Fill out your copyright notice in the Description page of Project Settings.


#include "PawnAnimInstance.h"

#include "Clotho/Pawn/PawnBase.h"

void UPawnAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	if (!OwningPawn)
	{
		OwningPawn = Cast<APawnBase>(TryGetPawnOwner()); //尝试获取棋子
		return;
	}

	Speed = OwningPawn->GetVelocity().Size2D(); //获取速度信息
}
