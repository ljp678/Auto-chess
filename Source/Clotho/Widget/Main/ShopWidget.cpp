// Fill out your copyright notice in the Description page of Project Settings.


#include "ShopWidget.h"

#include "ShopPieceWidget.h"

void UShopWidget::NativeConstruct()
{
	Super::NativeConstruct();

	Pieces.Add(Piece0); //将棋子按钮添加到Pieces
	Pieces.Add(Piece1);
	Pieces.Add(Piece2);
	Pieces.Add(Piece3);
	Pieces.Add(Piece4);
}


void UShopWidget::RefreshShopUI()
{
	for (auto Piece : Pieces)
	{
		Piece->RefreshUI(); //对每个棋子都刷新UI
	}
}

void UShopWidget::RefreshShopPieceIndex(TArray<int32> Index)
{
	for (int32 i = 0; i < Index.Num(); ++i)
	{
		Pieces[i]->SetPieceIndex(Index[i]); //将商店中相应位置的索引设置为对应的值
	}
}

void UShopWidget::SetPiecesVisibility(ESlateVisibility PieceVisibility)
{
	for (auto Piece :Pieces)
	{
		if (Piece)
		{
			Piece->SetVisibility(PieceVisibility); //将每个棋子的可见性设置为对应的参数
		}
	}
}
