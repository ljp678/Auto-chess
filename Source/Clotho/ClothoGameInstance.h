// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "ClothoGameInstance.generated.h"

class UPieceInfoManager;
/**
 * 
 */
UCLASS()
class CLOTHO_API UClothoGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:

	UPieceInfoManager* GetPieceInfoManager();//获取 PieceInfoManager 对象

	
protected:
	UPROPERTY()
	UPieceInfoManager* PieceInfoManager;//PieceInfoManager 对象的指针，用于管理棋子信息
};
