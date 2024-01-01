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

	virtual void NativeUpdateAnimation(float DeltaSeconds) override; //执行动画更新

protected:
	UPROPERTY(BlueprintReadOnly)
	float Speed; //速度

	UPROPERTY()
	ADragonCharacter* OwnerDragon; //角色
};
