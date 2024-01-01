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
 * 玩家控制器类
 */
UCLASS()
class CLOTHO_API AClothoPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	AClothoPlayerController();

	virtual void ClientWasKicked_Implementation(const FText& KickReason) override;// 被踢出游戏时的客户端实现

	UFUNCTION(Client, Reliable)
	void RefreshShopPiece();// 刷新商店棋子的客户端实现

	UFUNCTION(Client, Reliable)
	void RefreshShopUI();// 刷新商店UI的客户端实现

	UFUNCTION(Client, Reliable)
	void SetShopUIPieceVisible(ESlateVisibility SlateVisibility);// 设置商店UI棋子可见性的客户端实现

	UFUNCTION(Server, Reliable, WithValidation)
	void UserBuyPiece(int32 PieceIndex);// 用户购买棋子的服务端实现

	bool ControllerHasFocusPiece() const;// 控制器是否有焦点棋子的检查

	void SpawnEnvironmentPieces(FPieceCoor PieceCoor);// 在指定位置生成环境棋子的函数

	void SpawnPlayerPiecesAsEnvironmentPieces(int32 TargetPlayerIndex);// 生成玩家棋子作为环境棋子的函数

	UFUNCTION(BlueprintCallable, Client, Reliable, meta = (DisplayName = ServerChangeCamera))
	void Server_ChangeCamera(int32 Index);// 服务端改变相机的函数

	void GetAndShowRankUI();// 获取并显示排名UI的函数

	UFUNCTION(Client, Reliable)
	void StartDeployCountDownUI();// 启动部署倒计时UI的客户端实现

	UFUNCTION(Client, Reliable)
	void StartFightCountDownUI();// 启动战斗倒计时UI的客户端实现
protected:
	uint8 bMoveToMouseCursor : 1;// 移动鼠标光标标志位

	uint8 bHaveSpawnedActor : 1;// 是否已生成Actor标志位

	UPROPERTY()
	ACameraDirector* CameraDirector;// 相机总监对象

	UPROPERTY(VisibleAnywhere)
	APawnBase* FocusPiece;// 焦点棋子

	UPROPERTY()
	AGridEffectActor* FocusGrid;// 焦点网格

	FVector PieceOriginLocation;// 棋子原始位置

	uint8 bHasDragPiece : 1;// 是否正在拖拽棋子标志位

	uint8 bFocusPieceIsWaiting : 1;// 焦点棋子是否等待标志位

	int32 FocusPieceIndex;// 焦点棋子的索引

protected:
	virtual void PlayerTick(float DeltaTime) override;// 每帧调用的函数
	virtual void SetupInputComponent() override;// 设置输入组件的函数

	virtual void OnPossess(APawn* InPawn) override;// 控制器持有Pawn时调用的函数

	void MoveToMouseCursor(FHitResult HitResult);// 移动到鼠标光标位置的函数

	void SetNewMoveDestination(const FVector DestLocation);// 设置新移动目标位置的函数

	void OnSetDestinationPressed();
	void OnSetDestinationReleased();

	UFUNCTION(BlueprintCallable)
	void OnLeftMouseClickPressed();// 鼠标左键点击按下的函数

	void SpawnMouseClickDecal(FHitResult HitResult);// 生成鼠标点击痕迹的函数

	void CheckPieceDropPos(FHitResult HitResult);// 检查棋子放置位置的函数

	void CheckToMove(const FVector DestLocation);// 移动棋子的函数

	UFUNCTION(Server, Reliable)
	void Server_SetNewMoveDestination(const FVector DestLocation);// 服务端设置新移动目标位置的函数



	ACameraDirector* GetCameraDirector();// 获取相机对象的函数

	UFUNCTION(Server, Reliable)
	void Server_StartGame();// 服务端开始游戏的函数

	void StartGame();// 开始游戏的函数

	UFUNCTION(Server, Reliable)
	void Server_ToggleState();// 服务端切换状态的函数

	void ToggleState(); // 切换游戏状态的函数

	UFUNCTION(Client, Reliable)
	void ShowRankUI(int32 Rank);// 客户端显示排名UI的函数

	UFUNCTION(BlueprintImplementableEvent)
	void BlueprintShowRankUI(int32 Rank);// 蓝图中显示排名UI的事件

public:
	UFUNCTION(BlueprintCallable, meta = (DisplayName = ClothoChangeCamera))
	void ChangeCamera(int32 Index);// 改变相机的函数

	UFUNCTION(BlueprintCallable)
	void OnClickedStartGame();// 点击开始游戏按钮的函数

	void SetFocusPiece(APawnBase* _FocusPiece);// 设置焦点棋子的函数

	UFUNCTION(BlueprintCallable)
	void OnClickedToggleState(); // 点击切换状态按钮的函数（仅用于测试）
};
