// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CameraDirector.generated.h"

UCLASS()
class CLOTHO_API ACameraDirector : public AActor
{
	GENERATED_BODY()
	
public:	
	ACameraDirector(); //����Ĭ��ֵ����ʼ����ĳ�Ա����

protected:

	virtual void BeginPlay() override; //��Ϸ��ʼʱ����

public:	

	virtual void Tick(float DeltaTime) override; //��֡�����ĺ���

	void ChangeCamera(int32 Index); //���������л����

	AActor* GetCameraByIndex(int32 Index); //����������ȡ�������
protected:

	UPROPERTY(EditAnywhere)
	TArray<AActor*> CameraActors; //��ͬλ�úͽǶȵ����
	
};
