// Copyright Epic Games, Inc. All Rights Reserved.

#include "MyUnrealProjectGameMode.h"
#include "MyUnrealProjectCharacter.h"
#include "UObject/ConstructorHelpers.h"
#include "MyUnrealProject.h"

AMyUnrealProjectGameMode::AMyUnrealProjectGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
