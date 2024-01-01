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
	virtual void NativeUpdateAnimation(float DeltaSeconds) override; //执行动画更新

protected:

	UPROPERTY(BlueprintReadOnly)
	float Speed; //角色速度

	UPROPERTY()
	APawnBase* OwningPawn; //访问角色信息
};
