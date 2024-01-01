// Fill out your copyright notice in the Description page of Project Settings.


#include "PawnAction_ChangeNav.h"

#include "Clotho/Pawn/PawnBase.h"

bool UPawnAction_ChangeNav::Start()
{
	Super::Start(); //基类初始化

	if (const APawnBase* Piece = Cast<APawnBase>(GetPawn())) //获取棋子
	{
		Piece->SetNavNull(bNavNull); //设置导航组件的通行状态
		Finish(EPawnActionResult::Success); //结束操作
		return true;
	}
	Finish(EPawnActionResult::Failed);//操作失败
	return false;
}
