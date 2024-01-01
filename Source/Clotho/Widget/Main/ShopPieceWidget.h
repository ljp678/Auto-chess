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
	UImage* PieceInfo; //棋子的图像

	UPROPERTY(meta=(BindWidget))
	UTextBlock* Text_Name; //棋子的名称

	UPROPERTY(meta=(BindWdiget))
	UTextBlock* Text_Cost; //棋子的价格

	UPROPERTY(meta=(BindWidget))
	UButton* BuyButton; //购买按键

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	int32 PieceIndex; //棋子的index
};
