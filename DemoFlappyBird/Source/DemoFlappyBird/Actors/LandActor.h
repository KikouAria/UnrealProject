// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LandActor.generated.h"

UCLASS()
class DEMOFLAPPYBIRD_API ALandActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ALandActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	void ResetPos();
	UFUNCTION()
	void UpdateLocation(float DeltaTime);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	UPROPERTY()
	class UPaperSpriteComponent* LandSpriteComp;
	
	UPROPERTY()
	class UPaperSpriteComponent* LandSpriteNextComp;
	
	float MoveSpeed = 100;
	bool bEnableMovement = false;
};
