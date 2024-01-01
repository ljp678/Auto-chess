// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "PawnBase.generated.h"

class UWidgetComponent;
class UNavModifierComponent;
class ADragonCharacter;
UENUM(BlueprintType)
enum class EPieceRole : uint8
{
	Epr_Fight,
	Epr_Waiting
};

class UBehaviorTree;
UCLASS()
class CLOTHO_API APawnBase : public ACharacter
{
	GENERATED_BODY()

public:

	APawnBase();

protected:

	virtual void BeginPlay() override;   //游戏开始的函数

public:

	virtual void Tick(float DeltaTime) override; //如果启用跟随，则每帧更新角色的位置


	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	FORCEINLINE UBehaviorTree* GetBehaviorTree() const { return BehaviorTree; }//返回行为树

	void RunBehaviourTree();//运行行为树

	void StopBehaviourTree();//停止行为树

	FORCEINLINE void SetHateIndex(int32 HateIndex_) { HateIndex = HateIndex_; }//设置仇恨值

	FORCEINLINE int32 GetHateIndex() const { return HateIndex; }//获取仇恨值

	FORCEINLINE bool Alive() const { return Health > 0; };//判断是否存活

	FORCEINLINE void SetPieceRole(EPieceRole PieceRole_) { PieceRole = PieceRole_; } //设置等待或攻击状态

	FORCEINLINE EPieceRole GetPieceRole() const { return PieceRole; } //返回状态

	void SetFollow(bool Follow_);

	void SetFollowPosition(FVector FollowPosition_); 

	FORCEINLINE int32 GetOwnerIndex() const { return OwnerIndex; }

	FORCEINLINE void SetOwnerIndex(int32 OwnerIndex_) { OwnerIndex = OwnerIndex_; }

	FORCEINLINE int32 GetSelfIndex() const { return SelfIndex; }

	FORCEINLINE void SetSelfIndex(int32 SelfIndex_) { SelfIndex = SelfIndex_; }

	FORCEINLINE float GetAttack() const { return Attack; } //获取攻击力

	FORCEINLINE float GetHealth() const { return Health; } //获取生命值

	// Play Montage and Return Duration
	UFUNCTION(NetMulticast, Reliable)
	virtual void Dance();//舞蹈动画

	FORCEINLINE float GetDanceMontageDuration() const { return DanceMontageDuration; }

	UFUNCTION(NetMulticast, Reliable)
	virtual void DoAttack(); //攻击动画

	FORCEINLINE float GetAttackMontageDuration() const { return AttackMontageDuration; }

	UFUNCTION(NetMulticast, Reliable)
	virtual void DoDeath(); //死亡动画

	FORCEINLINE float GetDeathMontageDuration() const { return DeathMontageDuration; }//返回未知参数

	void SetNavNull(bool bNull) const; //设置未知参数

	void OnGetDamage(float Damage); //处理受伤时的状态
	
	void OnDeathMontageFinished(); //死亡状态的处理
	
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override; 

	void ResetState();//重置状态

	UFUNCTION(NetMulticast, Reliable)
	void SetStateVisible(bool Visible); //设置状态是否可见
protected:
	UFUNCTION()
	virtual void OnBeginCursorOverEvent(UPrimitiveComponent* TouchedComponent);

	UFUNCTION()
	virtual void OnEndCursorOverEvent(UPrimitiveComponent* TouchedComponent);

	UFUNCTION()
	virtual void OnMeshClickedEvent(UPrimitiveComponent* TouchedComponent, FKey ButtonPressed);

	UFUNCTION()
	void StartInterpTimeline();

	void BindPieceFigure();

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly) 
	float MaxHealth;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly,Replicated)
	float Health;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float MaxMagic;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly,Replicated)
	float Magic;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float MagicIncrease;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float Attack;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float AttackSpeed;
	//AttackSpeed = AttackSpeedBase + AttackSpeedCoefficient * AttackSpeedIncrease;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float AttackSpeedCoefficient;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float AttackSpeedBase;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float AttackSpeedIncrease;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float AttackDistance;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float MagicPower;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float Defence;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float MagicDefence;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float MoveSpeed;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	int32 Level;

	UPROPERTY(EditAnywhere)
	UBehaviorTree* BehaviorTree; //行为树

	UPROPERTY(EditAnywhere)
	int32 HateIndex;  //仇恨值

	UPROPERTY(EditAnywhere)
	EPieceRole PieceRole;  //等待状态、战斗状态

	// UPROPERTY(VisibleAnywhere)
	FVector FollowPosition; //跟随位置，便于传入后的记录

	uint8 bFollow : 1;
	uint8 bIsSetDifference: 1;

	UPROPERTY(BlueprintReadWrite)
	FVector Difference; //两个位置之间的偏移

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly,Replicated)
	int32 OwnerIndex; //玩家索引（哪个人有这张卡）

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly,Replicated)
	int32 SelfIndex; //自身索引（卡牌独一无二的ID）


	float TimelineMax; //时间线的最大值

	float TimeCount; //当前时间

	UPROPERTY(VisibleAnywhere)
	UNavModifierComponent* NavModifierComponent; //导航修改组件

	UPROPERTY(VisibleAnywhere)
	UWidgetComponent* WidgetComponent; //UI组件

	// Montage
	UPROPERTY(EditDefaultsOnly)
	UAnimMontage* DanceMontage;
	UPROPERTY(EditDefaultsOnly)
	UAnimMontage* AttackMontage;
	UPROPERTY(EditDefaultsOnly)
	UAnimMontage* DeathMontage;


	// MontageDuration
	float DanceMontageDuration;
	float AttackMontageDuration;
	float DeathMontageDuration;
};
