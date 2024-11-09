// Fill out your copyright notice in the Description page of Project Settings.


#include "Base/Stage1BossGameModeBase.h"
#include "../Component/StatComponent.h"
#include "MyGameInstance.h"
#include "../Player/MyPlayer.h"
#include "Kismet/GameplayStatics.h"


AStage1BossGameModeBase::AStage1BossGameModeBase()
{
    
}

void AStage1BossGameModeBase::BeginPlay()
{
     AMyPlayer* player = Cast<AMyPlayer>(UGameplayStatics::GetPlayerCharacter(this, 0));
	if (player)
	{
		UMyGameInstance* GameInstance = Cast<UMyGameInstance>(GetGameInstance());
		if(GameInstance)
		{
			UStatComponent* StatComponent = player->FindComponentByClass<UStatComponent>();
			if (StatComponent)
			{
				GameInstance->LoadPlayerStats(StatComponent);	

				_UIManager = GameInstance->GetUIManager();
                _soundManager = GameInstance->GetSoundManager();
                _effectManager = GameInstance->GetEffectManager();
			}
		}
		
	}
}

void AStage1BossGameModeBase::PostInitializeComponents()
{
     Super::PostInitializeComponents();
}
