// Fill out your copyright notice in the Description page of Project Settings.


#include "ClothoGameState.h"

#include "ClothoGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "Manager/PieceInfoManager.h"
#include "Net/UnrealNetwork.h"
#include "Player/DragonCharacter.h"
#include "Pawn/PawnBase.h"
#include "Util/ClothoFunctionLibrary.h"

AClothoGameState::AClothoGameState()
{
	Egs = EGameState::Egs_Fight;// 初始化游戏状态为战斗状态

	SummaryArray.Init(100, 4); // 初始化摘要数组，元素数量为4，每个元素初始值为100

	SummaryCount = 0;// 初始化摘要计数为0
}

void AClothoGameState::OnRep_ChangeGameState()
{

}

// 设置游戏状态的网络同步属性
void AClothoGameState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	// 声明Egs属性在网络中进行复制
	DOREPLIFETIME(AClothoGameState, Egs);
}
// 测试函数，用于切换游戏状态
void AClothoGameState::Test_ToggleGameState()
{
	Egs = static_cast<EGameState>((static_cast<int32>(Egs) + 1) % 2);// 测试切换游戏状态，将Egs在EGameState枚举值间循环切换
}
// 根据索引获取空闲的棋子
APawnBase* AClothoGameState::GetFreePieceByIndex(int32 Index)
{
	// 检查环境棋子池是否包含指定索引的棋子
	if (EnvironmentPiecePool.Contains(Index))
	{
		if (EnvironmentPiecePool[Index].Set.Num() > 0)
		{
			auto it = EnvironmentPiecePool[Index].Set.CreateConstIterator();
			APawnBase* Res = *it;
			EnvironmentPiecePool[Index].Set.Remove(*it);
			return Res;
		}
	}
	// 如果环境棋子池不包含指定索引的棋子，根据索引获取棋子数据并生成棋子
	FPieceData* Data = UClothoFunctionLibrary::GetPieceInfoManager(this)->GetPieceDataByID(Index);
	TSubclassOf<APawnBase> PieceClass = Data->PieceClass;

	FTransform Transform;
	APawnBase* Piece = GetWorld()->SpawnActorDeferred<APawnBase>(PieceClass, Transform);
	Piece->SetSelfIndex(Index);
	Piece->FinishSpawning(Transform);
	return Piece;
}
// 根据索引设置空闲的棋子
void AClothoGameState::SetFreePieceByIndex(APawnBase* Piece, int32 Index)
{
	if (EnvironmentPiecePool.Contains(Index))
	{
		EnvironmentPiecePool[Index].Set.Add(Piece);
	}
	else
	{
		FEnvironmentPieceSet* PieceSet = new FEnvironmentPieceSet();
		PieceSet->Set.Add(Piece);
		EnvironmentPiecePool.Add(Index,*PieceSet);
	}
}
// 检查并刷新summary数据
void AClothoGameState::CheckAndRefreshSummary()
{
	CheckSummary();
	RefreshSummary();
}
// 根据玩家索引和数据设置summary数据
void AClothoGameState::SetSummaryData(int32 PlayerIndex, int32 Data)
{
	// 如果summary数据为默认值，则summary计数增加
	if (SummaryArray[PlayerIndex] == SUMMARY_NO_SET)
	{
		++SummaryCount;
	}
	// 设置summary数据
	SummaryArray[PlayerIndex] = Data;
	CheckFightFinish();
}
// 检查summary数据
void AClothoGameState::CheckSummary()
{
	// 逻辑移到gamemode了
}
// 刷新summary数据
void AClothoGameState::RefreshSummary()
{
	int32 Count = UClothoFunctionLibrary::GetPlayerCount(this);
	for (int32 i = 0; i < Count; ++i)
	{
		SummaryArray[i] = 100;
	}

	SummaryCount = 0;
}
// 检查战斗是否结束
void AClothoGameState::CheckFightFinish()
{
	int32 Count = UClothoFunctionLibrary::GetAlivePlayerCount(this);
	UE_LOG(LogTemp, Warning, TEXT("Check Fight Finish %d %d"),SummaryCount,Count)
	if (SummaryCount >= Count)
	{
		// 战斗结束，调用 GameMode 中的相关函数
		AClothoGameMode* GameMode = Cast<AClothoGameMode>(GetWorld()->GetAuthGameMode());
		GameMode->StartToggleTimer(4);
		GameMode->StartFightCountDownUI();
	}
}
