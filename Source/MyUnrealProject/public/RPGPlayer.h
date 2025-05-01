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

public:
	UPROPERTY(VisibleAnywhere, Category = "Camera")
	class USpringArmComponent* springArmComp;
	UPROPERTY(VisibleAnywhere, Category = "Camera")
	class UCameraComponent* rpgCamComp;

	// 이동 속도
	UPROPERTY(EditAnywhere, Category = "PlayerSetting")
	float moveSpeed = 600;
	// 이동 방향
	FVector direction;	
};