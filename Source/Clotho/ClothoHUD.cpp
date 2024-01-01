// Fill out your copyright notice in the Description page of Project Settings.


#include "ClothoHUD.h"

#include "Widget/Main/MainUI.h"
#include "Widget/Main/PieceInfoWidget.h"
// 获取主界面 UI 的实例
UMainUI* AClothoHUD::GetMainUI()
{
	if (!MainUI)
	{
		// 通过类路径加载主界面 UI 类
		const TSubclassOf<UMainUI> MainUIClass = LoadClass<UMainUI>(
			this,TEXT("WidgetBlueprint'/Game/Clotho/UI/Main/UMG_MainUI.UMG_MainUI_C'"));

		MainUI = CreateWidget<UMainUI>(GetOwningPlayerController(), MainUIClass);// 创建主界面 UI 的实例并保存
	}
	return MainUI;
}
// 获取棋子信息界面 Widget 的实例
UPieceInfoWidget* AClothoHUD::GetPieceInfoWidget()
{
	if (!PieceInfoWidget)
	{
		// 通过类路径加载棋子信息界面 Widget 类
		const TSubclassOf<UPieceInfoWidget> PieceInfoClass = LoadClass<UPieceInfoWidget>(
			this,TEXT("WidgetBlueprint'/Game/Clotho/UI/Main/UMG_PieceInfo.UMG_PieceInfo_C'"));
		// 创建棋子信息界面 Widget 的实例并保存
		PieceInfoWidget = CreateWidget<UPieceInfoWidget>(GetOwningPlayerController(), PieceInfoClass);
	}
	return PieceInfoWidget;
}
// 在开始播放时调用，用于初始化 HUD
void AClothoHUD::BeginPlay()
{
	Super::BeginPlay();
	
	GetMainUI()->AddToViewport();// 将主界面 UI 添加到视口
	GetPieceInfoWidget()->AddToViewport();// 将棋子信息界面 Widget 添加到视口
	GetPieceInfoWidget()->SetActivate(false);// 设置棋子信息界面 Widget 为不激活状态
}
