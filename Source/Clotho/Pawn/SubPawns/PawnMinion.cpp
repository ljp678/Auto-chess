// Fill out your copyright notice in the Description page of Project Settings.


#include "PawnMinion.h"

void APawnMinion::OnBeginCursorOverEvent(UPrimitiveComponent* TouchedComponent)
{
	Super::OnBeginCursorOverEvent(TouchedComponent);
}

void APawnMinion::OnEndCursorOverEvent(UPrimitiveComponent* TouchedComponent)
{
	Super::OnEndCursorOverEvent(TouchedComponent);
}

void APawnMinion::OnMeshClickedEvent(UPrimitiveComponent* TouchedComponent, FKey ButtonPressed)
{
	Super::OnMeshClickedEvent(TouchedComponent, ButtonPressed);
}
