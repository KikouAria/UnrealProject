// Fill out your copyright notice in the Description page of Project Settings.


#include "BackgroundActor.h"

// Sets default values
ABackgroundActor::ABackgroundActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	SpriteComp = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("RootSpriteComp"));
    SetRootComponent(SpriteComp);

}

// Called when the game starts or when spawned
void ABackgroundActor::BeginPlay()
{
	Super::BeginPlay();
	UpdateBackground();
}

void ABackgroundActor::UpdateBackground() const
{
	if(SpriteComp)
	{
		UPaperSprite* BackgroundSprite = LoadObject<UPaperSprite>(nullptr, TEXT("PaperSprite'/Game/DemoFlappyBird/Resource/Sprites/Background/bg_day_Sprite.bg_day_Sprite'"));
		if (BackgroundSprite) 
			SpriteComp->SetSprite(BackgroundSprite);
	}

}

// Called every frame
void ABackgroundActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

