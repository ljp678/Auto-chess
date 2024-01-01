// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GameStateWidget.generated.h"

/**
 * 
 */
UCLASS()
class CLOTHO_API UGameStateWidget : public UUserWidget
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintImplementableEvent)
	void StartDeployCountDown(); //启动部署倒计时

	UFUNCTION(BlueprintImplementableEvent)
	void StartFightCountDown(); //启动战斗倒计时，均在蓝图中实现。
};
