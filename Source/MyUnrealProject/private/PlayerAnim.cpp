// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerAnim.h"
#include "RPGPlayer.h"
#include "MyUnrealProject.h"
#include "GameFramework/CharacterMovementComponent.h"


void UPlayerAnim::NativeUpdateAnimation(float DeltaSeconds)
{
	// �÷��̾� �̵� �ӵ��� ������ speed�� �Ҵ�
	// �� ��� ����
	auto ownerPawn = TryGetPawnOwner();
	// �÷��̾�� ĳ����
    auto player = Cast<ARPGPlayer>(ownerPawn);

	// ĳ���� ����
	if (player)
	{
		FVector velocity = player->GetVelocity();

		// �̵� �ӵ��� �ʿ�
		speed = velocity.Size();
		//PRINT_LOG(TEXT("My Log : %f"), speed);

		// �÷��̾ ���� ���߿� �ִ��� üũ
		auto movement = player->GetCharacterMovement();
		isInAir = movement->IsFalling();
	}
}