// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "DragonCharacter.generated.h"

class UWidgetComponent;
class AGridEffectActor;
class AGridEffectManager;						//跨场景管理actor实例，确保添加或放置actor的所有实例不会重叠、干扰或靠的太近
class APawnBase;								//用于创建新角色，并通过该管理器对象的函数AddPawn（）将其添加到游戏世界中
class UNavigationPath;
class USpringArmComponent;
class UCameraComponent;
UCLASS()
class CLOTHO_API ADragonCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	ADragonCharacter();//构造函数，设置角色的默认属性值

protected:
	virtual void BeginPlay() override;//在游戏开始或生成时调用的函数，用于初始化角色。				

	void CheckDeath();//检查角色是否死亡的函数
	void DestroyPieces();//销毁棋子的函数
public:
	virtual void Tick(float DeltaTime) override;//在每一帧调用的函数，用于处理与时间相关的逻辑


	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;//用于绑定输入功能的函数

	void SetPath(UNavigationPath* NewNavigationPath);//这个函数用于设置新的导航路径，以便角色能够按照这个路径进行移动

	void MoveToNextPoint(float DeltaTime);//该函数用于移动角色到导航路径上的下一个点。DeltaTime 是每一帧的时间间隔，用于平滑移动

	FORCEINLINE void SetPlayerIndex(int32 Index) { PlayerIndex = Index; }//用于设置角色的玩家索引，以标识不同的玩家

	FORCEINLINE int32 GetPlayerIndex() const { return PlayerIndex; }//用于获取角色的玩家索引

	FORCEINLINE bool GetIsMaster() const { return PlayerIndex == 0; }//用于检查当前角色是否是主角色

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;//用于定义需要在网络上传输的属性列表包括 PlayerIndex、PawnsInBoard、PawnsInWaiting 等

	void RunPawnsBehaviourTree();//用于启动与角色相关的行为树，以控制角色的行为和决策

	void StopPawnsBehaviourTree();//用于启动与角色相关的行为树，以控制角色的行为和决策

	APawnBase* GetValidatePawnInBoard(const APawnBase* OriginPiece);//

	APawnBase* GetValidateEnvironmentPieceInBoard(const APawnBase* OriginPiece);//这两个函数用于获取位于游戏板上的有效棋子涉及检查棋子的状态和位置等

	bool CheckPieceCanDrag(APawnBase* Piece, int32& Index, bool& bIsWaiting);//用于检查棋子是否可以拖动，并返回相关的信息，如棋子的索引、是否在等待区域等

	UFUNCTION(NetMulticast, Reliable)
	void BindGridEffectManager();//一个多播函数，用于在多个客户端上绑定

	void ShowGridEffect(bool Show, bool bIsSelf = true);//一个多播函数，用于显示或隐藏格子效果。

	int32 GetPieceIndexInWaiting(FVector& SpawnLocation);//用于获取在等待区域的棋子的索引，并提供生成位置信息

	void SetPieceInWaiting(int32 Index, APawnBase* Piece);//用于设置等待区域中指定索引的棋子

	UFUNCTION(NetMulticast, Reliable)
	void SetPieceByGrid(int32 GridIndex, bool bGridIsWaiting, FVector GridLocation, int32 Index, bool bIsWaiting, FVector OriginPosition);//一个多播函数，可能用于设置格子上的棋子信息

	UFUNCTION(Server, Reliable)
	void Server_SetPieceByGrid(int32 GridIndex, bool bGridIsWaiting, FVector GridLocation, int32 Index, bool bIsWaiting, FVector OriginPosition);//一个服务器端函数，用于设置格子上的棋子信息

	int32 GetGridIndex(AGridEffectActor* GridEffectActor, FVector& Location, bool& bGridIsWaiting);//

	FVector GetGridLocationByReverseIndex(int32 Index);//这两个函数用于获取与格子效果相关的信息，如位置、是否在等待区域等

	void SetEnvironmentPiece(APawnBase* Piece);

	void ClearEnvironmentPiece();//这两个函数用于设置和清除环境中的棋子

	FORCEINLINE void SetHateIndex(int32 HateIndex_) { HateIndex = HateIndex_; }//该函数用于设置当前敌人（仇恨目标）的索引

	void ChangeHealth(int32 Value);//用于更改角色的健康值

	void ResetPieces();//重置棋子

	void StartRunBehaviourTreeTimer();//启动与角色行为树相关的定时器

	void GotoOtherBoard(int32 TargetPlayerIndex);//用于切换到其他的棋盘

	UFUNCTION(BlueprintImplementableEvent)					
	void SetDragonLocationByIndex(int32 TargetPlayerIndex);//(蓝图实现）根据输入的参数 TargetPlayerIndex 设置龙的位置，用于在游戏中移动或调整龙的位置
	
	void SetDragonLocationAndCameraByIndex(int32 TargetPlayerIndex);//随角色移动设置相应的位置和摄像机

	FORCEINLINE TArray<APawnBase*> GetPiecesInBoard() const { return PawnsInBoard; }

	UFUNCTION(NetMulticast, Reliable)
	void SetStateVisible(bool Visible);//一个多播函数，用于设置角色的可见性状态

	FORCEINLINE bool Alive() const { return Health > 0; }//判断是否还活着
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Replicated)
	int32 PlayerIndex;	//玩家索引，用于标识不同的玩家。这个变量在实例化时会被设置为不同的值

	UPROPERTY(EditAnywhere, Replicated)
	TArray<APawnBase*> PawnsInBoard;//存储在游戏板上的棋子（APawnBase的子类）

	UPROPERTY(EditAnywhere, Replicated)
	TArray<APawnBase*> PawnsInWaiting;//存储在等待区域的棋子

	UPROPERTY(EditAnywhere, Replicated)
	TArray<APawnBase*> EnvironmentPieces;//存储处于环境中的棋子

	UPROPERTY(VisibleAnywhere)
	AGridEffectManager* GridEffectManager;//跨场景管理actor实例，确保添加或放置actor的所有实例不会重叠、干扰或靠的太近。

	UPROPERTY(VisibleAnywhere)
	int32 HateIndex;//当前敌人（仇恨目标）的索引

	UPROPERTY(VisibleAnywhere)
	UWidgetComponent* WidgetComponent;//一个可见的Widget组件，用于把角色与用户对象相关联

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Replicated)
	int32 Health;// 角色的当前健康值

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	int32 HealthMax;//最大健康值

private:

	UPROPERTY()
	UNavigationPath* NavigationPath;//导航路径,用于存储计算得到的路径，以便角色能够按照这个路径移动

	UPROPERTY()
	int32 TargetPointIndex;//用于表示角色当前导航路径中的目标点的索引

	FTimerHandle BehaviourTreeTimerHandle;//用于处理行为树的定时器句柄,用于管理角色行为树的定时器，例如在一定时间间隔内执行某些行为
};
