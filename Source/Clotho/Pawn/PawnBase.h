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

	virtual void BeginPlay() override;   //��Ϸ��ʼ�ĺ���

public:

	virtual void Tick(float DeltaTime) override; //������ø��棬��ÿ֡���½�ɫ��λ��


	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	FORCEINLINE UBehaviorTree* GetBehaviorTree() const { return BehaviorTree; }//������Ϊ��

	void RunBehaviourTree();//������Ϊ��

	void StopBehaviourTree();//ֹͣ��Ϊ��

	FORCEINLINE void SetHateIndex(int32 HateIndex_) { HateIndex = HateIndex_; }//���ó��ֵ

	FORCEINLINE int32 GetHateIndex() const { return HateIndex; }//��ȡ���ֵ

	FORCEINLINE bool Alive() const { return Health > 0; };//�ж��Ƿ���

	FORCEINLINE void SetPieceRole(EPieceRole PieceRole_) { PieceRole = PieceRole_; } //���õȴ��򹥻�״̬

	FORCEINLINE EPieceRole GetPieceRole() const { return PieceRole; } //����״̬

	void SetFollow(bool Follow_);

	void SetFollowPosition(FVector FollowPosition_); 

	FORCEINLINE int32 GetOwnerIndex() const { return OwnerIndex; }

	FORCEINLINE void SetOwnerIndex(int32 OwnerIndex_) { OwnerIndex = OwnerIndex_; }

	FORCEINLINE int32 GetSelfIndex() const { return SelfIndex; }

	FORCEINLINE void SetSelfIndex(int32 SelfIndex_) { SelfIndex = SelfIndex_; }

	FORCEINLINE float GetAttack() const { return Attack; } //��ȡ������

	FORCEINLINE float GetHealth() const { return Health; } //��ȡ����ֵ

	// Play Montage and Return Duration
	UFUNCTION(NetMulticast, Reliable)
	virtual void Dance();//�赸����

	FORCEINLINE float GetDanceMontageDuration() const { return DanceMontageDuration; }

	UFUNCTION(NetMulticast, Reliable)
	virtual void DoAttack(); //��������

	FORCEINLINE float GetAttackMontageDuration() const { return AttackMontageDuration; }

	UFUNCTION(NetMulticast, Reliable)
	virtual void DoDeath(); //��������

	FORCEINLINE float GetDeathMontageDuration() const { return DeathMontageDuration; }//����δ֪����

	void SetNavNull(bool bNull) const; //����δ֪����

	void OnGetDamage(float Damage); //��������ʱ��״̬
	
	void OnDeathMontageFinished(); //����״̬�Ĵ���
	
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override; 

	void ResetState();//����״̬

	UFUNCTION(NetMulticast, Reliable)
	void SetStateVisible(bool Visible); //����״̬�Ƿ�ɼ�
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
	UBehaviorTree* BehaviorTree; //��Ϊ��

	UPROPERTY(EditAnywhere)
	int32 HateIndex;  //���ֵ

	UPROPERTY(EditAnywhere)
	EPieceRole PieceRole;  //�ȴ�״̬��ս��״̬

	// UPROPERTY(VisibleAnywhere)
	FVector FollowPosition; //����λ�ã����ڴ����ļ�¼

	uint8 bFollow : 1;
	uint8 bIsSetDifference: 1;

	UPROPERTY(BlueprintReadWrite)
	FVector Difference; //����λ��֮���ƫ��

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly,Replicated)
	int32 OwnerIndex; //����������ĸ��������ſ���

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly,Replicated)
	int32 SelfIndex; //�������������ƶ�һ�޶���ID��


	float TimelineMax; //ʱ���ߵ����ֵ

	float TimeCount; //��ǰʱ��

	UPROPERTY(VisibleAnywhere)
	UNavModifierComponent* NavModifierComponent; //�����޸����

	UPROPERTY(VisibleAnywhere)
	UWidgetComponent* WidgetComponent; //UI���

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
