// Fill out your copyright notice in the Description page of Project Settings.


#include "ShopWidget.h"

#include "ShopPieceWidget.h"

void UShopWidget::NativeConstruct()
{
	Super::NativeConstruct();

	Pieces.Add(Piece0); //�����Ӱ�ť��ӵ�Pieces
	Pieces.Add(Piece1);
	Pieces.Add(Piece2);
	Pieces.Add(Piece3);
	Pieces.Add(Piece4);
}


void UShopWidget::RefreshShopUI()
{
	for (auto Piece : Pieces)
	{
		Piece->RefreshUI(); //��ÿ�����Ӷ�ˢ��UI
	}
}

void UShopWidget::RefreshShopPieceIndex(TArray<int32> Index)
{
	for (int32 i = 0; i < Index.Num(); ++i)
	{
		Pieces[i]->SetPieceIndex(Index[i]); //���̵�����Ӧλ�õ���������Ϊ��Ӧ��ֵ
	}
}

void UShopWidget::SetPiecesVisibility(ESlateVisibility PieceVisibility)
{
	for (auto Piece :Pieces)
	{
		if (Piece)
		{
			Piece->SetVisibility(PieceVisibility); //��ÿ�����ӵĿɼ�������Ϊ��Ӧ�Ĳ���
		}
	}
}
