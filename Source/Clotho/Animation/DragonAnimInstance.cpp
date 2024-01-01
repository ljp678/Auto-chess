// Fill out your copyright notice in the Description page of Project Settings.


#include "DragonAnimInstance.h"

#include "Clotho/Player/DragonCharacter.h"
#include "Net/UnrealNetwork.h"

void UDragonAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	if (!OwnerDragon)
	{
		OwnerDragon = Cast<ADragonCharacter>(TryGetPawnOwner()); //���Ի�ȡ��ɫ
		return;
	}

	Speed = OwnerDragon->GetVelocity().Size2D(); //��ȡ�ٶ���Ϣ
}
