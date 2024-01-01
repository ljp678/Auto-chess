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

	virtual void NativeConstruct() override; //���캯��
	
	void RefreshShopUI(); //ˢ��UI

	void RefreshShopPieceIndex(TArray<int32> Index); //ˢ���̵���ָ��λ�õ�����

	void SetPiecesVisibility(ESlateVisibility PieceVisibility); //�������ӵĿɼ���
protected:
	UPROPERTY(meta=(BindWidget))
	UButton* ButtonRefresh; //�̵�ˢ�°�ť

	UPROPERTY(meta=(BindWidget))
	UButton* ButtonBuyExp; //�����鰴ť


	UPROPERTY(meta=(BindWidget))	//���Ӱ�ť����
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
	TArray<UShopPieceWidget*> Pieces; //��������
};
