// Fill out your copyright notice in the Description page of Project Settings.


#include "MainUI.h"
#include "MapWidget.h"
#include "ShopWidget.h"
#include "Clotho/ClothoPlayerController.h"
#include "Clotho/Player/DragonCharacter.h"
#include "Clotho/Util/ClothoFunctionLibrary.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"

void UMainUI::AddToScreen(ULocalPlayer* LocalPlayer, int32 ZOrder)
{
	Super::AddToScreen(LocalPlayer, ZOrder);
	MapWidget->InitBorder(); //��ʼ����ͼ���ֵı߽�
	ShopWidget->RefreshShopUI(); //ˢ���̵겿�ֵĽ���

	ADragonCharacter* DragonCharacter = UClothoFunctionLibrary::GetDragonCharacter(this); //��ȡС����
	if (DragonCharacter->GetIsMaster()) //�����ǰ����������ɫ�Ļ�
	{
		StartButton->SetVisibility(ESlateVisibility::Visible); //���ÿ�ʼ��ť�ɼ�
	}
	
}
