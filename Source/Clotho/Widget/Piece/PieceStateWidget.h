// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Clotho/Pawn/PawnBase.h"
#include "PieceStateWidget.generated.h"

/**
 * 
 */
UCLASS()
class CLOTHO_API UPieceStateWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	FORCEINLINE void SetPiece(APawnBase* Piece_) { Piece = Piece_; } //…Ë÷√∆Â◊”

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	APawnBase* Piece;
};
