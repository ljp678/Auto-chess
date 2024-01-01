// Fill out your copyright notice in the Description page of Project Settings.


#include "CameraDirector.h"

#include "Kismet/GameplayStatics.h"


ACameraDirector::ACameraDirector()
{
	PrimaryActorTick.bCanEverTick = false; //设置不需要逐帧调用

}


void ACameraDirector::BeginPlay()
{
	Super::BeginPlay(); //父类的初始化
	
}


void ACameraDirector::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime); //父类的函数

}

void ACameraDirector::ChangeCamera(int32 Index)
{
	APlayerController* OurPlayerController = UGameplayStatics::GetPlayerController(this, 0); //获取玩家控制器对象
	OurPlayerController->SetViewTarget(CameraActors[Index]); //将玩家的视角切换到目标相机
}

AActor* ACameraDirector::GetCameraByIndex(int32 Index)
{
	return CameraActors[Index]; //返回索引未知的相机对象
}

