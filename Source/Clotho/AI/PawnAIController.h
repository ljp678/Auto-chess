// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "PawnAIController.generated.h"

/**
 * 
 */
UCLASS()
class CLOTHO_API APawnAIController : public AAIController
{
	GENERATED_BODY()


public:
	void RunMyBehaviourTree(); //启用行为树

	void StopMyBehaviourTree(); //停止行为树
	
};
