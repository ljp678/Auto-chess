// Fill out your copyright notice in the Description page of Project Settings.


#include "ClothoFunctionLibrary.h"

#include "Clotho/ClothoGameInstance.h"
#include "Clotho/ClothoGameMode.h"
#include "Clotho/ClothoGameState.h"
#include "Clotho/ClothoHUD.h"
#include "Clotho/Player/DragonCharacter.h"
#include "Clotho/Widget/Main/MainUI.h"
#include "Kismet/GameplayStatics.h"

UMapWidget* UClothoFunctionLibrary::GetMapWidget(const UObject* WorldContext)
{
	AClothoHUD* ClothoHUD = Cast<AClothoHUD>(UGameplayStatics::GetPlayerController(WorldContext, 0)->GetHUD());// ��ȡ ClothoHUD�����ڻ�ȡ���� UI Ԫ��
	return ClothoHUD->GetMainUI()->GetMapWidget();// ��ȡ�� UI�������л�ȡ��ͼС����
}

UGameStateWidget* UClothoFunctionLibrary::GetGameStateWidget(const UObject* WorldContext)
{
	AClothoHUD* ClothoHUD = Cast<AClothoHUD>(UGameplayStatics::GetPlayerController(WorldContext, 0)->GetHUD());
	return ClothoHUD->GetMainUI()->GetGameStateWidget();// ��ȡ�� UI�������л�ȡ��Ϸ״̬С����
}

ADragonCharacter* UClothoFunctionLibrary::GetDragonCharacter(const UObject* WorldContext)
{
	return Cast<ADragonCharacter>(UGameplayStatics::GetPlayerCharacter(WorldContext, 0));// ��ȡ��ҿ�����������ɫ
}

AClothoPlayerController* UClothoFunctionLibrary::GetClothoPlayerController(const UObject* WorldContext)
{
	return Cast<AClothoPlayerController>(UGameplayStatics::GetPlayerController(WorldContext, 0));// ��ȡ Clotho ��ҿ�����
}

UPieceInfoManager* UClothoFunctionLibrary::GetPieceInfoManager(const UObject* WorldContext)
{
	// ��ȡ ClothoGameInstance ʵ��
	if (UClothoGameInstance* Instance = Cast<UClothoGameInstance>(WorldContext->GetWorld()->GetGameInstance()))
	{
		return Instance->GetPieceInfoManager();// ��ȡ������Ϣ������
	}
	return nullptr;
}

EGameState UClothoFunctionLibrary::GetCurrentGameState(const UObject* WorldContext)
{
	return Cast<AClothoGameState>(UGameplayStatics::GetGameState(WorldContext))->GetCurrentGameState();// ��ȡ��ǰ��Ϸ״̬
}

UShopWidget* UClothoFunctionLibrary::GetShopWidget(const UObject* WorldContext)
{
	AClothoHUD* ClothoHUD = Cast<AClothoHUD>(UGameplayStatics::GetPlayerController(WorldContext, 0)->GetHUD());
	return ClothoHUD->GetMainUI()->GetShopWidget();// ��ȡ�� UI�������л�ȡ�̵�С����
}

float UClothoFunctionLibrary::GetYawByBoardIndex(int32 Index)
{
	// ����������������ƫ���Ƕ�
	return (1 - Index) * 90;
}

UPieceInfoWidget* UClothoFunctionLibrary::GetPieceInfoWidget(const UObject* WorldContext)
{
	AClothoHUD* ClothoHUD = Cast<AClothoHUD>(UGameplayStatics::GetPlayerController(WorldContext, 0)->GetHUD());
	return ClothoHUD->GetPieceInfoWidget();// ��ȡ������ϢС����
}

int32 UClothoFunctionLibrary::GetPlayerCount(const UObject* WorldContext)
{
	// ��ȡ ClothoGameMode�����ڻ�ȡ��������ʹ�������������Ϣ
	AClothoGameMode* ClothoGameMode = Cast<AClothoGameMode>(WorldContext->GetWorld()->GetAuthGameMode());
	return ClothoGameMode->GetPlayerCount();// ��ȡ�������
}

int32 UClothoFunctionLibrary::GetAlivePlayerCount(const UObject* WorldContext)
{
	AClothoGameMode* ClothoGameMode = Cast<AClothoGameMode>(WorldContext->GetWorld()->GetAuthGameMode());
	return ClothoGameMode->GetAlivePlayerCount();// ��ȡ����������
}
