// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "ClothoGameMode.generated.h"


USTRUCT(BlueprintType)
struct FPieceCoor
{
	GENERATED_BODY()
	
	int32 Coordinate;
	int32 PieceIndex;
	FPieceCoor* Next;
	FPieceCoor(): Coordinate(-1), PieceIndex(-1), Next(nullptr){}
	FPieceCoor(int32 Coordinate,int32 PieceIndex,FPieceCoor* Next = nullptr)
	{
		this->Coordinate = Coordinate;
		this->PieceIndex = PieceIndex;
		this->Next = Next;
	}
};

/**
 * 
 */
UCLASS()
class CLOTHO_API AClothoGameMode : public AGameMode
{
	GENERATED_BODY()

public:
	virtual void PostLogin(APlayerController* NewPlayer) override;// 重写 PostLogin 函数

	virtual void PreLogin(const FString& Options, const FString& Address, const FUniqueNetIdRepl& UniqueId,
	                      FString& ErrorMessage) override;// 重写 PreLogin 函数

	FORCEINLINE APlayerController* GetPlayerControllerByIndex(int32 Index) { return PlayerControllers[Index]; }// 获取指定索引的玩家控制器

	void RunOrStopPawnsBehaviourTree();// 运行或停止棋子行为树

	void RefreshShopPiece();// 刷新商店棋子和商店 UI

	void ToggleState();// 切换游戏状态

	void BindGridEffectManager(); // 绑定格子效果管理器

	int32 GetPlayerCount() const;// 获取玩家数量

	int32 GetAlivePlayerCount();// 获取存活玩家数量
	
	void StartToggleTimer(float Time);// 开始切换计时器

	void InitRank();// 初始化排名

	int32 GetAndChangeRank(); // 获取并修改排名

	void GetWinnerAndShowUI();// 获取获胜者并显示 UI

	void ResetAllState();// 重置所有状态

	void StartDeployCountDownUI();// 开始部署倒计时 UI

	void StartFightCountDownUI();// 开始战斗倒计时 UI
protected:

	virtual void InitGameState() override;// 重写初始化游戏状态函数

	void InitRoundConfig();// 初始化回合配置

	void StartDeploy();// 开始部署阶段

	void StartFight();// 开始战斗阶段

	void SummaryDragon();// 汇总龙的状态

	void MatchOpponent();// 匹配对手
	
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TArray<APlayerController*> PlayerControllers;// 存储所有玩家控制器的数组，可在编辑器中查看，只读不可修改

	UPROPERTY(VisibleAnywhere,BlueprintReadOnly)
	TMap<int32,FPieceCoor> RoundConfig;// 存储游戏回合配置的映射，使用int32作为键，FPieceCoor结构体作为值，可在编辑器中查看，只读不可修改


	UPROPERTY(VisibleAnywhere,BlueprintReadOnly)
	int32 GameRound;// 存储当前游戏回合数，可在编辑器中查看，只读不可修改

	UPROPERTY(VisibleAnywhere,BlueprintReadOnly)
	TArray<int32> OpponentMark;// 存储玩家对手标记的数组，可在编辑器中查看，只读不可修改

	FTimerHandle ToggleTimer;// 定时器句柄，用于控制定时任务

	UPROPERTY(VisibleAnywhere,BlueprintReadOnly)
	int32 Rank;// 存储玩家的排名，可在编辑器中查看，只读不可修改
};
