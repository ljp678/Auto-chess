// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "PawnAnimInstance.generated.h"

class APawnBase;
/**
 * 
 */
UCLASS()
class CLOTHO_API UPawnAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

protected:
	virtual void NativeUpdateAnimation(float DeltaSeconds) override; //ִ�ж�������

protected:

	UPROPERTY(BlueprintReadOnly)
	float Speed; //��ɫ�ٶ�

	UPROPERTY()
	APawnBase* OwningPawn; //���ʽ�ɫ��Ϣ
};
