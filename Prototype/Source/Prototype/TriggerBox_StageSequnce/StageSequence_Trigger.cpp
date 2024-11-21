// Fill out your copyright notice in the Description page of Project Settings.


#include "TriggerBox_StageSequnce/StageSequence_Trigger.h"

#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"

#include "../Player/MyPlayer.h"
#include "../Player/Dragon.h"
#include "LevelSequence.h"
#include "LevelSequencePlayer.h"
#include "LevelSequenceActor.h"
#include "MovieSceneSequencePlayer.h"

#include "UI/PlayerBarWidget.h"
#include "UI/SkillWidget_test.h"
#include "UI/MiniMapWidget.h"
#include "UI/Boss1Widget.h"
#include "UI/StatWidget.h"
#include "Component/StatComponent.h"
#include "Blueprint/UserWidget.h"


// Sets default values
AStageSequence_Trigger::AStageSequence_Trigger()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;


  /*  _boxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComponent"));
    RootComponent = _boxComponent;

    _boxComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
    _boxComponent->SetCollisionObjectType(ECC_WorldStatic);
    _boxComponent->SetCollisionResponseToAllChannels(ECR_Ignore);
    _boxComponent->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);*/

   /* _boxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComponent"));
    RootComponent = _boxComponent;
    _boxComponent->SetCollisionProfileName(TEXT("Trigger"));*/

}

// Called when the game starts or when spawned
void AStageSequence_Trigger::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void AStageSequence_Trigger::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

