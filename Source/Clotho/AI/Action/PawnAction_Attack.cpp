// Fill out your copyright notice in the Description page of Project Settings.


#include "PawnAction_Attack.h"

#include "Clotho/Pawn/PawnBase.h"

UPawnAction_Attack::UPawnAction_Attack()
{
	bWantsTick = true;
	TimeCount = 0.f;
	Duration = 0.f;
}

bool UPawnAction_Attack::Start()
{
	Super::Start(); //基类初始化
	if (APawnBase* Piece = Cast<APawnBase>(GetPawn())) //获取棋子
	{
		Piece->DoAttack(); //进行攻击
		Duration = Piece->GetAttackMontageDuration(); //获取攻击持续时间
		TimeCount = 0.f; //初始化目前的攻击时间
		return Duration > 0.f;
	}

	Finish(EPawnActionResult::Failed);//动作执行失败
	return false;
}

void UPawnAction_Attack::Tick(float DeltaTime)
{
	TimeCount += DeltaTime; //时间增加，过程由蓝图实现
	if (TimeCount >= Duration)
	{
		Finish(EPawnActionResult::Success); //攻击结束
	}
}
