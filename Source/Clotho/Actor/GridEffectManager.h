// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GridEffectManager.generated.h"

#define MAX_GRID_NUM 41

class AGridEffectActor;
UCLASS()
class CLOTHO_API AGridEffectManager : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AGridEffectManager();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void OnConstruction(const FTransform& Transform) override; // Function called during construction

	void SpawnGridEffectActors(); // Generate grid effects

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	FORCEINLINE int32 GetGridIndex() const { return GridIndex; } // Get the index of the grid

	void ShowGridEffect(bool Show, bool bIsSelf); // Control whether to display grid effects

	FVector GetGridLocationByIndex(int32 Index); // Get the location of the grid based on the index

	int32 GetGridIndex(AGridEffectActor* GridEffectActor, bool& bIsWaiting); // Get the index based on the grid

	FVector GetBoardGridLocationByIndex(int32 Index); // Get the location of the grid on the board

protected:
	UPROPERTY(VisibleAnywhere)
	TArray<AGridEffectActor*> GridInBoard; // Array to store grids on the board

	UPROPERTY(VisibleAnywhere)
	TArray<AGridEffectActor*> GridInWaiting;

	UPROPERTY(EditAnywhere)
	FVector WaitingStartPos0; // Starting position of the waiting area 1

	UPROPERTY(EditAnywhere)
	FVector WaitingStartPos1; // Starting position of the waiting area 2

	UPROPERTY(EditAnywhere)
	FVector WaitingGridStep; // Step between grids in the waiting area (for calculating positions)

	UPROPERTY(EditAnywhere)
	FVector BoardStartPos; // Starting position of the board

	UPROPERTY(EditAnywhere)
	FVector BoardGridStep; // Step between grids on the game board

	UPROPERTY(EditAnywhere)
	int32 GridIndex; // Current index of the grid
};