// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actions/PawnAction.h"
#include "PawnAction_ChangeNav.generated.h"

/**
 * 
 */
UCLASS()
class CLOTHO_API UPawnAction_ChangeNav : public UPawnAction
{
	GENERATED_BODY()

protected:

	virtual bool Start() override;
	
protected:

	UPROPERTY(EditAnywhere)
	uint8 bNavNull : 1; 
};
