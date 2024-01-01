// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Clotho/Pawn/PawnBase.h"
#include "PawnMinion.generated.h"

/**
 * 
 */
UCLASS()
class CLOTHO_API APawnMinion : public APawnBase
{
	GENERATED_BODY()
	
protected:

	virtual void OnBeginCursorOverEvent(UPrimitiveComponent* TouchedComponent) override;

	virtual void OnEndCursorOverEvent(UPrimitiveComponent* TouchedComponent) override;

	virtual void OnMeshClickedEvent(UPrimitiveComponent* TouchedComponent, FKey ButtonPressed) override;
};
