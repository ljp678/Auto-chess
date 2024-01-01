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
 * һ�����ߺ����⣬�������ڴ���ͬ��Ϸ���ܵľ�̬����
 */
UCLASS()
class CLOTHO_API UClothoFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	static UMapWidget* GetMapWidget(const UObject* WorldContext);// ��ȡ��ͼС����

	static UGameStateWidget* GetGameStateWidget(const UObject* WorldContext);// ��ȡ��Ϸ״̬С����

	static ADragonCharacter* GetDragonCharacter(const UObject* WorldContext);// ��ȡ����ɫ

	static AClothoPlayerController* GetClothoPlayerController(const UObject* WorldContext);// ��ȡ Clotho ��ҿ�����

	static UPieceInfoManager* GetPieceInfoManager(const UObject* WorldContext);// ��ȡ������Ϣ������

	static EGameState GetCurrentGameState(const UObject* WorldContext);// ��ȡ��ǰ��Ϸ״̬

	static UShopWidget* GetShopWidget(const UObject* WorldContext);// ��ȡ�̵�С����

	static float GetYawByBoardIndex(int32 Index);// ��������������ȡƫ���Ƕ�

	static UPieceInfoWidget* GetPieceInfoWidget(const UObject* WorldContext);// ��ȡ������ϢС����

	static int32 GetPlayerCount(const UObject* WorldContext);// ��ȡ�������

	static int32 GetAlivePlayerCount(const UObject* WorldContext);// ��ȡ����������
};
