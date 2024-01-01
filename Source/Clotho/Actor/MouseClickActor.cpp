// Fill out your copyright notice in the Description page of Project Settings.


#include "MouseClickActor.h"

#include "Components/DecalComponent.h"
#include "Kismet/GameplayStatics.h"


AMouseClickActor::AMouseClickActor()
{
	PrimaryActorTick.bCanEverTick = true; //设置每帧调用函数

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root")); //创建根组件
	CursorToWorld = CreateDefaultSubobject<UDecalComponent>(TEXT("CursorToWorld")); //创建CursorToWorld
	CursorToWorld->SetupAttachment(RootComponent); //将其附加到RootComponent上
	static ConstructorHelpers::FObjectFinder<UMaterial> DecalMaterialAsset(
		TEXT("Material'/Game/Clotho/Materials/M_Cursor_Decal.M_Cursor_Decal'")); //加载材质
	if (DecalMaterialAsset.Succeeded())
	{
		CursorToWorld->SetDecalMaterial(DecalMaterialAsset.Object); //设置给CursorToWorld
	}
	CursorToWorld->DecalSize = FVector(16.f, 32.f, 32.f); //设置Decal的大小
	CursorToWorld->SetRelativeRotation(FRotator(90.f, 0.f, 0.f).Quaternion()); //相对旋转
}

void AMouseClickActor::BeginPlay()
{
	Super::BeginPlay();

	if (CursorToWorld != nullptr)
	{
		if (APlayerController* Pc = Cast<APlayerController>(UGameplayStatics::GetPlayerController(this, 0))) //获取玩家控制器
		{
			//通过涉嫌获取鼠标点击位置的命中结果
			FHitResult TraceHitResult;
			Pc->GetHitResultUnderCursor(ECC_Visibility, true, TraceHitResult);
			FVector CursorFV = TraceHitResult.ImpactNormal;
			FRotator CursorR = CursorFV.Rotation();
			//将Decal设置到鼠标点击位置，并旋转到点击表面的法线方向
			CursorToWorld->SetWorldLocation(TraceHitResult.Location);
			CursorToWorld->SetWorldRotation(CursorR);
		}
	}
	//显示点击动画
	K2_ShowClickAnimation();
}

void AMouseClickActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AMouseClickActor::SetDecalLocationAndRotator(FVector Location, FRotator Rotator)
{
	CursorToWorld->SetWorldLocation(Location); //设置Decal的位置
	CursorToWorld->SetWorldRotation(Rotator); //旋转
}
