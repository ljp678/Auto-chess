// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GridEffectActor.generated.h"

UENUM()
enum class EGridColor :uint8
{
	Egc_Blue, //网格颜色
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

	void SetShowEffect(bool Show); //设置是否显示效果

	void SetEffectColor(EGridColor GridColor) const; //设置网格的颜色

	static FVector ConvertGridColorToVector(EGridColor GridColor); //将枚举类型转换为向量

	FORCEINLINE bool GetIsVisible() const { return bIsVisible; } //获取是否可见的信息
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* GridEffect; //网格效果的组件

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	uint8 bIsVisible: 1; //是否可见
};
