// Fill out your copyright notice in the Description page of Project Settings.


#include "ShopPieceWidget.h"

#include "Clotho/Manager/PieceInfoManager.h"
#include "Clotho/Util/ClothoFunctionLibrary.h"
#include "Components/Button.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"

UShopPieceWidget::UShopPieceWidget(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
	PieceIndex = -1; //初始化索引
}

void UShopPieceWidget::NativeConstruct()
{
	Super::NativeConstruct(); //调用父类的构造函数

	BuyButton->OnClicked.AddDynamic(this,&UShopPieceWidget::BuyButtonOnClickedEvent); //绑定点击事件
}

void UShopPieceWidget::SetPieceIndex(int32 PieceIndex_)
{
	PieceIndex = PieceIndex_;//设置棋子的索引
}

void UShopPieceWidget::RefreshUI()
{
	if (!CheckPieceValidate()) //如果棋子无效
	{
		SetVisibility(ESlateVisibility::Hidden); //隐藏小部件
		BuyButton->SetIsEnabled(false); //禁用购买按钮
		return;
	}

	BuyButton->SetIsEnabled(true); //启用按钮
	SetVisibility(ESlateVisibility::Visible); //显示

	FPieceData* PieceData = UClothoFunctionLibrary::GetPieceInfoManager(this)->GetPieceDataByID(PieceIndex);//获取棋子信息

	PieceInfo->SetBrushFromTexture(PieceData->InfoBg); //设置图片
	Text_Name->SetText(PieceData->PieceName); //设置名字
	Text_Cost->SetText(FText::AsNumber(PieceData->Cost)); //设置花费
}

bool UShopPieceWidget::CheckPieceValidate()
{
	int32 MaxIndex = UClothoFunctionLibrary::GetPieceInfoManager(this)->GetValidateMaxPieceID();
	return PieceIndex >= 0 && PieceIndex < MaxIndex; //检测棋子是否有效
}

void UShopPieceWidget::BuyButtonOnClickedEvent()
{

	//todo 检测金币是否够用

	//todo 检测数组已满
	
	SetVisibility(ESlateVisibility::Hidden); //隐藏小部件
	BuyButton->SetIsEnabled(false); //禁用购买按钮

	AClothoPlayerController* ClothoPlayerController = UClothoFunctionLibrary::GetClothoPlayerController(this); //获取玩家控制器
	ClothoPlayerController->UserBuyPiece(PieceIndex); //传递棋子index
	
}
