// Fill out your copyright notice in the Description page of Project Settings.


#include "Item/Consumes/ConsumeItem.h"
#include "Components/SphereComponent.h"
#include "Player/MyPlayer.h"

AConsumeItem::AConsumeItem()
{
	_trigger->SetCollisionProfileName(TEXT("OverlapAllDynamic"));
}

void AConsumeItem::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	_player = Cast<AMyPlayer>(OtherActor);
	if (_player == nullptr)
		return;
	UE_LOG(LogTemp, Warning, TEXT("Player Collision!"));
	_player->GetItem(this);
	Disable();
}
