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
	// �¿� �̵� �Է� �̺�Ʈ ó�� �Լ�
	void InputHorizontal(float value);
	// ���� �Է� �̺�Ʈ ó�� �Լ�
	void InputVertical(float value);
	// ���� �Է� �̺�Ʈ ó�� �Լ�
	void InputJump();
	// ȸ�� �Է� �̺�Ʈ ó�� �Լ�
	void InputEvasion();
	// ��Ÿ�� ����
	void ResetCoolDown();

public:
	UPROPERTY(VisibleAnywhere, Category = "Camera")
	class USpringArmComponent* springArmComp;
	UPROPERTY(VisibleAnywhere, Category = "Camera")
	class UCameraComponent* rpgCamComp;
	UPROPERTY()
	class UPlayerAnim* playerAnim;

	// �̵� �ӵ�
	UPROPERTY(EditAnywhere, Category = "PlayerSetting")
	float moveSpeed = 600;
	// �̵� ����
	FVector direction;
	// ȸ�� �ĵ�����
	UPROPERTY(EditAnywhere, Category = "PlayerSetting")
	float delayDvasionTime = 2.0f;
	float coolDownRemaining = 0.0f;
	bool isDvasion = false;
	FTimerHandle coolDownTimerHandle;

};