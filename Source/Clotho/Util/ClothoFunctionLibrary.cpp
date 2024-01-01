// Fill out your copyright notice in the Description page of Project Settings.


#include "ClothoFunctionLibrary.h"

#include "Clotho/ClothoGameInstance.h"
#include "Clotho/ClothoGameMode.h"
#include "Clotho/ClothoGameState.h"
#include "Clotho/ClothoHUD.h"
#include "Clotho/Player/DragonCharacter.h"
#include "Clotho/Widget/Main/MainUI.h"
#include "Kismet/GameplayStatics.h"

UMapWidget* UClothoFunctionLibrary::GetMapWidget(const UObject* WorldContext)
{
	AClothoHUD* ClothoHUD = Cast<AClothoHUD>(UGameplayStatics::GetPlayerController(WorldContext, 0)->GetHUD());// 获取 ClothoHUD，用于获取各种 UI 元素
	return ClothoHUD->GetMainUI()->GetMapWidget();// 获取主 UI，并从中获取地图小部件
}

UGameStateWidget* UClothoFunctionLibrary::GetGameStateWidget(const UObject* WorldContext)
{
	AClothoHUD* ClothoHUD = Cast<AClothoHUD>(UGameplayStatics::GetPlayerController(WorldContext, 0)->GetHUD());
	return ClothoHUD->GetMainUI()->GetGameStateWidget();// 获取主 UI，并从中获取游戏状态小部件
}

ADragonCharacter* UClothoFunctionLibrary::GetDragonCharacter(const UObject* WorldContext)
{
	return Cast<ADragonCharacter>(UGameplayStatics::GetPlayerCharacter(WorldContext, 0));// 获取玩家控制器的龙角色
}

AClothoPlayerController* UClothoFunctionLibrary::GetClothoPlayerController(const UObject* WorldContext)
{
	return Cast<AClothoPlayerController>(UGameplayStatics::GetPlayerController(WorldContext, 0));// 获取 Clotho 玩家控制器
}

UPieceInfoManager* UClothoFunctionLibrary::GetPieceInfoManager(const UObject* WorldContext)
{
	// 获取 ClothoGameInstance 实例
	if (UClothoGameInstance* Instance = Cast<UClothoGameInstance>(WorldContext->GetWorld()->GetGameInstance()))
	{
		return Instance->GetPieceInfoManager();// 获取棋子信息管理器
	}
	return nullptr;
}

EGameState UClothoFunctionLibrary::GetCurrentGameState(const UObject* WorldContext)
{
	return Cast<AClothoGameState>(UGameplayStatics::GetGameState(WorldContext))->GetCurrentGameState();// 获取当前游戏状态
}

UShopWidget* UClothoFunctionLibrary::GetShopWidget(const UObject* WorldContext)
{
	AClothoHUD* ClothoHUD = Cast<AClothoHUD>(UGameplayStatics::GetPlayerController(WorldContext, 0)->GetHUD());
	return ClothoHUD->GetMainUI()->GetShopWidget();// 获取主 UI，并从中获取商店小部件
}

float UClothoFunctionLibrary::GetYawByBoardIndex(int32 Index)
{
	// 根据棋盘索引计算偏航角度
	return (1 - Index) * 90;
}

UPieceInfoWidget* UClothoFunctionLibrary::GetPieceInfoWidget(const UObject* WorldContext)
{
	AClothoHUD* ClothoHUD = Cast<AClothoHUD>(UGameplayStatics::GetPlayerController(WorldContext, 0)->GetHUD());
	return ClothoHUD->GetPieceInfoWidget();// 获取棋子信息小部件
}

int32 UClothoFunctionLibrary::GetPlayerCount(const UObject* WorldContext)
{
	// 获取 ClothoGameMode，用于获取玩家数量和存活玩家数量等信息
	AClothoGameMode* ClothoGameMode = Cast<AClothoGameMode>(WorldContext->GetWorld()->GetAuthGameMode());
	return ClothoGameMode->GetPlayerCount();// 获取玩家数量
}

int32 UClothoFunctionLibrary::GetAlivePlayerCount(const UObject* WorldContext)
{
	AClothoGameMode* ClothoGameMode = Cast<AClothoGameMode>(WorldContext->GetWorld()->GetAuthGameMode());
	return ClothoGameMode->GetAlivePlayerCount();// 获取存活玩家数量
}
