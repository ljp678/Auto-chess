// Fill out your copyright notice in the Description page of Project Settings.


#include "ClothoGameInstance.h"

#include "Manager/PieceInfoManager.h"

UPieceInfoManager* UClothoGameInstance::GetPieceInfoManager()
{
	// 如果 PieceInfoManager 尚未创建，就创建一个新的 PieceInfoManager 对象
	if (!PieceInfoManager)
	{
		PieceInfoManager = NewObject<UPieceInfoManager>(this);
	}
	return PieceInfoManager;
}
