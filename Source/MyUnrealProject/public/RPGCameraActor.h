// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RPGCameraActor.generated.h"

UCLASS()
class MYUNREALPROJECT_API ARPGCameraActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ARPGCameraActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


public:
	
	// ������ �÷��̾�
	UPROPERTY(EditAnywhere, Category = "Target")
	AActor* targetActor;

	// ī�޶� ��ġ ������
	UPROPERTY(EditAnywhere, Category = "Target")
	FVector offset;

	UPROPERTY(VisibleAnywhere)
	class UCameraComponent* CameraComponent;
};
