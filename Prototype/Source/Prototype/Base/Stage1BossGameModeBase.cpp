// Fill out your copyright notice in the Description page of Project Settings.


#include "Base/Stage1BossGameModeBase.h"
#include "../Component/StatComponent.h"
#include "../Component/InventoryComponent.h"
#include "MyGameInstance.h"
#include "../Player/MyPlayer.h"
#include "Kismet/GameplayStatics.h"


AStage1BossGameModeBase::AStage1BossGameModeBase()
{
    
}

void AStage1BossGameModeBase::BeginPlay()
{
     AMyPlayer* player = Cast<AMyPlayer>(UGameplayStatics::GetPlayerCharacter(this, 0));
	 player->LoadPlayerState();
	if (player)
	{
		UMyGameInstance* GameInstance = Cast<UMyGameInstance>(GetGameInstance());
		if(GameInstance)
		{
			GameInstance->InitializeManagers();
			UStatComponent* StatComponent = player->FindComponentByClass<UStatComponent>();
			if (StatComponent)
			{
				GameInstance->LoadPlayerStats(StatComponent);	
			}
			
			UInventoryComponent* InvenComponent = player->FindComponentByClass<UInventoryComponent>();
			if (InvenComponent)
			{
			 	GameInstance->LoadInventory(InvenComponent);	
			}
		
		}
		
	}
}

void AStage1BossGameModeBase::PostInitializeComponents()
{
     Super::PostInitializeComponents();
}
