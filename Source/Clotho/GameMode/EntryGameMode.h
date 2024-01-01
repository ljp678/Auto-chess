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
	FText Message;	//��ͼֻ���������⵽����������������ͻ������������Ϊ��Ӧ����Ϣ�ı�
};
