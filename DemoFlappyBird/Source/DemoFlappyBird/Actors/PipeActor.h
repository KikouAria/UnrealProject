// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PipeActor.generated.h"

UCLASS()
class DEMOFLAPPYBIRD_API APipeActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APipeActor();
	virtual void Tick(float DeltaTime) override;
	void ResetPipePos();
	void ToggleMovement();
	bool bEnableMovement = false;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	void UpdateMovement(float DeltaTime);
	
	UPROPERTY()
	TArray<USceneComponent*>  PipeGroups;

	float PipeInterval = 220;
	float MoveSpeed = 100;
	USoundBase* CoinSE;
	USoundBase* DeadSE;
	bool bAddedScore;
	
};
