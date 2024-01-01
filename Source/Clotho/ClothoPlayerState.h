// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "ClothoPlayerState.generated.h"

/**
 * 
 */
UCLASS()
class CLOTHO_API AClothoPlayerState : public APlayerState
{
	GENERATED_BODY()

	AClothoPlayerState();

public:
	void RefreshShopPieceIndex();

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	FORCEINLINE TArray<int32> GetShopPieceIndex() const { return ShopPieceIndex; }

	UFUNCTION()
	void OnRep_ShopPieceIndex();
	
protected:
	UPROPERTY(VisibleAnywhere,ReplicatedUsing=OnRep_ShopPieceIndex)
	TArray<int32> ShopPieceIndex;
};
