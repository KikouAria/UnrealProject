// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PaperCharacter.h"
#include "MarioPaperCharacter.generated.h"

/**
 * 
 */
UCLASS()
class DEMOMARIO_API AMarioPaperCharacter : public APaperCharacter
{
	GENERATED_BODY()

	// void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;
		void BeginPlay() override;
	void BindInput();
	

	void DoJump();
	void Move(float Axis);
};
