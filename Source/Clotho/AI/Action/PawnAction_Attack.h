// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actions/PawnAction.h"
#include "PawnAction_Attack.generated.h"

/**
 * 
 */
UCLASS()
class CLOTHO_API UPawnAction_Attack : public UPawnAction
{
	GENERATED_BODY()

	UPawnAction_Attack();
	
protected:
	virtual bool Start() override; //������Ϊ��ʼ�Ĳ���

	virtual void Tick(float DeltaTime) override; //ÿ֡�Ĺ�������


protected:
	float Duration; //�����ĳ���ʱ��
	float TimeCount; //�����Ѿ����е�ʱ��
};
