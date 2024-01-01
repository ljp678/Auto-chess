// Fill out your copyright notice in the Description page of Project Settings.


#include "ClothoHUD.h"

#include "Widget/Main/MainUI.h"
#include "Widget/Main/PieceInfoWidget.h"
// ��ȡ������ UI ��ʵ��
UMainUI* AClothoHUD::GetMainUI()
{
	if (!MainUI)
	{
		// ͨ����·������������ UI ��
		const TSubclassOf<UMainUI> MainUIClass = LoadClass<UMainUI>(
			this,TEXT("WidgetBlueprint'/Game/Clotho/UI/Main/UMG_MainUI.UMG_MainUI_C'"));

		MainUI = CreateWidget<UMainUI>(GetOwningPlayerController(), MainUIClass);// ���������� UI ��ʵ��������
	}
	return MainUI;
}
// ��ȡ������Ϣ���� Widget ��ʵ��
UPieceInfoWidget* AClothoHUD::GetPieceInfoWidget()
{
	if (!PieceInfoWidget)
	{
		// ͨ����·������������Ϣ���� Widget ��
		const TSubclassOf<UPieceInfoWidget> PieceInfoClass = LoadClass<UPieceInfoWidget>(
			this,TEXT("WidgetBlueprint'/Game/Clotho/UI/Main/UMG_PieceInfo.UMG_PieceInfo_C'"));
		// ����������Ϣ���� Widget ��ʵ��������
		PieceInfoWidget = CreateWidget<UPieceInfoWidget>(GetOwningPlayerController(), PieceInfoClass);
	}
	return PieceInfoWidget;
}
// �ڿ�ʼ����ʱ���ã����ڳ�ʼ�� HUD
void AClothoHUD::BeginPlay()
{
	Super::BeginPlay();
	
	GetMainUI()->AddToViewport();// �������� UI ��ӵ��ӿ�
	GetPieceInfoWidget()->AddToViewport();// ��������Ϣ���� Widget ��ӵ��ӿ�
	GetPieceInfoWidget()->SetActivate(false);// ����������Ϣ���� Widget Ϊ������״̬
}
