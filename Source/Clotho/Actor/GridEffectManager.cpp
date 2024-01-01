// Fill out your copyright notice in the Description page of Project Settings.


#include "GridEffectManager.h"
#include "GridEffectActor.h"
#include "Clotho/Clotho.h"
#include "Clotho/Util/ClothoFunctionLibrary.h"

// Sets default values
AGridEffectManager::AGridEffectManager()
{
	PrimaryActorTick.bCanEverTick = true; //����ÿִ֡�к���

	WaitingStartPos0 = FVector(-100,-251,-10);
	WaitingStartPos1 = FVector(-100,607,-10);
	WaitingGridStep = FVector(-91,0,0);
	BoardStartPos = FVector(-104,-75,-20);
	BoardGridStep = FVector(-104.4,0,0); //��ʼ������
}


void AGridEffectManager::BeginPlay()
{
	Super::BeginPlay(); //�����ʼ��

	SpawnGridEffectActors(); //��������Ч��

}

void AGridEffectManager::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform); //
}

void AGridEffectManager::SpawnGridEffectActors()
{
	
	

	GridInWaiting.Empty(); //��յȴ����������


	const FVector ActorLocation = GetActorLocation(); //��ȡ��ɫλ��
	const TSubclassOf<AGridEffectActor> GridEffectActorWaitingClass = LoadClass<AGridEffectActor>(
		this,TEXT("Blueprint'/Game/Clotho/Actors/BP_GridEffectActorWaiting.BP_GridEffectActorWaiting_C'")); //ʹ��ָ����ͼ����������Ч��
	for (int i = 0; i < 16; ++i)
	{
		FVector StartPos = i < 8 ? WaitingStartPos0 : WaitingStartPos1; //��������ѡ����ʼλ��

		FVector TargetLocation = ActorLocation + StartPos + WaitingGridStep * (i % 8); //����Ŀ��λ��
		AGridEffectActor* GridEffectActor = GetWorld()->SpawnActor<AGridEffectActor>(
			GridEffectActorWaitingClass, TargetLocation, FRotator::ZeroRotator);
		GridInWaiting.Add(GridEffectActor); //���ɲ��������Ч��������
	}

	GridInBoard.Empty(); //�����Ϸ�������������


	const TSubclassOf<AGridEffectActor> GridEffectActorClass = LoadClass<AGridEffectActor>(
		this,TEXT("Blueprint'/Game/Clotho/Actors/BP_GridEffectActor.BP_GridEffectActor_C'")); //ʹ��ָ����ͼ��������Ϸ���ϵ�����Ч��
	const FVector BoardGridStepRotate(BoardGridStep.Y,-BoardGridStep.X,BoardGridStep.Z);  //����Ϸ����ת90��
	for (int i = 0; i < 6; ++i) //��������Ч��
	{
		for (int j = 0; j < 7; ++j)
		{
			FVector TargetLocation = ActorLocation + BoardStartPos + BoardGridStep * j + BoardGridStepRotate * i; //����Ŀ��λ��
			AGridEffectActor* GridEffectActor = GetWorld()->SpawnActor<AGridEffectActor>(GridEffectActorClass,TargetLocation,FRotator::ZeroRotator);
			GridInBoard.Add(GridEffectActor); //���ɲ��������Ч��������
		}
	}
}

void AGridEffectManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AGridEffectManager::ShowGridEffect(bool Show,bool bIsSelf)
{
	for (int32 i=0;i<8;++i) //�����ȴ�����
	{
		GridInWaiting[i]->SetShowEffect(Show); //���ݲ��������Ƿ���ʾ
	}

	if (UClothoFunctionLibrary::GetCurrentGameState(this) == EGameState::Egs_Deploy) //���Ϊ����׶�
	{
		for (int32 i=0;i<21;++i) //������Ϸ��
		{
			GridInBoard[i]->SetShowEffect(Show); //���ݲ��������Ƿ���ʾ
		}
	}
}

FVector AGridEffectManager::GetGridLocationByIndex(int32 Index)
{
	return GridInWaiting[Index]->GetActorLocation(); //����Ŀ�������λ��
}

int32 AGridEffectManager::GetGridIndex(AGridEffectActor* GridEffectActor, bool& bIsWaiting)
{
	int32 Index = GridInWaiting.Find(GridEffectActor); //�ڵȴ������в���
	if (Index != INDEX_NONE)
	{
		bIsWaiting = true; //����Ϊ�ȴ�״̬
		return Index;
	}

	Index = GridInBoard.Find(GridEffectActor); //��������Ϸ���ϲ���
	bIsWaiting = false; //���ǵȴ�״̬
	return Index;
}

FVector AGridEffectManager::GetBoardGridLocationByIndex(int32 Index)
{
	return GridInBoard[Index]->GetActorLocation(); //������������λ��
}
