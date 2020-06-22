// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "ScoreGameStateBase.generated.h"

/**
 * 
 */
UCLASS()
class DEMOFLAPPYBIRD_API AScoreGameStateBase : public AGameStateBase
{
	GENERATED_BODY()

public:
	void AddScore(int32 newScore);
	int32 GetScore();
	void ResetScore();
	
private:
	int32 Score;
};
