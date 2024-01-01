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
	MapWidget->InitBorder(); //初始化地图部分的边界
	ShopWidget->RefreshShopUI(); //刷新商店部分的界面

	ADragonCharacter* DragonCharacter = UClothoFunctionLibrary::GetDragonCharacter(this); //获取小恐龙
	if (DragonCharacter->GetIsMaster()) //如果当前恐龙是主角色的话
	{
		StartButton->SetVisibility(ESlateVisibility::Visible); //设置开始按钮可见
	}
	
}
