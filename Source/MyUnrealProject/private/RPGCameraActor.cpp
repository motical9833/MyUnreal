// Fill out your copyright notice in the Description page of Project Settings.


#include "RPGCameraActor.h"
#include "Camera/CameraComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ARPGCameraActor::ARPGCameraActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));
	RootComponent = CameraComponent;

	CameraComponent->bUsePawnControlRotation = false;

	offset = FVector(-200, 0, 300);
}

// Called when the game starts or when spawned
void ARPGCameraActor::BeginPlay()
{
	Super::BeginPlay();

	// 추적할 대상찾기
	if (!targetActor)
	{
		targetActor = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
	}
}

// Called every frame
void ARPGCameraActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (targetActor)
	{
		FVector TargetLocation = targetActor->GetActorLocation();
		SetActorLocation(TargetLocation + offset);
	}
}

