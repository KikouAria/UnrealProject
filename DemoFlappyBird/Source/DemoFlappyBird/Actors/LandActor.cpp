// Fill out your copyright notice in the Description page of Project Settings.

#include "LandActor.h"
#include "../Plugins/2D/Paper2D/Source/Paper2D/Classes/PaperSprite.h"
#include "../Plugins/2D/Paper2D/Source/Paper2D/Classes/PaperSpriteComponent.h"


// Sets default values
ALandActor::ALandActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	// create 2 Comp
    RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComp"));
    LandSpriteComp = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("LandSpriteComp"));
    LandSpriteComp->SetupAttachment(RootComponent);
	LandSpriteNextComp = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("LandSpriteNextComp"));
    LandSpriteNextComp->SetupAttachment(RootComponent);
    LandSpriteComp->SetCollisionEnabled(ECollisionEnabled::PhysicsOnly);
    LandSpriteNextComp->SetCollisionEnabled(ECollisionEnabled::PhysicsOnly);
	
	
    static ConstructorHelpers::FObjectFinder<UPaperSprite> LandSprite(TEXT("PaperSprite'/Game/DemoFlappyBird/Resource/Sprites/Land/land_Sprite.land_Sprite'"));
    if (LandSprite.Object)
    {
	    LandSpriteComp->SetSprite(LandSprite.Object);
	    LandSpriteNextComp->SetSprite(LandSprite.Object);
    	
    };
	
}

// Called when the game starts or when spawned
void ALandActor::BeginPlay()
{
	Super::BeginPlay();
	ResetPos();
}

void ALandActor::ResetPos()
{
	LandSpriteComp->SetRelativeLocation(FVector::ZeroVector);
	
	LandSpriteNextComp->SetRelativeLocation(FVector(336, 0, 0));
}

void ALandActor::UpdateLocation(float DeltaTime)
{
	if (!bEnableMovement)
		return;
	const float Offset = -1 * MoveSpeed * DeltaTime;
	if (LandSpriteComp->GetRelativeTransform().GetLocation().X < -336)  // 如果完全移出了屏幕 
	{
		ResetPos();  // 重置
	}else{  // 否则向左移动一下
		LandSpriteComp->AddLocalOffset(FVector(Offset, 0, 0));  // move the Sprite Comp of Land to left every frame
		LandSpriteNextComp->AddLocalOffset(FVector(Offset, 0, 0));  // move the Sprite Comp of Land to left every frame
		
	}
	
}

// Called every frame
void ALandActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	UpdateLocation(DeltaTime);
	
}

