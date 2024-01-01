// Fill out your copyright notice in the Description page of Project Settings.


#include "PieceInfoManager.h"
#include "Clotho/Pawn/PawnBase.h"

FPieceData* UPieceInfoManager::GetPieceDataByID(int32 ID)
{
	UDataTable* Table = GetPieceInfoTable(); //��ȡ��Ϣ���
	if (Table)
	{
		TMap<FName,uint8*> Data = Table->GetRowMap(); //��ȡ������ӳ��
		FName RowID = FName(*FString::FromInt(ID)); //��IDתΪFName���ͣ����ڼ��
		if (Data.Contains(RowID))
		{
			return reinterpret_cast<FPieceData*>(Data[RowID]); //���ڣ���ת�����Ͳ�����
		}
	}
	return nullptr;
}

int32 UPieceInfoManager::GetValidateMaxPieceID()
{
	static int32 Index = GetPieceInfoTable()->GetRowMap().Num(); //��ӳ�����������������
	return Index;
}

FPieceFigureConfig* UPieceInfoManager::GetPieceFigureConfigByID(int32 ID)
{
	UDataTable* Table = GetPieceFigureTable(); //��ɫ���Ե����ݱ��
	if (Table)
	{
		TMap<FName,uint8*> Data = Table->GetRowMap(); //��ȡ������ӳ��
		FName RowID = FName(*FString::FromInt(ID)); //����ת�������ڼ��
		if (Data.Contains(RowID))
		{
			return reinterpret_cast<FPieceFigureConfig*>(Data[RowID]);	 //ת�����Ͳ�����
		}
	}
	return nullptr;
}

UDataTable* UPieceInfoManager::GetPieceInfoTable()
{
	if (!PieceInfoTable)
	{
		PieceInfoTable = LoadObject<UDataTable>(this,TEXT("DataTable'/Game/Clotho/Data/DT_PieceInfo.DT_PieceInfo'"));
	}
	return PieceInfoTable;
}

UDataTable* UPieceInfoManager::GetPieceFigureTable()
{
	if (!PieceFigureTable)
	{
		PieceFigureTable = LoadObject<UDataTable>(this,TEXT("DataTable'/Game/Clotho/Data/DT_PieceFigureConfig.DT_PieceFigureConfig'"));
	}
	return PieceFigureTable;
}
