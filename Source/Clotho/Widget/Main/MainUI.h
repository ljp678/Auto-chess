// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameStateWidget.h"
#include "Blueprint/UserWidget.h"
#include "MainUI.generated.h"

class UPieceInfoWidget;
class UShopWidget;
class UButton;
class UMapWidget;
/**
 * 
 */
UCLASS()
class CLOTHO_API UMainUI : public UUserWidget
{
	GENERATED_BODY()

public:
	FORCEINLINE UMapWidget* GetMapWidget() const { return MapWidget; }

	FORCEINLINE UShopWidget* GetShopWidget() const { return ShopWidget; }

	FORCEINLINE UGameStateWidget* GetGameStateWidget() const { return GameStateWidget; }

protected:
	virtual void AddToScreen(ULocalPlayer* LocalPlayer, int32 ZOrder) override; //���û�������ӵ���Ļ��


protected:
	UPROPERTY(meta=(BindWidget))
	UMapWidget* MapWidget; //��ͼ���ֵ�UI

	UPROPERTY(meta=(BindWidget), BlueprintReadWrite)
	UButton* StartButton; //��ʼ��ť

	UPROPERTY(meta=(BindWidget))
	UShopWidget* ShopWidget; //�̵겿��UI

	UPROPERTY(meta=(BindWidget), BlueprintReadWrite)
	UButton* ToggleButton; //�л���ť

	UPROPERTY(meta=(BindWidget))
	UGameStateWidget* GameStateWidget; //��Ϸ״̬��UI
};
