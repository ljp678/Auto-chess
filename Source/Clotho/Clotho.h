// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

// ��ͼ���õ���Ϸ״̬ö��
UENUM(BlueprintType)
enum class EGameState : uint8
{
	Egs_Deploy=0,// ��Ϸ״̬������
	Egs_Fight // ��Ϸ״̬��ս��
};
// ������ײͨ���ĺ�
#define COLLISION_GRID ECC_GameTraceChannel4

#define ENVIRONMENT_HATE_INDEX 10	// ������������ĺ꣬��ʾ�ض������ĵжԳ̶�
#define SUMMARY_NO_SET 100	// ���ڱ�ʾδ���õ�summary��ŵĺֵ꣬Ϊ100��summary���Ϊ100ʱ��ʾû�н�������