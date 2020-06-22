// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "../Plugins/2D/Paper2D/Source/Paper2D/Classes/PaperFlipbookComponent.h"
#include "BirdPawn.generated.h"  

UENUM(BlueprintType)
enum class EStatus: uint8
{
	Idol = 0,
	Fly,
	Dead
	
};

UCLASS()
class DEMOFLAPPYBIRD_API ABirdPawn : public APawn
{
	GENERATED_BODY()

private:
	// Sets default values for this pawn's properties
	void Jump();
	USoundBase* JumpSE;
	void UpdateFaceDirection();
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	UFUNCTION()
	void OnComponentHitEvent(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& HitResult);

	UPROPERTY()
	EStatus CurrentStatus = EStatus::Idol;
public:
	ABirdPawn();
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(EditAnywhere)
    UPaperFlipbookComponent* FlipbookComp;  



	void ChangeStatus(EStatus Status);

	USoundBase* DeadSE;
};
