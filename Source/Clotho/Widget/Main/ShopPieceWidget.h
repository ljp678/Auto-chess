// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ShopPieceWidget.generated.h"

class UButton;
class UTextBlock;
class UImage;
/**
 * 
 */
UCLASS()
class CLOTHO_API UShopPieceWidget : public UUserWidget
{
	GENERATED_BODY()

	UShopPieceWidget(const FObjectInitializer& ObjectInitializer);

	virtual void NativeConstruct() override;

public:
	void SetPieceIndex(int32 PieceIndex_);

	void RefreshUI();

	bool CheckPieceValidate();

protected:

	UFUNCTION()
	void BuyButtonOnClickedEvent();
	
protected:
	UPROPERTY(meta=(BindWidget))
	UImage* PieceInfo; //���ӵ�ͼ��

	UPROPERTY(meta=(BindWidget))
	UTextBlock* Text_Name; //���ӵ�����

	UPROPERTY(meta=(BindWdiget))
	UTextBlock* Text_Cost; //���ӵļ۸�

	UPROPERTY(meta=(BindWidget))
	UButton* BuyButton; //���򰴼�

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	int32 PieceIndex; //���ӵ�index
};
