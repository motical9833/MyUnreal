// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "RPGPlayer.generated.h"

UCLASS()
class MYUNREALPROJECT_API ARPGPlayer : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ARPGPlayer();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

public:
	// 좌우 이동 입력 이벤트 처리 함수
	void InputHorizontal(float value);
	// 상하 입력 이벤트 처리 함수
	void InputVertical(float value);
	// 점프 입력 이벤트 처리 함수
	void InputJump();
	// 회피 입력 이벤트 처리 함수
	void InputEvasion();
	// 쿨타임 리셋
	void ResetCoolDown();

public:
	UPROPERTY(VisibleAnywhere, Category = "Camera")
	class USpringArmComponent* springArmComp;
	UPROPERTY(VisibleAnywhere, Category = "Camera")
	class UCameraComponent* rpgCamComp;
	UPROPERTY()
	class UPlayerAnim* playerAnim;

	// 이동 속도
	UPROPERTY(EditAnywhere, Category = "PlayerSetting")
	float moveSpeed = 600;
	// 이동 방향
	FVector direction;
	// 회피 후딜레이
	UPROPERTY(EditAnywhere, Category = "PlayerSetting")
	float delayDvasionTime = 2.0f;
	float coolDownRemaining = 0.0f;
	bool isDvasion = false;
	FTimerHandle coolDownTimerHandle;

};