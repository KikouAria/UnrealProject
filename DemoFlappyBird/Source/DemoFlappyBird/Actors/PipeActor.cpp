// Fill out your copyright notice in the Description page of Project Settings.


#include "PipeActor.h"
#include "../Plugins/2D/Paper2D/Source/Paper2D/Classes/PaperSprite.h"
#include "../Plugins/2D/Paper2D/Source/Paper2D/Classes/PaperSpriteComponent.h"
#include "DemoFlappyBird/DemoFlappyBirdGameModeBase.h"
#include "DemoFlappyBird/GameState/ScoreGameStateBase.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
APipeActor::APipeActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
    RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComp"));
    static ConstructorHelpers::FObjectFinder<UPaperSprite> PipeUpSource(TEXT("PaperSprite'/Game/DemoFlappyBird/Resource/Sprites/Pipes/pipe_up_Sprite.pipe_up_Sprite'"));
    static ConstructorHelpers::FObjectFinder<UPaperSprite> PipeDownSource(TEXT("PaperSprite'/Game/DemoFlappyBird/Resource/Sprites/Pipes/pipe_down_Sprite.pipe_down_Sprite'"));
    

	
	// 创建3个PipeGroup, 同时出现在一个画面中
    for (int i = 0; i < 3; ++i)
    {
    	// 创建一个Pipe Group 里面存有上下各一个Pipe
	    USceneComponent* PipeGroup = CreateDefaultSubobject<USceneComponent>(*FString::Printf(TEXT("PipeGroup%d"), i));
	    PipeGroup->SetupAttachment(RootComponent);
	    PipeGroups.Add(PipeGroup);

        UPaperSpriteComponent* PipeUpSpriteComp = CreateDefaultSubobject<UPaperSpriteComponent>(*FString::Printf(TEXT("PipeUp%d"), i));
        PipeUpSpriteComp->SetupAttachment(PipeGroup);
        PipeUpSpriteComp->SetSprite(PipeUpSource.Object);
        PipeUpSpriteComp->SetRelativeLocation(FVector(0, 0, -220));
    	
        UPaperSpriteComponent* PipeDownSpriteComp = CreateDefaultSubobject<UPaperSpriteComponent>(*FString::Printf(TEXT("PipeDown%d"), i));
        PipeDownSpriteComp->SetupAttachment(PipeGroup);
        PipeDownSpriteComp->SetSprite(PipeDownSource.Object);
        PipeDownSpriteComp->SetRelativeLocation(FVector(0, 0, 220));
    }

    // 读取音频文件
    static ConstructorHelpers::FObjectFinder<USoundBase> CoinSEScr(TEXT("SoundWave'/Game/DemoFlappyBird/Resource/Sounds/SE/coin.coin'"));
    if (CoinSEScr.Object)
        CoinSE = CoinSEScr.Object;
	static ConstructorHelpers::FObjectFinder<USoundBase> DeadSEScr(TEXT("SoundWave'/Game/DemoFlappyBird/Resource/Sounds/SE/dead.dead'"));
    if (DeadSEScr.Object)
        DeadSE = DeadSEScr.Object;
    
	
}

void APipeActor::ResetPipePos()
{
	for (int i = 0; i < 3; ++i)
	{
		auto EachPipeGroup = PipeGroups[i];
        EachPipeGroup->SetRelativeLocation(FVector( 300 + PipeInterval * i, 0, FMath::RandRange(-50, 50)));
		
	}
}




// Called when the game starts or when spawned
void APipeActor::BeginPlay()
{
	Super::BeginPlay();
    ResetPipePos();
}

void APipeActor::UpdateMovement(float DeltaTime)
{
    if (!bEnableMovement)
        return;
    float MoveDistance = -MoveSpeed * DeltaTime;
    for (int32 i = 0; i < 3; ++i) 
    {
	    auto EachPipeGroup = PipeGroups[i];
	    EachPipeGroup->AddLocalOffset(FVector(MoveDistance, 0, 0));
        // 加分
        if (!bAddedScore && EachPipeGroup->GetRelativeLocation().X < -100)
        {
            bAddedScore = true;
	        UGameplayStatics::PlaySound2D(GetWorld() ,CoinSE);
        	//  执行加分操作
            ADemoFlappyBirdGameModeBase* GameMode = Cast<ADemoFlappyBirdGameModeBase> (GetWorld()->GetAuthGameMode());  // 获取GameMode (强制类型转换)
            auto ScoreState = GameMode->GetGameState<AScoreGameStateBase>();  // 从GameMode中获取GameState
	        ScoreState->AddScore(1);

        }

    	
    	// 生成(移动到)下一个管子
    	if (EachPipeGroup->GetRelativeLocation().X < -180)
    	{
            bAddedScore = false;
            int32 TargetIndex = (i - 1) < 0 ? 2 : i - 1;
            EachPipeGroup->SetRelativeLocation(FVector(PipeGroups[TargetIndex]->GetRelativeLocation().X + PipeInterval,
                                                       0, FMath::RandRange(-50, 50)));
           
    	}
    }
}

// Called every frame
void APipeActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
    if (bEnableMovement)
        UpdateMovement(DeltaTime);
}

