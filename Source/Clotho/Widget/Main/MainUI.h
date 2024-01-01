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
	virtual void AddToScreen(ULocalPlayer* LocalPlayer, int32 ZOrder) override; //将用户界面添加到屏幕上


protected:
	UPROPERTY(meta=(BindWidget))
	UMapWidget* MapWidget; //地图部分的UI

	UPROPERTY(meta=(BindWidget), BlueprintReadWrite)
	UButton* StartButton; //开始按钮

	UPROPERTY(meta=(BindWidget))
	UShopWidget* ShopWidget; //商店部分UI

	UPROPERTY(meta=(BindWidget), BlueprintReadWrite)
	UButton* ToggleButton; //切换按钮

	UPROPERTY(meta=(BindWidget))
	UGameStateWidget* GameStateWidget; //游戏状态的UI
};
