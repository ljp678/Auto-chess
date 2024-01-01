// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MessageWidget.generated.h"

class UButton;
/**
 * 
 */
UCLASS()
class CLOTHO_API UMessageWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override; 
	
protected:

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	FText MessageText; //消息文本

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	FText ButtonText; //按钮的文本

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	bool HasButton; //是否含有按钮

	UPROPERTY(VisibleAnywhere,meta=(BindWidget),BlueprintReadWrite)
	UButton* Button_One; //引用蓝图中的按钮
	
};
