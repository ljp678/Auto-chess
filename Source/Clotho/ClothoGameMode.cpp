// Fill out your copyright notice in the Description page of Project Settings.


#include "ClothoGameMode.h"

#include "ClothoGameState.h"
#include "ClothoPlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "Player/DragonCharacter.h"
#include "Util/ClothoFunctionLibrary.h"

void AClothoGameMode::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);

	PlayerControllers.Add(NewPlayer);// 将新玩家的控制器添加到 PlayerControllers 数组中
}

void AClothoGameMode::PreLogin(const FString& Options, const FString& Address, const FUniqueNetIdRepl& UniqueId, FString& ErrorMessage)
{
	Super::PreLogin(Options, Address, UniqueId, ErrorMessage);
	// 检查玩家数量是否超过限制
	if (NumPlayers > 3)
	{
		ErrorMessage = TEXT("Player Num is More!");
	}
}

void AClothoGameMode::RunOrStopPawnsBehaviourTree()
{
	AClothoGameState* ClothoGameState = Cast<AClothoGameState>(UGameplayStatics::GetGameState(this));

	// 遍历所有玩家控制器
	for (const auto PlayerController : PlayerControllers)
	{
		// 获取玩家控制器关联的龙角色
		if (ADragonCharacter* DragonCharacter = Cast<ADragonCharacter>(PlayerController->GetPawn()))
		{
			// 根据当前游戏状态判断是否运行或停止行为树
			if (ClothoGameState->GetCurrentGameState() == EGameState::Egs_Deploy)
			{
				DragonCharacter->StopPawnsBehaviourTree();
			}
			else if (ClothoGameState->GetCurrentGameState() == EGameState::Egs_Fight)
			{
				DragonCharacter->RunPawnsBehaviourTree();
			}
		}
	}
}

void AClothoGameMode::RefreshShopPiece()
{
	// 遍历所有玩家控制器
	for (auto PlayerController : PlayerControllers)
	{
		AClothoPlayerController* ClothoPlayerController = Cast<AClothoPlayerController>(PlayerController);// 将玩家控制器转换为 ClothoPlayerController 类型
		// 调用玩家控制器的刷新商店棋子和刷新商店 UI 函数
		ClothoPlayerController->RefreshShopPiece();
		ClothoPlayerController->RefreshShopUI();
	}

}

void AClothoGameMode::ToggleState()
{
	GetWorldTimerManager().ClearTimer(ToggleTimer);// 清除计时器

	AClothoGameState* ClothoGameState = Cast<AClothoGameState>(UGameplayStatics::GetGameState(this));// 获取游戏状态对象
	ClothoGameState->Test_ToggleGameState();// 调用游戏状态的测试切换游戏状态函数
	// 根据当前游戏状态执行相应的逻辑
	switch (ClothoGameState->GetCurrentGameState())
	{
	case EGameState::Egs_Deploy:			// 部署阶段逻辑
		SummaryDragon();
		ClothoGameState->CheckAndRefreshSummary();
		RefreshShopPiece();
		StartDeploy();
		StartToggleTimer(15);				// 设置切换计时器
		StartDeployCountDownUI();
		break;
	case EGameState::Egs_Fight:				// 战斗阶段逻辑
		StartFight();
		break;
	default: ;
	}
}
// 绑定网格效果管理器，对每个玩家的角色执行操作
void AClothoGameMode::BindGridEffectManager()
{
	for (const auto PlayerController : PlayerControllers)
	{
		if (ADragonCharacter* DragonCharacter = Cast<ADragonCharacter>(PlayerController->GetPawn()))
		{
			DragonCharacter->BindGridEffectManager();
		}
	}
}
// 获取当前玩家数量
int32 AClothoGameMode::GetPlayerCount() const
{
	return PlayerControllers.Num();
}
// 获取当前存活玩家数量
int32 AClothoGameMode::GetAlivePlayerCount()
{
	int32 Res = 0;
	for (const auto PlayerController : PlayerControllers)
	{
		if (ADragonCharacter* DragonCharacter = Cast<ADragonCharacter>(PlayerController->GetPawn()))
		{
			if (DragonCharacter->Alive())
			{
				++Res;
			}
		}
	}
	return Res;
}

void AClothoGameMode::StartToggleTimer(float Time)
{
	GetWorldTimerManager().SetTimer(ToggleTimer, this, &AClothoGameMode::ToggleState, Time);
}
// 初始化玩家排名的函数
void AClothoGameMode::InitRank()
{
	Rank = GetPlayerCount();// 获取玩家数量，并将其赋值给排名变量
}
// 获取并改变排名的函数
int32 AClothoGameMode::GetAndChangeRank()
{
	// 获取当前排名，并将排名减一
	int32 Res = Rank--;
	// 当排名为1时，调用获胜者并显示UI的函数，同时重置所有状态
	if (Rank == 1)
	{
		GetWinnerAndShowUI();
		ResetAllState();
	}
	
	return Res;
}
// 获取获胜者并显示UI的函数
void AClothoGameMode::GetWinnerAndShowUI()
{
	// 遍历所有玩家控制器
	for (const auto PlayerController : PlayerControllers)
	{
		// 获取玩家控制器关联的龙角色
		if (ADragonCharacter* DragonCharacter = Cast<ADragonCharacter>(PlayerController->GetPawn()))
		{
			// 当龙角色存活时，获取并显示排名UI
			if (DragonCharacter->Alive())
			{
				AClothoPlayerController* ClothoPlayerController = Cast<AClothoPlayerController>(PlayerController);
				ClothoPlayerController->GetAndShowRankUI();
				break;
			}
		}
	}
}

void AClothoGameMode::ResetAllState()
{
	
}
// 启动部署倒计时UI的函数
void AClothoGameMode::StartDeployCountDownUI()
{
	// 遍历所有玩家控制器，调用其启动部署倒计时UI的函数
	for (const auto PlayerController : PlayerControllers)
	{
		AClothoPlayerController* ClothoPlayerController = Cast<AClothoPlayerController>(PlayerController);
		ClothoPlayerController->StartDeployCountDownUI();
	}
}
// 启动战斗倒计时UI的函数
void AClothoGameMode::StartFightCountDownUI()
{
	// 遍历所有玩家控制器，调用其启动战斗倒计时UI的函数
	for (const auto PlayerController : PlayerControllers)
	{
		AClothoPlayerController* ClothoPlayerController = Cast<AClothoPlayerController>(PlayerController);
		ClothoPlayerController->StartFightCountDownUI();
	}
}
// 初始化游戏状态的函数
void AClothoGameMode::InitGameState()
{
	Super::InitGameState();// 调用父类的初始化游戏状态函数
	// 初始化游戏回合配置和相关变量
	InitRoundConfig();
	GameRound = -1;
	OpponentMark.Init(0, 4);
}
// 初始化游戏回合配置的函数
void AClothoGameMode::InitRoundConfig()
{
	// 创建游戏回合配置，这里是一个简单的示例，具体配置内容可能根据游戏需求而定
	FPieceCoor* PieceCoor00 = new FPieceCoor(10, 100);
	FPieceCoor* PieceCoor01 = new FPieceCoor(16, 100, PieceCoor00);
	FPieceCoor* PieceCoor02 = new FPieceCoor(19, 100, PieceCoor01);

	RoundConfig.Add(0, *PieceCoor02);
}
// 启动部署阶段的函数
void AClothoGameMode::StartDeploy()
{
	// 如果存在当前回合的配置，则生成环境棋子
	if (RoundConfig.Contains(++GameRound))
	{
		for (const auto PlayerController : PlayerControllers)
		{
			AClothoPlayerController* ClothoPlayerController = Cast<AClothoPlayerController>(PlayerController);
			ClothoPlayerController->SpawnEnvironmentPieces(RoundConfig[GameRound]);
		}
	}

	OpponentMark.Init(0, 4);
}
// 启动战斗阶段的函数
void AClothoGameMode::StartFight()
{
	// 若当前回合配置不存在，调用匹配对手的函数
	if (!RoundConfig.Contains(GameRound))
	{
		MatchOpponent();
	}

	for (const auto PlayerController : PlayerControllers)
	{
		AClothoPlayerController* ClothoPlayerController = Cast<AClothoPlayerController>(PlayerController);
		if (ADragonCharacter* DragonCharacter = Cast<ADragonCharacter>(PlayerController->GetPawn()))
		{
			// 如果龙角色存活，执行相应逻辑
			if (!DragonCharacter->Alive())
			{
				continue;
			}
			
			int32 PlayerIndex = DragonCharacter->GetPlayerIndex();
			int32 TargetIndex = OpponentMark[PlayerIndex];
			if (TargetIndex == 0)
			{
				DragonCharacter->SetHateIndex(ENVIRONMENT_HATE_INDEX);
			}
			else
			{
				if (TargetIndex > 0)
				{					
					if (TargetIndex >= 10)
					{
						DragonCharacter->SetHateIndex(TargetIndex - 10);
					}else
					{
						DragonCharacter->SetHateIndex(TargetIndex - 1);
						DragonCharacter->GotoOtherBoard(TargetIndex - 1);
					}
				}
				else
				{
					ClothoPlayerController->SpawnPlayerPiecesAsEnvironmentPieces(-TargetIndex-1);
					DragonCharacter->SetHateIndex(ENVIRONMENT_HATE_INDEX);
				}
			}


			DragonCharacter->StartRunBehaviourTreeTimer();
		}
	}
}
// 总结龙角色状态的函数
void AClothoGameMode::SummaryDragon()
{
	AClothoGameState* ClothoGameState = Cast<AClothoGameState>(UGameplayStatics::GetGameState(this));
	TArray<int32> SummaryData = ClothoGameState->GetSummaryData();// 获取游戏状态中的总结数据
	// 遍历所有玩家控制器
	for (auto PlayerController : PlayerControllers)
	{
		if (ADragonCharacter* DragonCharacter = Cast<ADragonCharacter>(PlayerController->GetPawn()))
		{
			// 根据总结数据更新龙角色的状态
			DragonCharacter->ChangeHealth(SummaryData[DragonCharacter->GetPlayerIndex()]);
			DragonCharacter->ClearEnvironmentPiece();
			DragonCharacter->ResetPieces();
			DragonCharacter->SetDragonLocationAndCameraByIndex(DragonCharacter->GetPlayerIndex());
		}
	}
}
// 匹配对手的函数
void AClothoGameMode::MatchOpponent()
{
	int32 Count = GetPlayerCount();
	int32 Offset = GameRound % (Count - 1) + 1;

	UE_LOG(LogTemp, Warning, TEXT("test Match Opponent %d %d"),GameRound,Offset)

	// 遍历所有玩家
	for (int32 i = 0; i < Count; ++i)
	{
		// 如果该玩家已有对手，继续下一轮匹配
		if (OpponentMark[i] != 0)
		{
			continue;
		}

		ADragonCharacter* DragonCharacter = Cast<ADragonCharacter>(PlayerControllers[i]->GetPawn());
		// 如果该玩家已死亡，继续下一轮匹配
		if (!DragonCharacter->Alive())
		{
			continue;
		}
		
		int32 Target = (i + Offset) % Count;
		int32 AliveOffset = 0;
		ADragonCharacter* TargetDragon = Cast<ADragonCharacter>(PlayerControllers[Target]->GetPawn());
		// 寻找存活的对手
		while ((!TargetDragon->Alive()) || (Target == i))
		{
			++AliveOffset;
			Target = (i + Offset + AliveOffset) % Count;
			TargetDragon = Cast<ADragonCharacter>(PlayerControllers[Target]->GetPawn());
		}

		UE_LOG(LogTemp, Warning, TEXT("test Match Opponent in loop %d %d"),i,Target)
		// 根据匹配结果设置对手标记
		if (OpponentMark[Target] == 0)
		{
			OpponentMark[i] = Target + 1;
			OpponentMark[Target] = i + 10;
		}
		else
		{
			OpponentMark[i] = -(Target + 1);
		}
	}
	// 打印匹配结果
	for (int32 i = 0;i<Count;++i)
	{
		UE_LOG(LogTemp, Warning, TEXT("TEST MatchOpponent %d"),OpponentMark[i])
	}
}
