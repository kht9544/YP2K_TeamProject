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

#include "Components/Widget.h"

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

    //_boxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComponent"));
    //RootComponent = _boxComponent;
    //_boxComponent->SetCollisionProfileName(TEXT("Trigger"));

}

// Called when the game starts or when spawned
void AStageSequence_Trigger::BeginPlay()
{
	Super::BeginPlay();
	

    //FindBossWidget();

    //if (_boxComponent)
    //{
    //    _boxComponent->OnComponentBeginOverlap.AddDynamic(this, &AStageSequence_Trigger::OnOverlapBegin);
    //}
    // 
}
void AStageSequence_Trigger::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

}
//
//// Called every frame
//void AStageSequence_Trigger::Tick(float DeltaTime)
//{
//	Super::Tick(DeltaTime);
//
//}
//
//
//void AStageSequence_Trigger::OnSequenceFinished()
//{
//
//    UE_LOG(LogTemp, Log, TEXT("Sequence Finished"));
// // UI 위젯 복원
//    ShowUIWidgets();
//
//    // TriggerBox 삭제
//    DestroyTriggerBox();
//}
//
//
//
//void AStageSequence_Trigger::HideUIWidgets()
//{
//   /* if (Boss1WidgetInstance && Boss1WidgetInstance->CanvasPanel_15)
//    {
//        _bossHpBarUI->CanvasPanel_15->SetVisibility(ESlateVisibility::Hidden);
//        UE_LOG(LogTemp, Log, TEXT("CanvasPanel_15 is now hidden."));
//    }
//    else
//    {
//        UE_LOG(LogTemp, Warning, TEXT("CanvasPanel_15 is null or Boss1Widget not initialized."));
//    }*/
//}
//
//void AStageSequence_Trigger::ShowUIWidgets()
//{
//    for (UUserWidget* Widget : UIWidgets)
//    {
//        if (Widget)
//        {
//            Widget->AddToViewport(0); // 위젯 다시 추가
//            UE_LOG(LogTemp, Warning, TEXT("Widget %s restored"), *Widget->GetName());
//        }
//    }
//}
//
//void AStageSequence_Trigger::DestroyTriggerBox()
//{
//
//    if (_boxComponent)
//    {
//        _boxComponent->DestroyComponent();
//        UE_LOG(LogTemp, Log, TEXT("Trigger Box destroyed"));
//    }
//}
//
//void AStageSequence_Trigger::FindBossWidget()
//{
//
//}
//
//
//
//
//
//void AStageSequence_Trigger::OnOverlapBegin(
//    UPrimitiveComponent* OverlappedComponent,
//    AActor* OtherActor,
//    UPrimitiveComponent* OtherComp,
//    int32 OtherBodyIndex,
//    bool bFromSweep,
//    const FHitResult& SweepResult
//)
//{
// 
//    //if (!_sequencePlayer)
//    //{
//    //    UE_LOG(LogTemp, Error, TEXT("Sequence Player is not valid!"));
//    //    return;
//    //}
//
//    //// UI 숨김
//    //HideUIWidgets();
//
//    //// 시퀀스 재생
//    //_sequencePlayer->Play();
//
//    //// TriggerBox 소멸
//    //Destroy();
//
//    if (!OtherActor || OtherActor == this || SequencePath.IsEmpty())
//        return;
//
//    UE_LOG(LogTemp, Log, TEXT("Trigger Box activated by %s"), *OtherActor->GetName());
//
//    // UI 위젯 숨김
//    HideUIWidgets();
//
//    // Level Sequence 로드 및 플레이
//    ULevelSequence* LevelSequence = LoadObject<ULevelSequence>(nullptr, *SequencePath);
//    if (!LevelSequence)
//    {
//        UE_LOG(LogTemp, Error, TEXT("Failed to load Level Sequence: %s"), *SequencePath);
//        return;
//    }
//
//    FMovieSceneSequencePlaybackSettings PlaybackSettings;
//    ALevelSequenceActor* SequenceActor = nullptr;
//
//    _sequencePlayer = ULevelSequencePlayer::CreateLevelSequencePlayer(GetWorld(), LevelSequence, PlaybackSettings, SequenceActor);
//
//
//    if (_sequencePlayer)
//    {
//        _sequencePlayer->OnFinished.AddDynamic(this, &AStageSequence_Trigger::OnSequenceFinished);
//        _sequencePlayer->Play();
//    }
//    else
//    {
//        UE_LOG(LogTemp, Error, TEXT("Failed to create Level Sequence Player!"));
//    }
//}
//
