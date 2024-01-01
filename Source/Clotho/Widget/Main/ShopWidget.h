// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ShopWidget.generated.h"

class UShopPieceWidget;
class UButton;
/**
 * 
 */
UCLASS()
class CLOTHO_API UShopWidget : public UUserWidget
{
	GENERATED_BODY()

public:

	virtual void NativeConstruct() override; //构造函数
	
	void RefreshShopUI(); //刷新UI

	void RefreshShopPieceIndex(TArray<int32> Index); //刷新商店中指定位置的棋子

	void SetPiecesVisibility(ESlateVisibility PieceVisibility); //设置棋子的可见性
protected:
	UPROPERTY(meta=(BindWidget))
	UButton* ButtonRefresh; //商店刷新按钮

	UPROPERTY(meta=(BindWidget))
	UButton* ButtonBuyExp; //购买经验按钮


	UPROPERTY(meta=(BindWidget))	//棋子按钮数组
	UShopPieceWidget* Piece0;
	UPROPERTY(meta=(BindWidget))
	UShopPieceWidget* Piece1;
	UPROPERTY(meta=(BindWidget))
	UShopPieceWidget* Piece2;
	UPROPERTY(meta=(BindWidget))
	UShopPieceWidget* Piece3;
	UPROPERTY(meta=(BindWidget))
	UShopPieceWidget* Piece4;

	UPROPERTY(VisibleAnywhere,BlueprintReadOnly)
	TArray<UShopPieceWidget*> Pieces; //棋子数组
};
