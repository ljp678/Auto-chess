// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "ClothoPlayerController.generated.h"

struct FPieceCoor;
class AGridEffectActor;
class APawnBase;
class ACameraDirector;
/**
 * ��ҿ�������
 */
UCLASS()
class CLOTHO_API AClothoPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	AClothoPlayerController();

	virtual void ClientWasKicked_Implementation(const FText& KickReason) override;// ���߳���Ϸʱ�Ŀͻ���ʵ��

	UFUNCTION(Client, Reliable)
	void RefreshShopPiece();// ˢ���̵����ӵĿͻ���ʵ��

	UFUNCTION(Client, Reliable)
	void RefreshShopUI();// ˢ���̵�UI�Ŀͻ���ʵ��

	UFUNCTION(Client, Reliable)
	void SetShopUIPieceVisible(ESlateVisibility SlateVisibility);// �����̵�UI���ӿɼ��ԵĿͻ���ʵ��

	UFUNCTION(Server, Reliable, WithValidation)
	void UserBuyPiece(int32 PieceIndex);// �û��������ӵķ����ʵ��

	bool ControllerHasFocusPiece() const;// �������Ƿ��н������ӵļ��

	void SpawnEnvironmentPieces(FPieceCoor PieceCoor);// ��ָ��λ�����ɻ������ӵĺ���

	void SpawnPlayerPiecesAsEnvironmentPieces(int32 TargetPlayerIndex);// �������������Ϊ�������ӵĺ���

	UFUNCTION(BlueprintCallable, Client, Reliable, meta = (DisplayName = ServerChangeCamera))
	void Server_ChangeCamera(int32 Index);// ����˸ı�����ĺ���

	void GetAndShowRankUI();// ��ȡ����ʾ����UI�ĺ���

	UFUNCTION(Client, Reliable)
	void StartDeployCountDownUI();// �������𵹼�ʱUI�Ŀͻ���ʵ��

	UFUNCTION(Client, Reliable)
	void StartFightCountDownUI();// ����ս������ʱUI�Ŀͻ���ʵ��
protected:
	uint8 bMoveToMouseCursor : 1;// �ƶ�������־λ

	uint8 bHaveSpawnedActor : 1;// �Ƿ�������Actor��־λ

	UPROPERTY()
	ACameraDirector* CameraDirector;// ����ܼ����

	UPROPERTY(VisibleAnywhere)
	APawnBase* FocusPiece;// ��������

	UPROPERTY()
	AGridEffectActor* FocusGrid;// ��������

	FVector PieceOriginLocation;// ����ԭʼλ��

	uint8 bHasDragPiece : 1;// �Ƿ�������ק���ӱ�־λ

	uint8 bFocusPieceIsWaiting : 1;// ���������Ƿ�ȴ���־λ

	int32 FocusPieceIndex;// �������ӵ�����

protected:
	virtual void PlayerTick(float DeltaTime) override;// ÿ֡���õĺ���
	virtual void SetupInputComponent() override;// ������������ĺ���

	virtual void OnPossess(APawn* InPawn) override;// ����������Pawnʱ���õĺ���

	void MoveToMouseCursor(FHitResult HitResult);// �ƶ��������λ�õĺ���

	void SetNewMoveDestination(const FVector DestLocation);// �������ƶ�Ŀ��λ�õĺ���

	void OnSetDestinationPressed();
	void OnSetDestinationReleased();

	UFUNCTION(BlueprintCallable)
	void OnLeftMouseClickPressed();// ������������µĺ���

	void SpawnMouseClickDecal(FHitResult HitResult);// ����������ۼ��ĺ���

	void CheckPieceDropPos(FHitResult HitResult);// ������ӷ���λ�õĺ���

	void CheckToMove(const FVector DestLocation);// �ƶ����ӵĺ���

	UFUNCTION(Server, Reliable)
	void Server_SetNewMoveDestination(const FVector DestLocation);// ������������ƶ�Ŀ��λ�õĺ���



	ACameraDirector* GetCameraDirector();// ��ȡ�������ĺ���

	UFUNCTION(Server, Reliable)
	void Server_StartGame();// ����˿�ʼ��Ϸ�ĺ���

	void StartGame();// ��ʼ��Ϸ�ĺ���

	UFUNCTION(Server, Reliable)
	void Server_ToggleState();// ������л�״̬�ĺ���

	void ToggleState(); // �л���Ϸ״̬�ĺ���

	UFUNCTION(Client, Reliable)
	void ShowRankUI(int32 Rank);// �ͻ�����ʾ����UI�ĺ���

	UFUNCTION(BlueprintImplementableEvent)
	void BlueprintShowRankUI(int32 Rank);// ��ͼ����ʾ����UI���¼�

public:
	UFUNCTION(BlueprintCallable, meta = (DisplayName = ClothoChangeCamera))
	void ChangeCamera(int32 Index);// �ı�����ĺ���

	UFUNCTION(BlueprintCallable)
	void OnClickedStartGame();// �����ʼ��Ϸ��ť�ĺ���

	void SetFocusPiece(APawnBase* _FocusPiece);// ���ý������ӵĺ���

	UFUNCTION(BlueprintCallable)
	void OnClickedToggleState(); // ����л�״̬��ť�ĺ����������ڲ��ԣ�
};
