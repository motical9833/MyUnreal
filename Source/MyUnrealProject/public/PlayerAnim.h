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
	// 매 프레임 갱신되는 함수
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

public:
	void StartEvasionAnimation();
	bool GetIsEvasion() { return isEvasion; }
public:
	UFUNCTION(BlueprintCallable, Category = "FSMEvent")
	void EndEvasionAnimation();

public:
	// 플레이어
	UPROPERTY()
	ARPGPlayer* player;
	UPROPERTY()
	UCharacterMovementComponent* movement;
	// 플레이어 속도
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlayerAnim")
	float speed = 0;
	// 점프 상태인지
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlayerAnim")
	bool isInAir = false;
	// 정프중 하강 상태인지
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlayerAnim")
	bool isFallingDown = false;
	// 뛰는 상태인지
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlayerAnim")
	bool isRun = false;
	// 경직 상태인지
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlayerAnim")
	bool isStagger = false;
	// 회피 상태인지
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlayerAnim")
	bool isEvasion = false;
};