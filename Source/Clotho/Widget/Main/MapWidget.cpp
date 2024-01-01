// Fill out your copyright notice in the Description page of Project Settings.


#include "MapWidget.h"

#include "Clotho/Actor/CameraDirector.h"
#include "Clotho/Player/DragonCharacter.h"
#include "Kismet/GameplayStatics.h"

void UMapWidget::InitCameraDirector()
{
	TArray<AActor*> CameraDirectors;

	UGameplayStatics::GetAllActorsOfClass(this, ACameraDirector::StaticClass(), CameraDirectors); //��ȡ���������е������

	CameraDirector = Cast<ACameraDirector>(CameraDirectors[0]); //�������е�һ�����������Ϊ��ǰ�������
}

void UMapWidget::InitBorder()
{
	ADragonCharacter* Pawn = Cast<ADragonCharacter>(UGameplayStatics::GetPlayerCharacter(this,0)); //��ȡ��ǰ���
	if (Pawn)
	{
		UE_LOG(LogTemp, Warning, TEXT("-------%d"),Pawn->GetPlayerIndex())
		K2_ChangeBorder(Pawn->GetPlayerIndex()); //��ȡ��������������������������
	}else
	{
		UE_LOG(LogTemp, Warning, TEXT("MapWidget InitBorder ,No Pawn"))
	}
}

void UMapWidget::K2_ChangeCamera(int32 Index)
{

}
