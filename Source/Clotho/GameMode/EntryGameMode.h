// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "GameFramework/GameMode.h"
#include "EntryGameMode.generated.h"

/**
 * 
 */
UCLASS()
class CLOTHO_API AEntryGameMode : public AGameMode
{
	GENERATED_BODY()

public:
	virtual FString InitNewPlayer(APlayerController* NewPlayerController, const FUniqueNetIdRepl& UniqueId,
	                              const FString& Options, const FString& Portal) override;


protected:
	
	UPROPERTY(BlueprintReadOnly)
	FText Message;	//蓝图只读，如果检测到人数已满的情况，就会设置这个属性为相应的消息文本
};
