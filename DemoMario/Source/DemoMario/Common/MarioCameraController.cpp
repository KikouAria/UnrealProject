// Fill out your copyright notice in the Description page of Project Settings.


#include "MarioCameraController.h"


#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"

// Sets default values
AMarioCameraController::AMarioCameraController()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
    USpringArmComponent* SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
    SpringArm->SetupAttachment(RootComponent);
    SpringArm->SetRelativeRotation(FRotator(0, -90, 0));
    UCameraComponent* CameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComp"));
    CameraComp->SetupAttachment(SpringArm);
    SpringArm->bDoCollisionTest = false;
    CameraComp->SetProjectionMode(ECameraProjectionMode::Orthographic);
	
    
}

// Called when the game starts or when spawned
void AMarioCameraController::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMarioCameraController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

