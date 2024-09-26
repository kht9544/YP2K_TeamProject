// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "MyPlayer.generated.h"

struct FInputActionValue;

UENUM(BlueprintType)
enum class EPlayerState : uint8
{
    Normal UMETA(DisplayName = "Normal"),
    Climbing UMETA(DisplayName = "Climbing")
};


UCLASS()
class PROTOTYPE_API AMyPlayer : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMyPlayer();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	virtual void PostInitializeComponents() override;
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	bool CanSetArmor();

	void SetArmor(class AArmor_test* Armor);

	void SetSkillOnCooldown(int32 index,bool cool){SkillOnCooldown[index] = cool;}

private:
	void Move(const FInputActionValue& value);
	void Look(const FInputActionValue& value);
	void JumpA(const FInputActionValue& value);
	void AttackA(const FInputActionValue& value);
	void Skill1(const FInputActionValue& value);
	void Skill2(const FInputActionValue& value);
	void Skill3(const FInputActionValue& value);
	void Skill4(const FInputActionValue& value);
	 void Mouse(const FInputActionValue& value);
	//cheol
	void StatUIOpen(const FInputActionValue& value);

	//void CheckForClimbableWall();
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Skill, meta = (AllowPrivateAccess = "true"))
    TArray<bool> SkillOnCooldown;

	//TODO:item으로 변경
	TArray<class Armor_test*> Equipment; //0:하체 1:상체 2:검 3:견갑 4:방패 5:투구

	bool bIsDashing;
    FVector DashDirection;
    float DashTimeElapsed;
    float DashDuration;

    void PerformDash(float DeltaTime);


public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* _lookAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* _moveAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* _jumpAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* _attackAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* _skill1Action;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* _skill2Action;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* _skill3Action;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* _skill4Action;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* _mouseAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* _StatOpenAction;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* _springArm;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* _camera;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = UI, meta = (AllowPrivateAccess = "true"))
    class USkillWidget_test* _skillWidgetInstance;

	//  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Parkour, meta = (AllowPrivateAccess = "true"))
    //  class UParkourComponent_Test* _parkourComp;

	//cheol
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stat, meta = (AllowPrivateAccess = "true"))
	class UStatComponent* _StatCom;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = UI, meta = (AllowPrivateAccess = "true"))
	class UStatWidget* _statWidget;

	// MiniMap
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = MiniMap, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* _MiniMapspringArm;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = MiniMap, meta = (AllowPrivateAccess = "true"))
	class USceneCaptureComponent2D* _MiniMapCapture;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Minimap, meta = (AllowPrivateAccess = "true"))
	class UPaperSpriteComponent* _MinimapSprite;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category = "Dash")
	float _dashDistance;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category = "Dash")
	float _dashSpeed;



};
