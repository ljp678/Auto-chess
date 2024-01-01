// Fill out your copyright notice in the Description page of Project Settings.


#include "ClothoPlayerState.h"

#include "Kismet/KismetMathLibrary.h"
#include "Net/UnrealNetwork.h"
#include "Util/ClothoFunctionLibrary.h"

// Ĭ�Ϲ��캯������ʼ�� ShopPieceIndex ����
AClothoPlayerState::AClothoPlayerState()
{
	ShopPieceIndex.Init(-1, 5);
}
// ˢ���̵���������
void AClothoPlayerState::RefreshShopPieceIndex()
{
	for (int32 i = 0; i < 5; ++i)
	{
		ShopPieceIndex[i] = UKismetMathLibrary::RandomIntegerInRange(0,1);// ������� 0 �� 1�����洢�� ShopPieceIndex ������
	}
}
// ������Ҫ��������ͬ��������
void AClothoPlayerState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	// �� ShopPieceIndex ������Ϊ��Ҫ��������ͬ��
	DOREPLIFETIME(AClothoPlayerState,ShopPieceIndex);
}
// �� ShopPieceIndex ��������ͬ��ʱ����
void AClothoPlayerState::OnRep_ShopPieceIndex()
{

}
