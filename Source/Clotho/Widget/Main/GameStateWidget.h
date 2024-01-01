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
	void StartDeployCountDown(); //�������𵹼�ʱ

	UFUNCTION(BlueprintImplementableEvent)
	void StartFightCountDown(); //����ս������ʱ��������ͼ��ʵ�֡�
};
