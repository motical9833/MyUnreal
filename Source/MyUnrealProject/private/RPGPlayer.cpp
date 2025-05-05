// Fill out your copyright notice in the Description page of Project Settings.


#include "RPGPlayer.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "PlayerAnim.h"
#include "MyUnrealProject.h"
#include "TimerManager.h"

// Sets default values
ARPGPlayer::ARPGPlayer()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// 1. ���̷�Ż�޽� ������ �ҷ�����
	ConstructorHelpers::FObjectFinder<USkeletalMesh> tempMesh(TEXT("/Script/Engine.SkeletalMesh'/Game/ParagonTwinblast/Characters/Heroes/TwinBlast/Meshes/TwinBlast.TwinBlast'"));
	if (tempMesh.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(tempMesh.Object);
		// 2. Mesh ������Ʈ�� ��ġ�� ȸ������ ����
		GetMesh()->SetRelativeLocationAndRotation(FVector(0.0f, 0.0f, -90.0f), FRotator(0.0f, -90.0f, 0.0f));
	}

	// ī�޶� ���̱�
	// springArm ������Ʈ ���̱�
	springArmComp = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComp"));
	springArmComp->SetupAttachment(GetCapsuleComponent());
	springArmComp->TargetArmLength = 500;
	springArmComp->bUsePawnControlRotation = false;
	springArmComp->bInheritYaw = false;
	springArmComp->bInheritPitch = false;
	springArmComp->bInheritRoll = false;


	// camera ������Ʈ ���̱�
	rpgCamComp = CreateDefaultSubobject<UCameraComponent>(TEXT("RpgCamComp"));
	rpgCamComp->SetupAttachment(springArmComp);
	rpgCamComp->bUsePawnControlRotation = false;
	rpgCamComp->SetRelativeLocationAndRotation(FVector(500.0f, 900.0f, 300.0f), FRotator(-20.0f, -90.0f, 0.0f));

	// CharacterMovement ����
	GetCharacterMovement()->bOrientRotationToMovement = true;
	// Yaw ���� �ʴ� 720�� ȸ��
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 720.0f, 0.0f);
}

// Called when the game starts or when spawned
void ARPGPlayer::BeginPlay()
{
	Super::BeginPlay();

	// PlayerAnim ��������
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
		FVector NewLocation = GetActorLocation() + (dashDir * dashSpeed * DeltaTime);
		SetActorLocation(NewLocation, true);
	}
	else
	{
		// �÷��̾� �̵�
		direction = FTransform(GetControlRotation()).TransformVector(direction);
		AddMovementInput(direction);
		direction = FVector::ZeroVector;
	}
}

// Called to bind functionality to input
void ARPGPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// �¿� �Է� �̺�Ʈ ó�� �Լ� ���ε�
	PlayerInputComponent->BindAxis(TEXT("Horizontal"), this, &ARPGPlayer::InputHorizontal);
	// ���� �Է� �̺�Ʈ ó�� �Լ� ���ε�
	PlayerInputComponent->BindAxis(TEXT("Vertical"), this, &ARPGPlayer::InputVertical);
	// ���� �Է� �̺�Ʈ ó�� �Լ� ���ε�
	PlayerInputComponent->BindAction(TEXT("Jump"), IE_Pressed, this, &ARPGPlayer::InputJump);
	// ȸ�� �Է� �̺�Ʈ ó�� �Լ� ���ε�
	PlayerInputComponent->BindAction(TEXT("Evasion"), IE_Pressed, this, &ARPGPlayer::InputEvasion);
}

// �¿� �Է� �̺�Ʈ ó�� �Լ�
void ARPGPlayer::InputHorizontal(float value)
{
	direction.X = value;
}

// ���� �Է� �̺�Ʈ ó�� �Լ�
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
	// ��Ÿ��
	if (!isDvasion && !GetCharacterMovement()->IsFalling())
	{
		isDvasion = true;
		coolDownRemaining = delayDvasionTime;
		// �ٶ󺸴� ����
		dashDir = GetActorForwardVector();
		GetWorldTimerManager().SetTimer(coolDownTimerHandle, this, &ARPGPlayer::ResetCoolDown, delayDvasionTime, false);
		// �뽬 ó��
		StartDash();
		// �ִϸ��̼� ����
		playerAnim->StartEvasionAnimation();
		// ���� ����
		playerAnim->InVulStart();
	}
}

void ARPGPlayer::ResetCoolDown()
{
	isDvasion = false;
	coolDownRemaining = 0.0f;
	playerAnim->InVulEnd();
}

void ARPGPlayer::StartDash()
{
	//FVector NewLocation = GetActorLocation() + (dashDir * dashSpeed * detatime);
	//SetActorLocation(NewLocation, true);

	//FVector lauchVelocity = GetActorForwardVector() * 3000.0f;
	//LaunchCharacter(lauchVelocity, true, false);
}

void ARPGPlayer::StopDash()
{
	// ���� �ʿ�� �߰� ���氡�� -> �뽬�� ���� ȸ���� �����Ͽ� Ư�� ���� ���....
}