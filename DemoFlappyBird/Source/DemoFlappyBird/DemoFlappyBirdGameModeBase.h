// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Actors/LandActor.h"
#include "Actors/PipeActor.h"
#include "Background/BackgroundActor.h"
#include "Character/BirdPawn.h"
#include "GameFramework/GameModeBase.h"
#include "DemoFlappyBirdGameModeBase.generated.h"


UENUM(BlueprintType)
enum class EGameState : uint8
{
	Game_Menu = 0,
	Game_Running,
	Game_Over
};

UCLASS()
class DEMOFLAPPYBIRD_API ADemoFlappyBirdGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
public:
	ADemoFlappyBirdGameModeBase();
	virtual void BeginPlay() override;
	void ChangeGameState(EGameState State);
private:
	ABackgroundActor* Background;
	ALandActor* LandActor;
	APipeActor* PipeActor;
	ABirdPawn* BirdPawn;
};

