// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Clotho/ClothoPlayerController.h"
#include "Clotho/Widget/Main/GameStateWidget.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "ClothoFunctionLibrary.generated.h"

class UPieceInfoWidget;
class UShopWidget;
enum class EGameState : uint8;
class UPieceInfoManager;
class ADragonCharacter;
class UMapWidget;
/**
 * 一个工具函数库，包含用于处理不同游戏功能的静态函数
 */
UCLASS()
class CLOTHO_API UClothoFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	static UMapWidget* GetMapWidget(const UObject* WorldContext);// 获取地图小部件

	static UGameStateWidget* GetGameStateWidget(const UObject* WorldContext);// 获取游戏状态小部件

	static ADragonCharacter* GetDragonCharacter(const UObject* WorldContext);// 获取龙角色

	static AClothoPlayerController* GetClothoPlayerController(const UObject* WorldContext);// 获取 Clotho 玩家控制器

	static UPieceInfoManager* GetPieceInfoManager(const UObject* WorldContext);// 获取棋子信息管理器

	static EGameState GetCurrentGameState(const UObject* WorldContext);// 获取当前游戏状态

	static UShopWidget* GetShopWidget(const UObject* WorldContext);// 获取商店小部件

	static float GetYawByBoardIndex(int32 Index);// 根据棋盘索引获取偏航角度

	static UPieceInfoWidget* GetPieceInfoWidget(const UObject* WorldContext);// 获取棋子信息小部件

	static int32 GetPlayerCount(const UObject* WorldContext);// 获取玩家数量

	static int32 GetAlivePlayerCount(const UObject* WorldContext);// 获取存活玩家数量
};
