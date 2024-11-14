// Fill out your copyright notice in the Description page of Project Settings.

#include "MeteorDecal.h"
#include "Components/StaticMeshComponent.h"
#include "Components/DecalComponent.h"
#include "Monster/Monster.h"
#include "NiagaraComponent.h"
#include "Engine/DamageEvents.h"
#include "NiagaraFunctionLibrary.h"
#include "Kismet/GameplayStatics.h"

AMeteorDecal::AMeteorDecal()
{
    PrimaryActorTick.bCanEverTick = true;
    _fallDuration = 3.0f;  // Default fall duration
    _elapsedTime = 0.0f;

    // Initialize Static Mesh for Meteor
    _niagaraCom = CreateDefaultSubobject<UNiagaraComponent>(TEXT("NiagaraComponent"));
    _niagaraCom->SetupAttachment(RootComponent);

    static ConstructorHelpers::FObjectFinder<UNiagaraSystem> NiagaraEffect(TEXT("/Script/Niagara.NiagaraSystem'/Game/RPGEffects/ParticlesNiagara/Warrior/HeavyImpact/NS_Warrior_HeavyImpact_02.NS_Warrior_HeavyImpact_02'"));
    if (NiagaraEffect.Succeeded())
    {
        _additionalEffect = NiagaraEffect.Object;
    }
}

void AMeteorDecal::BeginPlay()
{
    Super::BeginPlay();
    _elapsedTime = 0.0f;

    SetActorScale3D(FVector(1.0f, 20.0f, 20.0f));

    // Niagara 크기 설정
    if (_niagaraCom)
    {
        _niagaraCom->SetWorldScale3D(FVector(1.0f, 1.0f, 1.0f));
    }
}

void AMeteorDecal::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    if (_elapsedTime < _fallDuration)
    {
        _elapsedTime += DeltaTime;
        UpdateMeteorPosition(DeltaTime);  // 메테오 위치 업데이트

        // Update Decal size as the meteor falls (데칼 크기 업데이트)
        float progress = _elapsedTime / _fallDuration;
        FVector curScale = GetActorScale();
        curScale.Y = progress * _areaRadius;
        curScale.Z = progress * _areaRadius;
        SetActorScale3D(curScale);

        if (_elapsedTime >= _fallDuration)
        {
            OnMeteorImpact();  // 메테오가 바닥에 닿으면 충돌 처리
        }
    }
}

void AMeteorDecal::StartMeteor(FVector startLocation, FVector endLocation, float fallDuration)
{
    _startLocation = startLocation;
    _endLocation = endLocation;
    _fallDuration = fallDuration;
    _elapsedTime = 0.0f;

    // 메테오를 하늘에 위치시킴
    _niagaraCom->SetWorldLocation(startLocation);

    SetActorLocation(endLocation);  // 데칼은 바닥에 위치
    _bIsPlay = true;
}

void AMeteorDecal::OnMeteorImpact()
{
    _fieldAttackDelegate.Broadcast(GetActorLocation());

    // 메테오 메시 숨김
    _niagaraCom->SetVisibility(false);

    if (_additionalEffect)
    {
        // 즉시 _additionalEffect 발동
        UNiagaraFunctionLibrary::SpawnSystemAtLocation(
            GetWorld(),
            _additionalEffect,
            GetActorLocation(),  // 메테오 떨어진 위치
            FRotator::ZeroRotator,
            FVector(10.0f) // 후적용되는 나이아가라 사이즈 크기 
        );
    }

    TArray<AActor*> IgnoredActors;
    float DamageAmount = 500.0f;
    FVector DecalSize = GetDecal()->DecalSize;
    float Size = DecalSize.Y;
    float DamageRadius = _areaRadius * Size;
    UE_LOG(LogTemp, Warning, TEXT("Meteor Radius :%f"),_areaRadius);

    UGameplayStatics::ApplyRadialDamage(
        GetWorld(),
        DamageAmount,
        GetActorLocation(),
        DamageRadius,
        UDamageType::StaticClass(),
        IgnoredActors,
        this,
        GetInstigatorController(),
        true
    );

    // 데칼 폭발 처리
    DeActiveEvent(GetActorLocation());
}

void AMeteorDecal::UpdateMeteorPosition(float DeltaTime)
{
    FVector currentLocation = FMath::Lerp(_startLocation, _endLocation, _elapsedTime / _fallDuration);
    _niagaraCom->SetWorldLocation(currentLocation);
}

void AMeteorDecal::DeActiveEvent(FVector location)
{


}