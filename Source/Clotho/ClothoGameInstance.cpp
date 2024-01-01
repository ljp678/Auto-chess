// Fill out your copyright notice in the Description page of Project Settings.


#include "ClothoGameInstance.h"

#include "Manager/PieceInfoManager.h"

UPieceInfoManager* UClothoGameInstance::GetPieceInfoManager()
{
	// ��� PieceInfoManager ��δ�������ʹ���һ���µ� PieceInfoManager ����
	if (!PieceInfoManager)
	{
		PieceInfoManager = NewObject<UPieceInfoManager>(this);
	}
	return PieceInfoManager;
}
