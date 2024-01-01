// Fill out your copyright notice in the Description page of Project Settings.


#include "MouseClickActor.h"

#include "Components/DecalComponent.h"
#include "Kismet/GameplayStatics.h"


AMouseClickActor::AMouseClickActor()
{
	PrimaryActorTick.bCanEverTick = true; //����ÿ֡���ú���

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root")); //���������
	CursorToWorld = CreateDefaultSubobject<UDecalComponent>(TEXT("CursorToWorld")); //����CursorToWorld
	CursorToWorld->SetupAttachment(RootComponent); //���丽�ӵ�RootComponent��
	static ConstructorHelpers::FObjectFinder<UMaterial> DecalMaterialAsset(
		TEXT("Material'/Game/Clotho/Materials/M_Cursor_Decal.M_Cursor_Decal'")); //���ز���
	if (DecalMaterialAsset.Succeeded())
	{
		CursorToWorld->SetDecalMaterial(DecalMaterialAsset.Object); //���ø�CursorToWorld
	}
	CursorToWorld->DecalSize = FVector(16.f, 32.f, 32.f); //����Decal�Ĵ�С
	CursorToWorld->SetRelativeRotation(FRotator(90.f, 0.f, 0.f).Quaternion()); //�����ת
}

void AMouseClickActor::BeginPlay()
{
	Super::BeginPlay();

	if (CursorToWorld != nullptr)
	{
		if (APlayerController* Pc = Cast<APlayerController>(UGameplayStatics::GetPlayerController(this, 0))) //��ȡ��ҿ�����
		{
			//ͨ�����ӻ�ȡ�����λ�õ����н��
			FHitResult TraceHitResult;
			Pc->GetHitResultUnderCursor(ECC_Visibility, true, TraceHitResult);
			FVector CursorFV = TraceHitResult.ImpactNormal;
			FRotator CursorR = CursorFV.Rotation();
			//��Decal���õ������λ�ã�����ת���������ķ��߷���
			CursorToWorld->SetWorldLocation(TraceHitResult.Location);
			CursorToWorld->SetWorldRotation(CursorR);
		}
	}
	//��ʾ�������
	K2_ShowClickAnimation();
}

void AMouseClickActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AMouseClickActor::SetDecalLocationAndRotator(FVector Location, FRotator Rotator)
{
	CursorToWorld->SetWorldLocation(Location); //����Decal��λ��
	CursorToWorld->SetWorldRotation(Rotator); //��ת
}
