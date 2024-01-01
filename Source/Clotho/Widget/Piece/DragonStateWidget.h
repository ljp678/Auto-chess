// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Clotho/Player/DragonCharacter.h"
#include "DragonStateWidget.generated.h"

/**
 * 
 */
UCLASS()
class CLOTHO_API UDragonStateWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	FORCEINLINE void SetDragon(ADragonCharacter* Dragon_) { Dragon = Dragon_; } //…Ë÷√ÕÊº“

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	ADragonCharacter* Dragon;
};
