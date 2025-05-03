// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "PlayerAnim.generated.h"

class ARPGPlayer;
class UCharacterMovementComponent;
/**
 * 
 */
UCLASS()
class MYUNREALPROJECT_API UPlayerAnim : public UAnimInstance
{
	GENERATED_BODY()
	
public:
	// �� ������ ���ŵǴ� �Լ�
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

public:
	void StartEvasionAnimation();
	bool GetIsEvasion() { return isEvasion; }
public:
	UFUNCTION(BlueprintCallable, Category = "FSMEvent")
	void EndEvasionAnimation();

public:
	// �÷��̾�
	UPROPERTY()
	ARPGPlayer* player;
	UPROPERTY()
	UCharacterMovementComponent* movement;
	// �÷��̾� �ӵ�
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlayerAnim")
	float speed = 0;
	// ���� ��������
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlayerAnim")
	bool isInAir = false;
	// ������ �ϰ� ��������
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlayerAnim")
	bool isFallingDown = false;
	// �ٴ� ��������
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlayerAnim")
	bool isRun = false;
	// ���� ��������
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlayerAnim")
	bool isStagger = false;
	// ȸ�� ��������
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlayerAnim")
	bool isEvasion = false;
};