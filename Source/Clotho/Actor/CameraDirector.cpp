// Fill out your copyright notice in the Description page of Project Settings.


#include "CameraDirector.h"

#include "Kismet/GameplayStatics.h"


ACameraDirector::ACameraDirector()
{
	PrimaryActorTick.bCanEverTick = false; //���ò���Ҫ��֡����

}


void ACameraDirector::BeginPlay()
{
	Super::BeginPlay(); //����ĳ�ʼ��
	
}


void ACameraDirector::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime); //����ĺ���

}

void ACameraDirector::ChangeCamera(int32 Index)
{
	APlayerController* OurPlayerController = UGameplayStatics::GetPlayerController(this, 0); //��ȡ��ҿ���������
	OurPlayerController->SetViewTarget(CameraActors[Index]); //����ҵ��ӽ��л���Ŀ�����
}

AActor* ACameraDirector::GetCameraByIndex(int32 Index)
{
	return CameraActors[Index]; //��������δ֪���������
}

