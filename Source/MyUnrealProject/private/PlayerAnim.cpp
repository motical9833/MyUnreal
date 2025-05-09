// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerAnim.h"
#include "RPGPlayer.h"
#include "MyUnrealProject.h"
#include "GameFramework/CharacterMovementComponent.h"

void UPlayerAnim::NativeUpdateAnimation(float DeltaSeconds)
{
	if (!player)
	{
		// �÷��̾� �̵� �ӵ��� ������ speed�� �Ҵ�
        // �� ��� ����
		auto ownerPawn = TryGetPawnOwner();
		// �÷��̾�� ĳ����
		player = Cast<ARPGPlayer>(ownerPawn);

		if (player)
		{
			movement = player->GetCharacterMovement();
		}
	}

	// ĳ���� ����
	if (player)
	{
		FVector velocity = player->GetVelocity();

		// �̵� �ӵ��� �ʿ�
		speed = velocity.Size();
		//PRINT_LOG(TEXT("My Log : %f"), speed);

		// �÷��̾ ���� ���߿� �ִ��� üũ
		isInAir = movement->IsFalling();
	}
}

void UPlayerAnim::StartEvasionAnimation()
{
	isEvasion = true;
}

void UPlayerAnim::EndEvasionAnimation()
{
	isEvasion = false;
}

void UPlayerAnim::EndRightHandFireAnimation()
{
	isAttack = false;
}
