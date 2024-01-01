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
struct FPieceDataBase : public FTableRowBase      //��¼���ӵ���Ϣ
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	int32 ID;
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	FText PieceName; //��������
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	FText SkillName; //��������
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	FText SkillDescription; //��������
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	int32 Cost; //�ɱ�
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	UTexture2D* InfoBg; //������Ϣ�ı���ͼ
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	UTexture2D* PieceIcon; //���ӵ�ͼ��
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	UTexture2D* SkillIcon; //���Ӽ��ܵ�ͼ��
	
	
};

USTRUCT(BlueprintType)
struct FPieceData : public FPieceDataBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	TSubclassOf<APawnBase> PieceClass; //�洢���Ӷ�Ӧ��APawnBase��
};

USTRUCT(BlueprintType)
struct FPieceFigureConfigBase : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	int32 ID;
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	float MaxHealth;  //Ѫ��
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	float MaxMagic;   //����
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	float MagicIncrease;  //�����ٶ�
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	float Attack;  //������
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	float AttackDistance; //��������
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	float AttackSpeedCoefficient; //�����ٶ�ϵ��
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	float AttackSpeedBase;  //���������ٶ�          //AttackSpeed = AttackSpeedBase + AttackSpeedCoefficient * AttackSpeedIncrease;
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	float MagicPower;  //ħ��ǿ��
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	float Defence;  //������
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	float MagicDefence;  //����������
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	float MoveSpeed;  //����
};

USTRUCT()
struct FPieceFigureConfig : public FPieceFigureConfigBase
{
	GENERATED_BODY()
	FPieceFigureConfig() //�½���һ���ṹ���ʼ��FPieceFigureConfigBase������
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

	FPieceData* GetPieceDataByID(int32 ID);  //����ID��ȡ���ӵĻ�������

	int32 GetValidateMaxPieceID(); //��ȡ��������ID

	FPieceFigureConfig* GetPieceFigureConfigByID(int32 ID); //��ȡ������Ϣ

protected:

	UDataTable* GetPieceInfoTable(); //��ȡ������Ϣ���

	UDataTable* GetPieceFigureTable(); //��ȡ�������Ա��
	
protected:
	UPROPERTY()
	UDataTable* PieceInfoTable; //������Ϣ������ơ�ͼ�����ݣ�

	UPROPERTY()
	UDataTable* PieceFigureTable; //�������Ա��Ѫ�������ݣ�
};
