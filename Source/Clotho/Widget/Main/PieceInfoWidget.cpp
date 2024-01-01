// Fill out your copyright notice in the Description page of Project Settings.


#include "PieceInfoWidget.h"

void UPieceInfoWidget::SetPiece(APawnBase* Piece_, bool bActivate)
{
	Piece = Piece_; //��ȡ����

	SetActivate(bActivate); //���ü���״̬
}

void UPieceInfoWidget::SetActivate(bool bActivate)
{
	bMyActivate = bActivate;
	if (bMyActivate)
	{
		RefreshInfo(); //��������ˢ����Ϣ
		SetVisibility(ESlateVisibility::Visible); //�ɼ�
	}
	else
	{
		SetVisibility(ESlateVisibility::Collapsed); //���򲻿ɼ�
	}
}
