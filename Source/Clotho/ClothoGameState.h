// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Clotho.h"
#include "GameFramework/GameState.h"
#include "ClothoGameState.generated.h"

// �ṹ�壬���ڱ�ʾ�������ӵļ���
class APawnBase;

USTRUCT(BlueprintType)
struct FEnvironmentPieceSet
{
	GENERATED_BODY()
	TSet<APawnBase*> Set;// �洢�������ӵļ���
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
	void OnRep_ChangeGameState();// ��������Ϸ״̬�ı�ʱ���и���

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;// ��������ͬ������

	void CheckSummary();// ���summary

	void RefreshSummary();// ˢ��summary

	void CheckFightFinish();// ���ս���Ƿ����

public:
	UFUNCTION(Exec)
	void Test_ToggleGameState();// ���ڲ����л���Ϸ״̬

	FORCEINLINE EGameState GetCurrentGameState() const { return Egs; }// ��ȡ��ǰ��Ϸ״̬

	APawnBase* GetFreePieceByIndex(int32 Index); // ����������ȡ���е�����

	void SetFreePieceByIndex(APawnBase* Piece,int32 Index);// �����������ÿ��е�����

	void CheckAndRefreshSummary();// ��鲢ˢ��summary����

	void SetSummaryData(int32 PlayerIndex,int32 Data);// ����summary����

	FORCEINLINE TArray<int32> GetSummaryData() const {return SummaryArray;}// ��ȡsummary��������

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, ReplicatedUsing=OnRep_ChangeGameState)
	EGameState Egs;// ��ǰ��Ϸ״̬

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TMap<int32, FEnvironmentPieceSet> EnvironmentPiecePool;// �洢�������ӵĳ�

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TArray<int32> SummaryArray;// �洢summary���ݵ�����

	int32 SummaryCount;
};// summary����
