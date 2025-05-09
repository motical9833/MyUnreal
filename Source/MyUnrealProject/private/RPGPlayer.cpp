// Fill out your copyright notice in the Description page of Project Settings.


#include "RPGPlayer.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "PlayerAnim.h"
#include "MyUnrealProject.h"
#include "TimerManager.h"
#include "Bullet.h"

// Sets default values
ARPGPlayer::ARPGPlayer()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// 1. 스켈레탈메시 데이터 불러오기
	ConstructorHelpers::FObjectFinder<USkeletalMesh> tempMesh(TEXT("/Script/Engine.SkeletalMesh'/Game/ParagonTwinblast/Characters/Heroes/TwinBlast/Meshes/TwinBlast.TwinBlast'"));
	if (tempMesh.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(tempMesh.Object);
		// 2. Mesh 컴포넌트의 위치와 회전값을 설정
		GetMesh()->SetRelativeLocationAndRotation(FVector(100.0f, 0.0f, -90.0f), FRotator(0.0f, -90.0f, 0.0f));
	}

	// 카메라 붙이기
	// springArm 컴포넌트 붙이기
	springArmComp = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComp"));
	springArmComp->SetupAttachment(GetCapsuleComponent());
	springArmComp->TargetArmLength = 500;
	springArmComp->bUsePawnControlRotation = false;
	springArmComp->bInheritYaw = false;
	springArmComp->bInheritPitch = false;
	springArmComp->bInheritRoll = false;


	// camera 컴포넌트 붙이기
	rpgCamComp = CreateDefaultSubobject<UCameraComponent>(TEXT("RpgCamComp"));
	rpgCamComp->SetupAttachment(springArmComp);
	rpgCamComp->bUsePawnControlRotation = false;
	rpgCamComp->SetRelativeLocationAndRotation(FVector(500.0f, 900.0f, 300.0f), FRotator(-20.0f, -90.0f, 0.0f));

	// CharacterMovement 조절
	GetCharacterMovement()->bOrientRotationToMovement = true;
	// Yaw 기준 초당 720도 회전
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 720.0f, 0.0f);

	// 기본 공격 체크 bool 배열 초기화
	isNomalAttackArrs.Init(false, 4);
}

// Called when the game starts or when spawned
void ARPGPlayer::BeginPlay()
{
	Super::BeginPlay();

	// PlayerAnim 가져오기
	playerAnim = Cast<UPlayerAnim>(GetMesh()->GetAnimInstance());
	if (!playerAnim)
	{
		PRINT_LOG(TEXT("%s"), TEXT("Non playerAnim"));
	}
}

// Called every frame
void ARPGPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (isDvasion)
	{
		StartDash(DeltaTime);
	}
	else
	{
		// 플레이어 이동
		direction = FTransform(GetControlRotation()).TransformVector(direction);
		AddMovementInput(direction);
		direction = FVector::ZeroVector;
	}
}

// Called to bind functionality to input
void ARPGPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// 좌우 입력 이벤트 처리 함수 바인딩
	PlayerInputComponent->BindAxis(TEXT("Horizontal"), this, &ARPGPlayer::InputHorizontal);
	// 상하 입력 이벤트 처리 함수 바인딩
	PlayerInputComponent->BindAxis(TEXT("Vertical"), this, &ARPGPlayer::InputVertical);
	// 점프 입력 이벤트 처리 함수 바인딩
	PlayerInputComponent->BindAction(TEXT("Jump"), IE_Pressed, this, &ARPGPlayer::InputJump);
	// 회피 입력 이벤트 처리 함수 바인딩
	PlayerInputComponent->BindAction(TEXT("Evasion"), IE_Pressed, this, &ARPGPlayer::InputEvasion);
	// 기본 공격 입력 이벤트 처리 함수 바인딩
	PlayerInputComponent->BindAction(TEXT("Attack"), IE_Pressed, this, &ARPGPlayer::InputAttack);

}

// 좌우 입력 이벤트 처리 함수
void ARPGPlayer::InputHorizontal(float value)
{
	direction.X = value;
}

// 상하 입력 이벤트 처리 함수
void ARPGPlayer::InputVertical(float value)
{
	direction.Y = value;
}

void ARPGPlayer::InputJump()
{
	Jump();
}

void ARPGPlayer::InputEvasion()
{
	// 쿨타임
	if (!isDvasion && !GetCharacterMovement()->IsFalling())
	{
		isDvasion = true;
		// 바라보는 방향
		dashDir = GetActorForwardVector();
		GetWorldTimerManager().SetTimer(coolDownTimerHandle, this, &ARPGPlayer::ResetCoolDown, delayDvasionTime, false);
		GetWorldTimerManager().SetTimer(inVulTimerHandle, this, &ARPGPlayer::ResetInVulTime, dashInVulTime, false);
		// 애니메이션 실행
		playerAnim->StartEvasionAnimation();
		// 무적 적용
		playerAnim->InVulStart();
	}
}

void ARPGPlayer::ResetCoolDown()
{
	isDvasion = false;
	coolDownRemaining = 0.0f;
}

void ARPGPlayer::ResetInVulTime()
{
	playerAnim->InVulEnd();
}

void ARPGPlayer::StartDash(float DeltaTime)
{
	FVector NewLocation = GetActorLocation() + (dashDir * dashSpeed * DeltaTime);
	SetActorLocation(NewLocation, true);
}

void ARPGPlayer::StopDash()
{
	// 추후 필요시 추가 변경가능 -> 대쉬로 무적 회피후 공격하여 특수 공격 등등....
}

void ARPGPlayer::BulletFire()
{
	// 총알 발사 로직 처리
	FTransform firePosition = GetMesh()->GetSocketTransform(TEXT("FirePosition"), RTS_World);
	GetWorld()->SpawnActor<ABullet>(bulletFactory, firePosition);
}

void ARPGPlayer::InputAttack()
{
	// 기본 공격 로직 처리
	BulletFire();
	playerAnim->StartAttackAnimation();
}