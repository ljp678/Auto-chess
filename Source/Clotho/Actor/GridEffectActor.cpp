// Fill out your copyright notice in the Description page of Project Settings.


#include "GridEffectActor.h"

#include "Particles/ParticleSystemComponent.h"


AGridEffectActor::AGridEffectActor()
{
	PrimaryActorTick.bCanEverTick = true; //设置逐帧调用Tick函数

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root")); //创建默认子对象


	GridEffect = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("GridEffect")); //创建网格效果的组件
	GridEffect->SetupAttachment(RootComponent); //

	static ConstructorHelpers::FObjectFinder<UStaticMesh> GridEffectObjectFinder(
		TEXT("StaticMesh'/Engine/BasicShapes/Plane.Plane'")); //查找网格效果的静态网格
	if (GridEffectObjectFinder.Succeeded())
	{
		GridEffect->SetStaticMesh(GridEffectObjectFinder.Object);//作为模板
	}

}


void AGridEffectActor::BeginPlay()
{
	Super::BeginPlay();

	SetShowEffect(false); //开始时设置网格效果为不可见
}


void AGridEffectActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AGridEffectActor::SetShowEffect(bool Show)
{
	const float Opacity = Show ? 0.8 : 0; //根据传入的参数设置不透明度
	bIsVisible = Show;

	GridEffect->SetScalarParameterValueOnMaterials(FName(TEXT("Opacity")), Opacity); //在材质上更新设置
}

void AGridEffectActor::SetEffectColor(EGridColor GridColor) const
{
	const FVector Color = ConvertGridColorToVector(GridColor); //将枚举类型转换为颜色向量
	GridEffect->SetVectorParameterValueOnMaterials(FName(TEXT("Color")),Color); //设置颜色参数值
}

FVector AGridEffectActor::ConvertGridColorToVector(EGridColor GridColor)
{
	switch (GridColor)
	{
	case EGridColor::Egc_Blue: return FVector(0, 0.06, 0.36);
		break;
	case EGridColor::Egc_Yellow: return FVector(0.65, 0.59, 0.06);
		break;
	default: ;
	}
	return FVector(0, 0.06, 0.36); //默认返回蓝色
}
