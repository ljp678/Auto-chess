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

	void SetPiece(APawnBase* Piece_,bool bActivate = true); //��������

	void SetActivate(bool bActivate); //���ü���״̬

protected:

	UFUNCTION(BlueprintImplementableEvent)
	void RefreshInfo(); //��ͼ��ʵ��
	
protected:

	UPROPERTY(VisibleAnywhere,BlueprintReadOnly)
	APawnBase* Piece; //����

	UPROPERTY(VisibleAnywhere,BlueprintReadOnly)
	uint8 bMyActivate : 1; //����״̬
};
