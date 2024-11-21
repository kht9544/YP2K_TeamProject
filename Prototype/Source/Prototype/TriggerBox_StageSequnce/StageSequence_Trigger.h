// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "Components/WidgetComponent.h"
#include "LevelSequence.h"
#include "LevelSequencePlayer.h"
#include "LevelSequenceActor.h"
#include "MovieSceneSequencePlayer.h"
#include "Blueprint/UserWidget.h"
#include "StageSequence_Trigger.generated.h"




UCLASS()
class PROTOTYPE_API AStageSequence_Trigger : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AStageSequence_Trigger();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;



public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;




private:
//
//	UPROPERTY(EditAnywhere, Category = "TriggerBox")
//	UBoxComponent* _boxComponent;
//
//	UPROPERTY(EditAnywhere, Category = "UI")
//	TArray<UUserWidget*> UIWidgets;
//
//	UPROPERTY(EditAnywhere, Category = "Sequence")
//	FString SequencePath;
//
//	UPROPERTY()
//	ULevelSequencePlayer* _sequencePlayer;
//	
//
//	UFUNCTION()
//	void OnOverlapBegin(
//		UPrimitiveComponent* OverlappedComponent,
//		AActor* OtherActor,
//		UPrimitiveComponent* OtherComp,
//		int32 OtherBodyIndex,
//		bool bFromSweep,
//		const FHitResult& SweepResult
//	);
//
//	UFUNCTION()
//	void OnSequenceFinished();
//
//	void HideUIWidgets();
//	void ShowUIWidgets();
//	void DestroyTriggerBox();
//
//	void FindBossWidget();
//
//	
//private:
//	UPROPERTY(EditAnywhere, Category = "UI")
//	TSubclassOf<class UBoss1Widget> _bossHpBarUI;
//
//	UPROPERTY()
//	class UBoss1Widget* Boss1WidgetInstance;


};
