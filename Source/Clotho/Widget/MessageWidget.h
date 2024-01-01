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
	FText MessageText; //��Ϣ�ı�

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	FText ButtonText; //��ť���ı�

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	bool HasButton; //�Ƿ��а�ť

	UPROPERTY(VisibleAnywhere,meta=(BindWidget),BlueprintReadWrite)
	UButton* Button_One; //������ͼ�еİ�ť
	
};
