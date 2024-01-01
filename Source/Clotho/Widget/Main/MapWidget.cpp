// Fill out your copyright notice in the Description page of Project Settings.


#include "MapWidget.h"

#include "Clotho/Actor/CameraDirector.h"
#include "Clotho/Player/DragonCharacter.h"
#include "Kismet/GameplayStatics.h"

void UMapWidget::InitCameraDirector()
{
	TArray<AActor*> CameraDirectors;

	UGameplayStatics::GetAllActorsOfClass(this, ACameraDirector::StaticClass(), CameraDirectors); //获取场景中所有的摄像机

	CameraDirector = Cast<ACameraDirector>(CameraDirectors[0]); //将数组中第一个摄像机设置为当前的摄像机
}

void UMapWidget::InitBorder()
{
	ADragonCharacter* Pawn = Cast<ADragonCharacter>(UGameplayStatics::GetPlayerCharacter(this,0)); //获取当前玩家
	if (Pawn)
	{
		UE_LOG(LogTemp, Warning, TEXT("-------%d"),Pawn->GetPlayerIndex())
		K2_ChangeBorder(Pawn->GetPlayerIndex()); //获取玩家索引，并根据索引更改相机
	}else
	{
		UE_LOG(LogTemp, Warning, TEXT("MapWidget InitBorder ,No Pawn"))
	}
}

void UMapWidget::K2_ChangeCamera(int32 Index)
{

}
