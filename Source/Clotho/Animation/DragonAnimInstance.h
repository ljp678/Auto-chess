// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "DragonAnimInstance.generated.h"

class ADragonCharacter;
/**
 * 
 */
UCLASS()
class CLOTHO_API UDragonAnimInstance : public UAnimInstance
{
	GENERATED_BODY()


protected:

	virtual void NativeUpdateAnimation(float DeltaSeconds) override; //ִ�ж�������

protected:
	UPROPERTY(BlueprintReadOnly)
	float Speed; //�ٶ�

	UPROPERTY()
	ADragonCharacter* OwnerDragon; //��ɫ
};
