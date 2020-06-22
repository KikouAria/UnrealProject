// Fill out your copyright notice in the Description page of Project Settings.


#include "BirdPawn.h"
#include "../Plugins/2D/Paper2D/Source/Paper2D/Classes/PaperFlipbook.h"
#include "Camera/CameraComponent.h"
#include "DemoFlappyBird/DemoFlappyBirdGameModeBase.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/GameplayStatics.h"


// Sets default values
ABirdPawn::ABirdPawn()
{
	PrimaryActorTick.bCanEverTick = true;

	//  create Flipbook comp
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComp"));
	FlipbookComp = CreateDefaultSubobject<UPaperFlipbookComponent>(TEXT("FlipbookComp"));
    FlipbookComp->SetupAttachment(RootComponent);
	
	// set resource of Flipbook comp
    static ConstructorHelpers::FObjectFinder<UPaperFlipbook> FlipbookRes(TEXT("PaperFlipbook'/Game/DemoFlappyBird/Resource/Flipbooks/FLB_BirdBlue.FLB_BirdBlue'"));
	FlipbookComp->SetFlipbook(FlipbookRes.Object);
	
	// create a spring arm for camera
    USpringArmComponent* ArmComp = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring"));
    ArmComp->SetupAttachment(RootComponent);
	// rotate the spring in order to change the direction of camera
    ArmComp->SetRelativeRotation(FRotator(0, -90, 0));
	// create a camera on spring arm
    UCameraComponent* CameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComp"));
    CameraComp->SetupAttachment(ArmComp);
	// remove the collision test so that won't collide with background paper
	ArmComp->bDoCollisionTest = false;
	// 2D project so change the project mode into Orthographic
	CameraComp->SetProjectionMode(ECameraProjectionMode::Orthographic);
	CameraComp->OrthoWidth = 1080;

	// 锁定X Y轴的运动
	 FBodyInstance* Body = FlipbookComp->GetBodyInstance();
	if (Body)
	{
		Body->bLockXRotation = true;
		// Body->bLockYRotation = true;

		Body->bLockXTranslation = true;
		Body->bLockYTranslation = true;

		Body->CreateDOFLock();
	}

	static ConstructorHelpers::FObjectFinder<USoundBase> DeadSEScr(TEXT("SoundWave'/Game/DemoFlappyBird/Resource/Sounds/SE/dead.dead'"));
	if (DeadSEScr.Object)
		DeadSE = DeadSEScr.Object;
}

void ABirdPawn::Jump()
{
	if (CurrentStatus == EStatus::Dead) {
		ADemoFlappyBirdGameModeBase* GameMode = Cast<ADemoFlappyBirdGameModeBase>(GetWorld()->GetAuthGameMode());
		GameMode->ChangeGameState(EGameState::Game_Menu);
	}else if (CurrentStatus == EStatus::Idol)
	{
		ADemoFlappyBirdGameModeBase* GameMode = Cast<ADemoFlappyBirdGameModeBase>(GetWorld()->GetAuthGameMode());
		GameMode->ChangeGameState(EGameState::Game_Running);
		
	}
	FlipbookComp->SetPhysicsLinearVelocity(FVector::ZeroVector);
	FlipbookComp->AddImpulse(FVector(0, 0, 2000));
	UGameplayStatics::PlaySound2D(GetWorld(), JumpSE);
	
	UE_LOG(LogTemp, Log, TEXT("Jumped"));
	
}

void ABirdPawn::UpdateFaceDirection()
{
	if (CurrentStatus == EStatus::Fly) {
		FVector BirdVelocity = FlipbookComp->GetPhysicsLinearVelocity();
		FlipbookComp->SetRelativeRotation(FRotator(FMath::Clamp<float>(BirdVelocity.Z * 0.1, -90, 90), 0, 0));
	}
}

// Called when the game starts or when spawned
void ABirdPawn::BeginPlay()
{
	Super::BeginPlay();

	// Bind Collision Event
	FlipbookComp->OnComponentHit.AddDynamic(this, &ABirdPawn::OnComponentHitEvent);  // 绑定碰撞事件
	FlipbookComp->GetBodyInstance()->bNotifyRigidBodyCollision = true;  // 开启物理通知
	FlipbookComp->SetCollisionObjectType(ECC_Pawn);  // 设置碰撞类型为Pawn(和任何物体碰撞)
	// Load Sound
	JumpSE = LoadObject<USoundBase>(nullptr,TEXT("SoundWave'/Game/DemoFlappyBird/Resource/Sounds/SE/fly.fly'"));
	
}

void ABirdPawn::OnComponentHitEvent(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	FVector NormalImpulse, const FHitResult& HitResult)
{
	if (CurrentStatus == EStatus::Dead)
		return;
	ChangeStatus(EStatus::Dead);
	ADemoFlappyBirdGameModeBase* GameMode = Cast<ADemoFlappyBirdGameModeBase>(GetWorld()->GetAuthGameMode());
	GameMode->ChangeGameState(EGameState::Game_Over);
	UGameplayStatics::PlaySound2D(GetWorld(), DeadSE);
	
	UE_LOG(LogTemp, Log, TEXT("%s"), *OtherActor->GetName());
	
}


// Called every frame
void ABirdPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	UpdateFaceDirection();
}

// Called to bind functionality to input
void ABirdPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAction(TEXT("DoJump"), IE_Pressed, this, &ABirdPawn::Jump);

}

void ABirdPawn::ChangeStatus(EStatus Status)
{
	CurrentStatus = Status;
	switch (Status)
	{
	case EStatus::Idol:
		FlipbookComp->SetSimulatePhysics(false);
		FlipbookComp->SetRelativeLocation(FVector::ZeroVector);
		FlipbookComp->SetRelativeRotation(FRotator(0, 0, 0));
		
		break;
	case EStatus::Fly:
		FlipbookComp->SetSimulatePhysics(true);
		break;
	case EStatus::Dead:
		break;
	default:
		break;
	}
}

