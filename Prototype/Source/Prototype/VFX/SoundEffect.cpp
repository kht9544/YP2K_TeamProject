// Fill out your copyright notice in the Description page of Project Settings.


#include "VFX/SoundEffect.h"
#include "Components/AudioComponent.h"
#include "Sound/SoundBase.h"

// Sets default values
ASoundEffect::ASoundEffect()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	_audioComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("AudioComponent"));
	RootComponent = _audioComponent;
	_audioComponent->bAutoActivate = false;


}

// Called when the game starts or when spawned
void ASoundEffect::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASoundEffect::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ASoundEffect::Play(FVector location)
{
	UE_LOG(LogTemp, Warning, TEXT("Playing sound at location: %s"), *location.ToString());
	if (_audioComponent && _soundCom)
	{
		SetActorLocation(location);
		_audioComponent->SetSound(_soundCom);
		/*_audioComponent->Play();*/
		if (!IsPlaying()) // 이미 재생 중이지 않을 때만 재생
		{
			_audioComponent->Play();
		}
	}
}

bool ASoundEffect::IsPlaying() const
{
	return _audioComponent->IsPlaying();
}

void ASoundEffect::Stop()
{
	if (IsPlaying())
	{
		_audioComponent->Stop();
	}
}




