// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "UObject/NoExportTypes.h"
#include "PieceInfoManager.generated.h"

/**
 * 
 */

class APawnBase;
USTRUCT(BlueprintType)
struct FPieceDataBase : public FTableRowBase      //记录棋子的信息
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	int32 ID;
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	FText PieceName; //棋子名称
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	FText SkillName; //技能名称
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	FText SkillDescription; //技能描述
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	int32 Cost; //成本
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	UTexture2D* InfoBg; //棋子信息的背景图
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	UTexture2D* PieceIcon; //棋子的图标
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	UTexture2D* SkillIcon; //棋子技能的图标
	
	
};

USTRUCT(BlueprintType)
struct FPieceData : public FPieceDataBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	TSubclassOf<APawnBase> PieceClass; //存储棋子对应的APawnBase类
};

USTRUCT(BlueprintType)
struct FPieceFigureConfigBase : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	int32 ID;
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	float MaxHealth;  //血量
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	float MaxMagic;   //蓝条
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	float MagicIncrease;  //回蓝速度
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	float Attack;  //攻击力
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	float AttackDistance; //攻击距离
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	float AttackSpeedCoefficient; //攻击速度系数
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	float AttackSpeedBase;  //基础攻击速度          //AttackSpeed = AttackSpeedBase + AttackSpeedCoefficient * AttackSpeedIncrease;
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	float MagicPower;  //魔法强度
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	float Defence;  //防御力
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	float MagicDefence;  //法术防御力
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	float MoveSpeed;  //移速
};

USTRUCT()
struct FPieceFigureConfig : public FPieceFigureConfigBase
{
	GENERATED_BODY()
	FPieceFigureConfig() //新建了一个结构体初始化FPieceFigureConfigBase的数据
	{
		MaxHealth = 100.f;
		MaxMagic = 0;
		MagicIncrease = 0;
		Attack = 10.f;
		AttackDistance = 100;
		AttackSpeedCoefficient = 1.f;
		AttackSpeedBase = 1;
		MagicPower = 0;
		Defence = 0;
		MagicDefence = 0;
		MoveSpeed = 260;
	}
};


UCLASS()
class CLOTHO_API UPieceInfoManager : public UObject
{
	GENERATED_BODY()

public:

	FPieceData* GetPieceDataByID(int32 ID);  //根据ID获取棋子的基本数据

	int32 GetValidateMaxPieceID(); //获取最大的棋子ID

	FPieceFigureConfig* GetPieceFigureConfigByID(int32 ID); //获取棋子信息

protected:

	UDataTable* GetPieceInfoTable(); //获取棋子信息表格

	UDataTable* GetPieceFigureTable(); //获取棋子属性表格
	
protected:
	UPROPERTY()
	UDataTable* PieceInfoTable; //棋子信息表格（名称、图等内容）

	UPROPERTY()
	UDataTable* PieceFigureTable; //棋子属性表格（血量等内容）
};
