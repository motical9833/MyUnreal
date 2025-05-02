// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "PlayerAnim.generated.h"

/**
 * 
 */
UCLASS()
class MYUNREALPROJECT_API UPlayerAnim : public UAnimInstance
{
	GENERATED_BODY()
	

public:
	// 플레이어 속도
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlayerAnim")
	float speed = 0;
	// 점프 상태인지
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlayerAnim")
	bool bJump = false;
	// 뛰는 상태인지
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlayerAnim")
	bool bRun = false;
	// 경직 상태인지
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlayerAnim")
	bool bStagger = false;
};