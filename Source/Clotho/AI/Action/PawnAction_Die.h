// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actions/PawnAction.h"
#include "PawnAction_Die.generated.h"

/**
 * 
 */
UCLASS()
class CLOTHO_API UPawnAction_Die : public UPawnAction
{
	GENERATED_BODY()

	UPawnAction_Die();

protected:
	virtual bool Start() override; //死亡动画开始

	virtual void Tick(float DeltaTime) override; //逐帧操作

protected:
	float Duration; //持续时间
	float TimeCount; //目前时间
};
