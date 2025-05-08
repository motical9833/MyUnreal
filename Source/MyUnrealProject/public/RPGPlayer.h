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
	// 무적 종료
	void ResetInVulTime();
	// 대쉬 시작
	void StartDash(float DeltaTime);
	// 대쉬 끝
	void StopDash();

	// 총알 발사 처리 함수
	void BulletFire();
	// 기본 공격 처리 함수
	void InputAttack();

	//UFUNCTION(BlueprintCallable, Category = "FSMEvent")
public:
	UPROPERTY(VisibleAnywhere, Category = "Camera")
	class USpringArmComponent* springArmComp;
	UPROPERTY(VisibleAnywhere, Category = "Camera")
	class UCameraComponent* rpgCamComp;
	UPROPERTY()
	class UPlayerAnim* playerAnim;
	// 플레이어 스켈레탈메시
	UPROPERTY(VisibleAnywhere, Category = "PlayerMesh")
	class USkeletalMeshComponent* playerMeshComp;

	// 이동 속도
	UPROPERTY(EditAnywhere, Category = "PlayerSetting")
	float moveSpeed = 600;
	// 이동 방향
	FVector direction;
	// 회피 후딜레이
	UPROPERTY(EditAnywhere, Category = "PlayerSetting")
	float delayDvasionTime = 1.0f;
	float coolDownRemaining = 0.0f;
	bool isDvasion = false;
	FTimerHandle coolDownTimerHandle;

	// 회피 변수
	FTimerHandle inVulTimerHandle;
	float dashInVulTime = 0.5f;
	float dashInVulRemaining = 0.0f;
	// 회피 이동
	float dashSpeed = 400.0f;
	float dashDuration = 1.0f;
	// 회피 이동 방향
	FVector dashDir;

	// 총알 공장
	UPROPERTY(EditDefaultsOnly, Category = "BulletFactory")
	TSubclassOf<class ABullet> bulletFactory;
};