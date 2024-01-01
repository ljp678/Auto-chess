// Fill out your copyright notice in the Description page of Project Settings.


#include "EntryGameMode.h"

#include "Kismet/GameplayStatics.h"
// 当前函数在玩家加入游戏时被调用，处理了在玩家加入游戏时的一些逻辑，例如检查是否人数已满，并根据情况设置一些消息。
FString AEntryGameMode::InitNewPlayer(APlayerController* NewPlayerController, const FUniqueNetIdRepl& UniqueId,
                                      const FString& Options, const FString& Portal)
{

	

	// 检查 Options 字符串是否包含 "closed" 选项
	if (UGameplayStatics::HasOption(Options,TEXT("closed")))
	{

		Message = FText::FromString(TEXT("人数已满"));// 设置消息，表示人数已满

	}
	
	return Super::InitNewPlayer(NewPlayerController, UniqueId, Options, Portal);// 调用基类的同名函数，并返回其结果
}
