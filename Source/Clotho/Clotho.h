// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

// 蓝图可用的游戏状态枚举
UENUM(BlueprintType)
enum class EGameState : uint8
{
	Egs_Deploy=0,// 游戏状态：部署
	Egs_Fight // 游戏状态：战斗
};
// 定义碰撞通道的宏
#define COLLISION_GRID ECC_GameTraceChannel4

#define ENVIRONMENT_HATE_INDEX 10	// 环境仇恨索引的宏，表示特定环境的敌对程度
#define SUMMARY_NO_SET 100	// 用于表示未设置的summary编号的宏，值为100，summary编号为100时表示没有进行设置