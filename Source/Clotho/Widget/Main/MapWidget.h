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
	void InitCameraDirector(); //初始化

	void InitBorder(); //初始化边界信息

	UFUNCTION(BlueprintImplementableEvent,BlueprintCallable,meta=(DisplayName=ChangeBoarder))
	void K2_ChangeBorder(int32 Index); //改变边界
	
protected:
	UFUNCTION(BlueprintCallable, meta=(DisplayName=ChangeCamera))
	void K2_ChangeCamera(int32 Index); //改变摄像机的方位
	
protected:
	
	UPROPERTY(EditAnywhere)
	ACameraDirector* CameraDirector; //摄像机

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	int32 CameraIndex; //摄像机的index
};
