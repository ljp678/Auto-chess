// Fill out your copyright notice in the Description page of Project Settings.


#include "PieceInfoWidget.h"

void UPieceInfoWidget::SetPiece(APawnBase* Piece_, bool bActivate)
{
	Piece = Piece_; //获取棋子

	SetActivate(bActivate); //设置激活状态
}

void UPieceInfoWidget::SetActivate(bool bActivate)
{
	bMyActivate = bActivate;
	if (bMyActivate)
	{
		RefreshInfo(); //如果激活，则刷新信息
		SetVisibility(ESlateVisibility::Visible); //可见
	}
	else
	{
		SetVisibility(ESlateVisibility::Collapsed); //否则不可见
	}
}
