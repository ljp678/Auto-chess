// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MouseClickActor.generated.h"

UCLASS()
class CLOTHO_API AMouseClickActor : public AActor
{
	GENERATED_BODY()

public:

	AMouseClickActor();

protected:

	virtual void BeginPlay() override;

public:

	virtual void Tick(float DeltaTime) override;

	FORCEINLINE UDecalComponent* GetCursorToWorld() { return CursorToWorld; } // Get the mouse click position

	void SetDecalLocationAndRotator(FVector Location, FRotator Rotator); // Set the position and rotation of the Decal

	UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "ShowClickAnimation"))
	void K2_ShowClickAnimation(); // Blueprint callable event

private:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess = "true"))
	UDecalComponent* CursorToWorld; // Decal component displayed at the mouse click position
};