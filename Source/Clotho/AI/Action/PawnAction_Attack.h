// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actions/PawnAction.h"
#include "PawnAction_Attack.generated.h"

/**
 * 
 */
UCLASS()
class CLOTHO_API UPawnAction_Attack : public UPawnAction
{
	GENERATED_BODY()

	UPawnAction_Attack();
	
protected:
	virtual bool Start() override; //攻击行为开始的操作

	virtual void Tick(float DeltaTime) override; //每帧的攻击操作


protected:
	float Duration; //攻击的持续时间
	float TimeCount; //攻击已经进行的时间
};
