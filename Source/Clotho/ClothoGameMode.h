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
	virtual void PostLogin(APlayerController* NewPlayer) override;// ��д PostLogin ����

	virtual void PreLogin(const FString& Options, const FString& Address, const FUniqueNetIdRepl& UniqueId,
	                      FString& ErrorMessage) override;// ��д PreLogin ����

	FORCEINLINE APlayerController* GetPlayerControllerByIndex(int32 Index) { return PlayerControllers[Index]; }// ��ȡָ����������ҿ�����

	void RunOrStopPawnsBehaviourTree();// ���л�ֹͣ������Ϊ��

	void RefreshShopPiece();// ˢ���̵����Ӻ��̵� UI

	void ToggleState();// �л���Ϸ״̬

	void BindGridEffectManager(); // �󶨸���Ч��������

	int32 GetPlayerCount() const;// ��ȡ�������

	int32 GetAlivePlayerCount();// ��ȡ����������
	
	void StartToggleTimer(float Time);// ��ʼ�л���ʱ��

	void InitRank();// ��ʼ������

	int32 GetAndChangeRank(); // ��ȡ���޸�����

	void GetWinnerAndShowUI();// ��ȡ��ʤ�߲���ʾ UI

	void ResetAllState();// ��������״̬

	void StartDeployCountDownUI();// ��ʼ���𵹼�ʱ UI

	void StartFightCountDownUI();// ��ʼս������ʱ UI
protected:

	virtual void InitGameState() override;// ��д��ʼ����Ϸ״̬����

	void InitRoundConfig();// ��ʼ���غ�����

	void StartDeploy();// ��ʼ����׶�

	void StartFight();// ��ʼս���׶�

	void SummaryDragon();// ��������״̬

	void MatchOpponent();// ƥ�����
	
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TArray<APlayerController*> PlayerControllers;// �洢������ҿ����������飬���ڱ༭���в鿴��ֻ�������޸�

	UPROPERTY(VisibleAnywhere,BlueprintReadOnly)
	TMap<int32,FPieceCoor> RoundConfig;// �洢��Ϸ�غ����õ�ӳ�䣬ʹ��int32��Ϊ����FPieceCoor�ṹ����Ϊֵ�����ڱ༭���в鿴��ֻ�������޸�


	UPROPERTY(VisibleAnywhere,BlueprintReadOnly)
	int32 GameRound;// �洢��ǰ��Ϸ�غ��������ڱ༭���в鿴��ֻ�������޸�

	UPROPERTY(VisibleAnywhere,BlueprintReadOnly)
	TArray<int32> OpponentMark;// �洢��Ҷ��ֱ�ǵ����飬���ڱ༭���в鿴��ֻ�������޸�

	FTimerHandle ToggleTimer;// ��ʱ����������ڿ��ƶ�ʱ����

	UPROPERTY(VisibleAnywhere,BlueprintReadOnly)
	int32 Rank;// �洢��ҵ����������ڱ༭���в鿴��ֻ�������޸�
};
