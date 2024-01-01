// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "ClothoHUD.generated.h"

class UPieceInfoWidget;
class UMainUI;
/**
 * 
 */
UCLASS()
class CLOTHO_API AClothoHUD : public AHUD
{
	GENERATED_BODY()

public:

	UMainUI* GetMainUI();// 获取主界面 UI 的实例

	UPieceInfoWidget* GetPieceInfoWidget();// 获取棋子信息界面 Widget 的实例
	
protected:
	virtual void BeginPlay() override;// 在游戏开始时调用，用于初始化 HUD

protected:
	UPROPERTY(VisibleAnywhere)
	UMainUI* MainUI;// 主界面 UI 实例

	UPROPERTY(VisibleAnywhere)
	UPieceInfoWidget* PieceInfoWidget;
};// 棋子信息界面 Widget 实例
