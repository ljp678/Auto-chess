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

	PlayerControllers.Add(NewPlayer);// ������ҵĿ�������ӵ� PlayerControllers ������
}

void AClothoGameMode::PreLogin(const FString& Options, const FString& Address, const FUniqueNetIdRepl& UniqueId, FString& ErrorMessage)
{
	Super::PreLogin(Options, Address, UniqueId, ErrorMessage);
	// �����������Ƿ񳬹�����
	if (NumPlayers > 3)
	{
		ErrorMessage = TEXT("Player Num is More!");
	}
}

void AClothoGameMode::RunOrStopPawnsBehaviourTree()
{
	AClothoGameState* ClothoGameState = Cast<AClothoGameState>(UGameplayStatics::GetGameState(this));

	// ����������ҿ�����
	for (const auto PlayerController : PlayerControllers)
	{
		// ��ȡ��ҿ���������������ɫ
		if (ADragonCharacter* DragonCharacter = Cast<ADragonCharacter>(PlayerController->GetPawn()))
		{
			// ���ݵ�ǰ��Ϸ״̬�ж��Ƿ����л�ֹͣ��Ϊ��
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
	// ����������ҿ�����
	for (auto PlayerController : PlayerControllers)
	{
		AClothoPlayerController* ClothoPlayerController = Cast<AClothoPlayerController>(PlayerController);// ����ҿ�����ת��Ϊ ClothoPlayerController ����
		// ������ҿ�������ˢ���̵����Ӻ�ˢ���̵� UI ����
		ClothoPlayerController->RefreshShopPiece();
		ClothoPlayerController->RefreshShopUI();
	}

}

void AClothoGameMode::ToggleState()
{
	GetWorldTimerManager().ClearTimer(ToggleTimer);// �����ʱ��

	AClothoGameState* ClothoGameState = Cast<AClothoGameState>(UGameplayStatics::GetGameState(this));// ��ȡ��Ϸ״̬����
	ClothoGameState->Test_ToggleGameState();// ������Ϸ״̬�Ĳ����л���Ϸ״̬����
	// ���ݵ�ǰ��Ϸ״ִ̬����Ӧ���߼�
	switch (ClothoGameState->GetCurrentGameState())
	{
	case EGameState::Egs_Deploy:			// ����׶��߼�
		SummaryDragon();
		ClothoGameState->CheckAndRefreshSummary();
		RefreshShopPiece();
		StartDeploy();
		StartToggleTimer(15);				// �����л���ʱ��
		StartDeployCountDownUI();
		break;
	case EGameState::Egs_Fight:				// ս���׶��߼�
		StartFight();
		break;
	default: ;
	}
}
// ������Ч������������ÿ����ҵĽ�ɫִ�в���
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
// ��ȡ��ǰ�������
int32 AClothoGameMode::GetPlayerCount() const
{
	return PlayerControllers.Num();
}
// ��ȡ��ǰ����������
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
// ��ʼ����������ĺ���
void AClothoGameMode::InitRank()
{
	Rank = GetPlayerCount();// ��ȡ��������������丳ֵ����������
}
// ��ȡ���ı������ĺ���
int32 AClothoGameMode::GetAndChangeRank()
{
	// ��ȡ��ǰ����������������һ
	int32 Res = Rank--;
	// ������Ϊ1ʱ�����û�ʤ�߲���ʾUI�ĺ�����ͬʱ��������״̬
	if (Rank == 1)
	{
		GetWinnerAndShowUI();
		ResetAllState();
	}
	
	return Res;
}
// ��ȡ��ʤ�߲���ʾUI�ĺ���
void AClothoGameMode::GetWinnerAndShowUI()
{
	// ����������ҿ�����
	for (const auto PlayerController : PlayerControllers)
	{
		// ��ȡ��ҿ���������������ɫ
		if (ADragonCharacter* DragonCharacter = Cast<ADragonCharacter>(PlayerController->GetPawn()))
		{
			// ������ɫ���ʱ����ȡ����ʾ����UI
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
// �������𵹼�ʱUI�ĺ���
void AClothoGameMode::StartDeployCountDownUI()
{
	// ����������ҿ��������������������𵹼�ʱUI�ĺ���
	for (const auto PlayerController : PlayerControllers)
	{
		AClothoPlayerController* ClothoPlayerController = Cast<AClothoPlayerController>(PlayerController);
		ClothoPlayerController->StartDeployCountDownUI();
	}
}
// ����ս������ʱUI�ĺ���
void AClothoGameMode::StartFightCountDownUI()
{
	// ����������ҿ�����������������ս������ʱUI�ĺ���
	for (const auto PlayerController : PlayerControllers)
	{
		AClothoPlayerController* ClothoPlayerController = Cast<AClothoPlayerController>(PlayerController);
		ClothoPlayerController->StartFightCountDownUI();
	}
}
// ��ʼ����Ϸ״̬�ĺ���
void AClothoGameMode::InitGameState()
{
	Super::InitGameState();// ���ø���ĳ�ʼ����Ϸ״̬����
	// ��ʼ����Ϸ�غ����ú���ر���
	InitRoundConfig();
	GameRound = -1;
	OpponentMark.Init(0, 4);
}
// ��ʼ����Ϸ�غ����õĺ���
void AClothoGameMode::InitRoundConfig()
{
	// ������Ϸ�غ����ã�������һ���򵥵�ʾ���������������ݿ��ܸ�����Ϸ�������
	FPieceCoor* PieceCoor00 = new FPieceCoor(10, 100);
	FPieceCoor* PieceCoor01 = new FPieceCoor(16, 100, PieceCoor00);
	FPieceCoor* PieceCoor02 = new FPieceCoor(19, 100, PieceCoor01);

	RoundConfig.Add(0, *PieceCoor02);
}
// ��������׶εĺ���
void AClothoGameMode::StartDeploy()
{
	// ������ڵ�ǰ�غϵ����ã������ɻ�������
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
// ����ս���׶εĺ���
void AClothoGameMode::StartFight()
{
	// ����ǰ�غ����ò����ڣ�����ƥ����ֵĺ���
	if (!RoundConfig.Contains(GameRound))
	{
		MatchOpponent();
	}

	for (const auto PlayerController : PlayerControllers)
	{
		AClothoPlayerController* ClothoPlayerController = Cast<AClothoPlayerController>(PlayerController);
		if (ADragonCharacter* DragonCharacter = Cast<ADragonCharacter>(PlayerController->GetPawn()))
		{
			// �������ɫ��ִ����Ӧ�߼�
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
// �ܽ�����ɫ״̬�ĺ���
void AClothoGameMode::SummaryDragon()
{
	AClothoGameState* ClothoGameState = Cast<AClothoGameState>(UGameplayStatics::GetGameState(this));
	TArray<int32> SummaryData = ClothoGameState->GetSummaryData();// ��ȡ��Ϸ״̬�е��ܽ�����
	// ����������ҿ�����
	for (auto PlayerController : PlayerControllers)
	{
		if (ADragonCharacter* DragonCharacter = Cast<ADragonCharacter>(PlayerController->GetPawn()))
		{
			// �����ܽ����ݸ�������ɫ��״̬
			DragonCharacter->ChangeHealth(SummaryData[DragonCharacter->GetPlayerIndex()]);
			DragonCharacter->ClearEnvironmentPiece();
			DragonCharacter->ResetPieces();
			DragonCharacter->SetDragonLocationAndCameraByIndex(DragonCharacter->GetPlayerIndex());
		}
	}
}
// ƥ����ֵĺ���
void AClothoGameMode::MatchOpponent()
{
	int32 Count = GetPlayerCount();
	int32 Offset = GameRound % (Count - 1) + 1;

	UE_LOG(LogTemp, Warning, TEXT("test Match Opponent %d %d"),GameRound,Offset)

	// �����������
	for (int32 i = 0; i < Count; ++i)
	{
		// �����������ж��֣�������һ��ƥ��
		if (OpponentMark[i] != 0)
		{
			continue;
		}

		ADragonCharacter* DragonCharacter = Cast<ADragonCharacter>(PlayerControllers[i]->GetPawn());
		// ����������������������һ��ƥ��
		if (!DragonCharacter->Alive())
		{
			continue;
		}
		
		int32 Target = (i + Offset) % Count;
		int32 AliveOffset = 0;
		ADragonCharacter* TargetDragon = Cast<ADragonCharacter>(PlayerControllers[Target]->GetPawn());
		// Ѱ�Ҵ��Ķ���
		while ((!TargetDragon->Alive()) || (Target == i))
		{
			++AliveOffset;
			Target = (i + Offset + AliveOffset) % Count;
			TargetDragon = Cast<ADragonCharacter>(PlayerControllers[Target]->GetPawn());
		}

		UE_LOG(LogTemp, Warning, TEXT("test Match Opponent in loop %d %d"),i,Target)
		// ����ƥ�������ö��ֱ��
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
	// ��ӡƥ����
	for (int32 i = 0;i<Count;++i)
	{
		UE_LOG(LogTemp, Warning, TEXT("TEST MatchOpponent %d"),OpponentMark[i])
	}
}
