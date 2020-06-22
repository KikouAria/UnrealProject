// Copyright Epic Games, Inc. All Rights Reserved.


#include "DemoMarioGameModeBase.h"

#include "Character/MarioPaperCharacter.h"

ADemoMarioGameModeBase::ADemoMarioGameModeBase()
{
	static ConstructorHelpers::FClassFinder<AMarioPaperCharacter> MarioClass(TEXT("Blueprint'/Game/DemoMario/Bluprint/Character/BP_MarioPaperCharacter.BP_MarioPaperCharacter_C'"));
	DefaultPawnClass = MarioClass.Class;
	
}
