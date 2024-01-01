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
	ACameraDirector(); //设置默认值，初始化类的成员变量

protected:

	virtual void BeginPlay() override; //游戏开始时操作

public:	

	virtual void Tick(float DeltaTime) override; //逐帧操作的函数

	void ChangeCamera(int32 Index); //根据索引切换相机

	AActor* GetCameraByIndex(int32 Index); //根据索引获取相机对象
protected:

	UPROPERTY(EditAnywhere)
	TArray<AActor*> CameraActors; //不同位置和角度的相机
	
};
