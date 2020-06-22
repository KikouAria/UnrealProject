// Copyright Epic Games, Inc. All Rights Reserved.


#include "DemoFlappyBirdGameModeBase.h"



#include "Actors/LandActor.h"
#include "Actors/PipeActor.h"
#include "Background/BackgroundActor.h"
#include "Character/BirdPawn.h"
#include "GameState/ScoreGameStateBase.h"
#include "Kismet/GameplayStatics.h"

ADemoFlappyBirdGameModeBase::ADemoFlappyBirdGameModeBase()
{
	DefaultPawnClass = ABirdPawn::StaticClass();
	GameStateClass = AScoreGameStateBase::StaticClass();
}

void ADemoFlappyBirdGameModeBase::BeginPlay()
{
	Super::BeginPlay();
	Background = GetWorld()->SpawnActor<ABackgroundActor>(ABackgroundActor::StaticClass(), 
		FVector(0, -100, 0), FRotator(0, 0, 0));
	LandActor = GetWorld()->SpawnActor<ALandActor>(ALandActor::StaticClass(),
		FVector(0, 0, -250), FRotator::ZeroRotator);
	PipeActor = GetWorld()->SpawnActor<APipeActor>(APipeActor::StaticClass(),
	                                 FVector::ZeroVector, FRotator::ZeroRotator);
	BirdPawn = Cast<ABirdPawn>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));

}

void ADemoFlappyBirdGameModeBase::ChangeGameState(EGameState State)
{
	switch (State)
	{
	case EGameState::Game_Menu:
		BirdPawn->ChangeStatus(EStatus::Idol);
		BirdPawn->SetActorLocation(FVector(-90, 0, 0));
		PipeActor->bEnableMovement = false;
		PipeActor->SetActorLocation(FVector(0, 0, 0));
		PipeActor->ResetPipePos();
		LandActor->bEnableMovement = false;
		break;
	case EGameState::Game_Running:
		BirdPawn->ChangeStatus(EStatus::Fly);
		PipeActor->bEnableMovement = true;
		LandActor->bEnableMovement = true;
		break;
	case EGameState::Game_Over:
		BirdPawn->ChangeStatus(EStatus::Dead);
		PipeActor->bEnableMovement = false;
		LandActor->bEnableMovement = false;
		break;
	default:
		break;
	}
}
