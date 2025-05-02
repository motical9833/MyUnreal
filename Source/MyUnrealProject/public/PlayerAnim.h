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
	// �÷��̾� �ӵ�
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlayerAnim")
	float speed = 0;
	// ���� ��������
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlayerAnim")
	bool bJump = false;
	// �ٴ� ��������
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlayerAnim")
	bool bRun = false;
	// ���� ��������
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlayerAnim")
	bool bStagger = false;
};