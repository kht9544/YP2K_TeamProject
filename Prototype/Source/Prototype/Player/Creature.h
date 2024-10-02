// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Creature.generated.h"

UCLASS()
class PROTOTYPE_API ACreature : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ACreature();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void PostInitializeComponents() override;
	virtual void Init();
	virtual void Disable();
		
	virtual float TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser);

	float GetVertical() {return _vertical;}
	float GetHorizontal() {return _horizontal;}

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	bool _isAttcking = false;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	int32 _curAttackIndex = 0;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	float _vertical = 0.0f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	float _horizontal = 0.0f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = AttackHit, meta = (AllowPrivateAccess = "true"))
	FVector _hitPoint;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Stat, meta = (AllowPrivateAccess = "true"))
	class UWidgetComponent* _hpWidget;


public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = UI, meta = (AllowPrivateAccess = "true"))
	class UWidgetComponent* _Widget;


};
