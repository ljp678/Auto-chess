// Fill out your copyright notice in the Description page of Project Settings.


#include "GridEffectManager.h"
#include "GridEffectActor.h"
#include "Clotho/Clotho.h"
#include "Clotho/Util/ClothoFunctionLibrary.h"

// Sets default values
AGridEffectManager::AGridEffectManager()
{
	PrimaryActorTick.bCanEverTick = true; //设置每帧执行函数

	WaitingStartPos0 = FVector(-100,-251,-10);
	WaitingStartPos1 = FVector(-100,607,-10);
	WaitingGridStep = FVector(-91,0,0);
	BoardStartPos = FVector(-104,-75,-20);
	BoardGridStep = FVector(-104.4,0,0); //初始化变量
}


void AGridEffectManager::BeginPlay()
{
	Super::BeginPlay(); //父类初始化

	SpawnGridEffectActors(); //生成网格效果

}

void AGridEffectManager::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform); //
}

void AGridEffectManager::SpawnGridEffectActors()
{
	
	

	GridInWaiting.Empty(); //清空等待网格的数组


	const FVector ActorLocation = GetActorLocation(); //获取角色位置
	const TSubclassOf<AGridEffectActor> GridEffectActorWaitingClass = LoadClass<AGridEffectActor>(
		this,TEXT("Blueprint'/Game/Clotho/Actors/BP_GridEffectActorWaiting.BP_GridEffectActorWaiting_C'")); //使用指定蓝图类生成网格效果
	for (int i = 0; i < 16; ++i)
	{
		FVector StartPos = i < 8 ? WaitingStartPos0 : WaitingStartPos1; //根据索引选择起始位置

		FVector TargetLocation = ActorLocation + StartPos + WaitingGridStep * (i % 8); //计算目标位置
		AGridEffectActor* GridEffectActor = GetWorld()->SpawnActor<AGridEffectActor>(
			GridEffectActorWaitingClass, TargetLocation, FRotator::ZeroRotator);
		GridInWaiting.Add(GridEffectActor); //生成并添加网格效果到数组
	}

	GridInBoard.Empty(); //清空游戏板上网格的数组


	const TSubclassOf<AGridEffectActor> GridEffectActorClass = LoadClass<AGridEffectActor>(
		this,TEXT("Blueprint'/Game/Clotho/Actors/BP_GridEffectActor.BP_GridEffectActor_C'")); //使用指定蓝图类生成游戏板上的网格效果
	const FVector BoardGridStepRotate(BoardGridStep.Y,-BoardGridStep.X,BoardGridStep.Z);  //将游戏板旋转90度
	for (int i = 0; i < 6; ++i) //生成网格效果
	{
		for (int j = 0; j < 7; ++j)
		{
			FVector TargetLocation = ActorLocation + BoardStartPos + BoardGridStep * j + BoardGridStepRotate * i; //计算目标位置
			AGridEffectActor* GridEffectActor = GetWorld()->SpawnActor<AGridEffectActor>(GridEffectActorClass,TargetLocation,FRotator::ZeroRotator);
			GridInBoard.Add(GridEffectActor); //生成并添加网格效果到数组
		}
	}
}

void AGridEffectManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AGridEffectManager::ShowGridEffect(bool Show,bool bIsSelf)
{
	for (int32 i=0;i<8;++i) //遍历等待区域
	{
		GridInWaiting[i]->SetShowEffect(Show); //根据参数设置是否显示
	}

	if (UClothoFunctionLibrary::GetCurrentGameState(this) == EGameState::Egs_Deploy) //如果为部署阶段
	{
		for (int32 i=0;i<21;++i) //遍历游戏板
		{
			GridInBoard[i]->SetShowEffect(Show); //根据参数设置是否显示
		}
	}
}

FVector AGridEffectManager::GetGridLocationByIndex(int32 Index)
{
	return GridInWaiting[Index]->GetActorLocation(); //返回目标网格的位置
}

int32 AGridEffectManager::GetGridIndex(AGridEffectActor* GridEffectActor, bool& bIsWaiting)
{
	int32 Index = GridInWaiting.Find(GridEffectActor); //在等待区域中查找
	if (Index != INDEX_NONE)
	{
		bIsWaiting = true; //设置为等待状态
		return Index;
	}

	Index = GridInBoard.Find(GridEffectActor); //否则在游戏板上查找
	bIsWaiting = false; //不是等待状态
	return Index;
}

FVector AGridEffectManager::GetBoardGridLocationByIndex(int32 Index)
{
	return GridInBoard[Index]->GetActorLocation(); //根据索引返回位置
}
