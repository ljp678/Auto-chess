// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MapWidget.generated.h"

class UImage;
class ACameraDirector;
/**
 * 
 */
UCLASS()
class CLOTHO_API UMapWidget : public UUserWidget
{
	GENERATED_BODY()


public:
	void InitCameraDirector(); //��ʼ��

	void InitBorder(); //��ʼ���߽���Ϣ

	UFUNCTION(BlueprintImplementableEvent,BlueprintCallable,meta=(DisplayName=ChangeBoarder))
	void K2_ChangeBorder(int32 Index); //�ı�߽�
	
protected:
	UFUNCTION(BlueprintCallable, meta=(DisplayName=ChangeCamera))
	void K2_ChangeCamera(int32 Index); //�ı�������ķ�λ
	
protected:
	
	UPROPERTY(EditAnywhere)
	ACameraDirector* CameraDirector; //�����

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	int32 CameraIndex; //�������index
};
