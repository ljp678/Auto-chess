// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Clotho.h"
#include "GameFramework/GameState.h"
#include "ClothoGameState.generated.h"

// 结构体，用于表示环境棋子的集合
class APawnBase;

USTRUCT(BlueprintType)
struct FEnvironmentPieceSet
{
	GENERATED_BODY()
	TSet<APawnBase*> Set;// 存储环境棋子的集合
};

/**
 * 
 */
UCLASS()
class CLOTHO_API AClothoGameState : public AGameState
{
	GENERATED_BODY()

	AClothoGameState();

protected:
	UFUNCTION()
	void OnRep_ChangeGameState();// 用于在游戏状态改变时进行复制

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;// 设置网络同步属性

	void CheckSummary();// 检查summary

	void RefreshSummary();// 刷新summary

	void CheckFightFinish();// 检查战斗是否结束

public:
	UFUNCTION(Exec)
	void Test_ToggleGameState();// 用于测试切换游戏状态

	FORCEINLINE EGameState GetCurrentGameState() const { return Egs; }// 获取当前游戏状态

	APawnBase* GetFreePieceByIndex(int32 Index); // 根据索引获取空闲的棋子

	void SetFreePieceByIndex(APawnBase* Piece,int32 Index);// 根据索引设置空闲的棋子

	void CheckAndRefreshSummary();// 检查并刷新summary数据

	void SetSummaryData(int32 PlayerIndex,int32 Data);// 设置summary数据

	FORCEINLINE TArray<int32> GetSummaryData() const {return SummaryArray;}// 获取summary数据数组

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, ReplicatedUsing=OnRep_ChangeGameState)
	EGameState Egs;// 当前游戏状态

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TMap<int32, FEnvironmentPieceSet> EnvironmentPiecePool;// 存储环境棋子的池

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TArray<int32> SummaryArray;// 存储summary数据的数组

	int32 SummaryCount;
};// summary计数
