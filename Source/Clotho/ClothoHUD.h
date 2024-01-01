// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "ClothoHUD.generated.h"

class UPieceInfoWidget;
class UMainUI;
/**
 * 
 */
UCLASS()
class CLOTHO_API AClothoHUD : public AHUD
{
	GENERATED_BODY()

public:

	UMainUI* GetMainUI();// ��ȡ������ UI ��ʵ��

	UPieceInfoWidget* GetPieceInfoWidget();// ��ȡ������Ϣ���� Widget ��ʵ��
	
protected:
	virtual void BeginPlay() override;// ����Ϸ��ʼʱ���ã����ڳ�ʼ�� HUD

protected:
	UPROPERTY(VisibleAnywhere)
	UMainUI* MainUI;// ������ UI ʵ��

	UPROPERTY(VisibleAnywhere)
	UPieceInfoWidget* PieceInfoWidget;
};// ������Ϣ���� Widget ʵ��
