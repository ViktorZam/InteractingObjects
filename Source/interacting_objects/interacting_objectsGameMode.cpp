// Copyright Epic Games, Inc. All Rights Reserved.

#include "interacting_objectsGameMode.h"
#include "interacting_objectsCharacter.h"
#include "UInterfacePlayers.h"
#include "UObject/ConstructorHelpers.h"


Ainteracting_objectsGameMode::Ainteracting_objectsGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}

	static ConstructorHelpers::FClassFinder<AHUD> UInterfacePlayers(TEXT("/Game/ThirdPersonCPP/Blueprints/Widgets/BP_UInterfacePlayers"));
	if (UInterfacePlayers.Class != NULL)
	{
		HUDClass = UInterfacePlayers.Class;
	}

}
