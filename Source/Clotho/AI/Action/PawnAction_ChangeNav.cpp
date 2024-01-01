// Fill out your copyright notice in the Description page of Project Settings.


#include "PawnAction_ChangeNav.h"

#include "Clotho/Pawn/PawnBase.h"

bool UPawnAction_ChangeNav::Start()
{
	Super::Start(); //�����ʼ��

	if (const APawnBase* Piece = Cast<APawnBase>(GetPawn())) //��ȡ����
	{
		Piece->SetNavNull(bNavNull); //���õ��������ͨ��״̬
		Finish(EPawnActionResult::Success); //��������
		return true;
	}
	Finish(EPawnActionResult::Failed);//����ʧ��
	return false;
}
