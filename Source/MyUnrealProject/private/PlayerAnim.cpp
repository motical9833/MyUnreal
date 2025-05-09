// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerAnim.h"
#include "RPGPlayer.h"
#include "MyUnrealProject.h"
#include "GameFramework/CharacterMovementComponent.h"

void UPlayerAnim::NativeUpdateAnimation(float DeltaSeconds)
{
	if (!player)
	{
		// 플레이어 이동 속도를 가져와 speed에 할당
        // 폰 얻어 오기
		auto ownerPawn = TryGetPawnOwner();
		// 플레이어로 캐스팅
		player = Cast<ARPGPlayer>(ownerPawn);

		if (player)
		{
			movement = player->GetCharacterMovement();
		}
	}

	// 캐스팅 성공
	if (player)
	{
		FVector velocity = player->GetVelocity();

		// 이동 속도가 필요
		speed = velocity.Size();
		//PRINT_LOG(TEXT("My Log : %f"), speed);

		// 플레이어가 현재 공중에 있는지 체크
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
