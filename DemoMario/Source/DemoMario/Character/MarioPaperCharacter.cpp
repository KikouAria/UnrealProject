// Fill out your copyright notice in the Description page of Project Settings.


#include "MarioPaperCharacter.h"

// void AMarioPaperCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
// {
// 	PlayerInputComponent->BindAction(TEXT("DoJump"), EInputEvent::IE_Pressed, this, &AMarioPaperCharacter::DoJump);
// 	InputComponent->BindAxis(TEXT("Wow"),this, &AMarioPaperCharacter::Move);
// 	
// 	
// }

void AMarioPaperCharacter::BeginPlay()
{
	BindInput();
}

void AMarioPaperCharacter::BindInput()
{
	EnableInput(GetWorld()->GetFirstPlayerController());
	
	InputComponent->BindAction(TEXT("DoJump"), EInputEvent::IE_Pressed, this, &AMarioPaperCharacter::DoJump);
	InputComponent->BindAxis(TEXT("MoveRight"), this, &AMarioPaperCharacter::Move);
}

void AMarioPaperCharacter::DoJump()
{
}

void AMarioPaperCharacter::Move(float Axis)
{
	AddMovementInput(FVector(Axis, 0, 0));
	UE_LOG(LogTemp, Log, TEXT("In Move, Axis: %f"), Axis);
	
	
}
