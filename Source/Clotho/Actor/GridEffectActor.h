// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GridEffectActor.generated.h"

UENUM()
enum class EGridColor :uint8
{
	Egc_Blue, //������ɫ
	Egc_Yellow
};

UCLASS()
class CLOTHO_API AGridEffectActor : public AActor
{
	GENERATED_BODY()

public:

	AGridEffectActor();

protected:

	virtual void BeginPlay() override;

public:

	virtual void Tick(float DeltaTime) override;

	void SetShowEffect(bool Show); //�����Ƿ���ʾЧ��

	void SetEffectColor(EGridColor GridColor) const; //�����������ɫ

	static FVector ConvertGridColorToVector(EGridColor GridColor); //��ö������ת��Ϊ����

	FORCEINLINE bool GetIsVisible() const { return bIsVisible; } //��ȡ�Ƿ�ɼ�����Ϣ
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* GridEffect; //����Ч�������

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	uint8 bIsVisible: 1; //�Ƿ�ɼ�
};
