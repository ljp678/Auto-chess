// Fill out your copyright notice in the Description page of Project Settings.


#include "PawnAction_Die.h"

#include "BehaviorTree/BlackboardComponent.h"
#include "Clotho/AI/PawnAIController.h"
#include "Clotho/Pawn/PawnBase.h"

UPawnAction_Die::UPawnAction_Die()
{
	bWantsTick = true;
	TimeCount = 0.f;
	Duration = 0.f;
}

bool UPawnAction_Die::Start()
{
	Super::Start();
	if (APawnBase* Piece = Cast<APawnBase>(GetPawn()))//获取操作
	{
		Piece->DoDeath(); //死亡动画开始
		Duration = Piece->GetDeathMontageDuration(); //获取时间
		TimeCount = 0.f;
		return Duration > 0.f;
	}

	Finish(EPawnActionResult::Failed);
	return false;
}

void UPawnAction_Die::Tick(float DeltaTime)
{
	TimeCount += DeltaTime; //时间改变
	if (TimeCount >= Duration)
	{
		APawnBase* Piece = Cast<APawnBase>(GetPawn());
		Piece->OnDeathMontageFinished(); //死亡操作结束后的操作
		AController* Controller = Piece->GetController(); //获取控制器
		if (Controller)
		{
			APawnAIController* PawnAIController = Cast<APawnAIController>(Controller);
			PawnAIController->GetBlackboardComponent()->SetValueAsBool(TEXT("HasDied"),true); //在行为树中标记死亡
		}
		
		Finish(EPawnActionResult::Success);
	}

}
