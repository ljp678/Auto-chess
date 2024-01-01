// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PieceInfoWidget.generated.h"

class APawnBase;
/**
 * 
 */
UCLASS()
class CLOTHO_API UPieceInfoWidget : public UUserWidget
{
	GENERATED_BODY()


public:

	void SetPiece(APawnBase* Piece_,bool bActivate = true); //设置棋子

	void SetActivate(bool bActivate); //设置激活状态

protected:

	UFUNCTION(BlueprintImplementableEvent)
	void RefreshInfo(); //蓝图中实现
	
protected:

	UPROPERTY(VisibleAnywhere,BlueprintReadOnly)
	APawnBase* Piece; //棋子

	UPROPERTY(VisibleAnywhere,BlueprintReadOnly)
	uint8 bMyActivate : 1; //激活状态
};
