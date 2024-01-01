// Fill out your copyright notice in the Description page of Project Settings.


#include "GridEffectActor.h"

#include "Particles/ParticleSystemComponent.h"


AGridEffectActor::AGridEffectActor()
{
	PrimaryActorTick.bCanEverTick = true; //������֡����Tick����

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root")); //����Ĭ���Ӷ���


	GridEffect = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("GridEffect")); //��������Ч�������
	GridEffect->SetupAttachment(RootComponent); //

	static ConstructorHelpers::FObjectFinder<UStaticMesh> GridEffectObjectFinder(
		TEXT("StaticMesh'/Engine/BasicShapes/Plane.Plane'")); //��������Ч���ľ�̬����
	if (GridEffectObjectFinder.Succeeded())
	{
		GridEffect->SetStaticMesh(GridEffectObjectFinder.Object);//��Ϊģ��
	}

}


void AGridEffectActor::BeginPlay()
{
	Super::BeginPlay();

	SetShowEffect(false); //��ʼʱ��������Ч��Ϊ���ɼ�
}


void AGridEffectActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AGridEffectActor::SetShowEffect(bool Show)
{
	const float Opacity = Show ? 0.8 : 0; //���ݴ���Ĳ������ò�͸����
	bIsVisible = Show;

	GridEffect->SetScalarParameterValueOnMaterials(FName(TEXT("Opacity")), Opacity); //�ڲ����ϸ�������
}

void AGridEffectActor::SetEffectColor(EGridColor GridColor) const
{
	const FVector Color = ConvertGridColorToVector(GridColor); //��ö������ת��Ϊ��ɫ����
	GridEffect->SetVectorParameterValueOnMaterials(FName(TEXT("Color")),Color); //������ɫ����ֵ
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
	return FVector(0, 0.06, 0.36); //Ĭ�Ϸ�����ɫ
}
