// Fill out your copyright notice in the Description page of Project Settings.


#include "ClothoPlayerState.h"

#include "Kismet/KismetMathLibrary.h"
#include "Net/UnrealNetwork.h"
#include "Util/ClothoFunctionLibrary.h"

// 默认构造函数，初始化 ShopPieceIndex 数组
AClothoPlayerState::AClothoPlayerState()
{
	ShopPieceIndex.Init(-1, 5);
}
// 刷新商店棋子索引
void AClothoPlayerState::RefreshShopPieceIndex()
{
	for (int32 i = 0; i < 5; ++i)
	{
		ShopPieceIndex[i] = UKismetMathLibrary::RandomIntegerInRange(0,1);// 随机生成 0 或 1，并存储到 ShopPieceIndex 数组中
	}
}
// 设置需要在网络上同步的属性
void AClothoPlayerState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	// 将 ShopPieceIndex 数组标记为需要在网络上同步
	DOREPLIFETIME(AClothoPlayerState,ShopPieceIndex);
}
// 当 ShopPieceIndex 在网络上同步时调用
void AClothoPlayerState::OnRep_ShopPieceIndex()
{

}
