// Fill out your copyright notice in the Description page of Project Settings.


#include "PieceInfoManager.h"
#include "Clotho/Pawn/PawnBase.h"

FPieceData* UPieceInfoManager::GetPieceDataByID(int32 ID)
{
	UDataTable* Table = GetPieceInfoTable(); //获取信息表格
	if (Table)
	{
		TMap<FName,uint8*> Data = Table->GetRowMap(); //获取表格的行映射
		FName RowID = FName(*FString::FromInt(ID)); //将ID转为FName类型，便于检查
		if (Data.Contains(RowID))
		{
			return reinterpret_cast<FPieceData*>(Data[RowID]); //存在，则转换类型并返回
		}
	}
	return nullptr;
}

int32 UPieceInfoManager::GetValidateMaxPieceID()
{
	static int32 Index = GetPieceInfoTable()->GetRowMap().Num(); //行映射的数量即棋子数量
	return Index;
}

FPieceFigureConfig* UPieceInfoManager::GetPieceFigureConfigByID(int32 ID)
{
	UDataTable* Table = GetPieceFigureTable(); //角色属性的数据表格
	if (Table)
	{
		TMap<FName,uint8*> Data = Table->GetRowMap(); //获取表格的行映射
		FName RowID = FName(*FString::FromInt(ID)); //类型转换，便于检查
		if (Data.Contains(RowID))
		{
			return reinterpret_cast<FPieceFigureConfig*>(Data[RowID]);	 //转换类型并返回
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
