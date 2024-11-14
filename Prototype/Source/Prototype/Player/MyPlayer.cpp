#include "MyPlayer.h"

#include "Base/MyGameInstance.h"
#include "Base/MyPlayerSaveGame.h"

#include "Components/CapsuleComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Component/InventoryComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Camera/CameraShakeBase.h"
#include "EnhancedInputComponent.h"
#include "../Monster/NormalMonster.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "Kismet/GameplayStatics.h"
#include "MyPlayerController.h"
#include "../UI/SkillWidget_test.h"
#include "MeteorDecal.h"
#include "Fireball.h"
#include "Kismet/KismetMathLibrary.h"

// chelo
#include "Base/Managers/UIManager.h"
#include "UI/InventoryWidget.h"
#include "UI/StatWidget.h"
#include "Components/WidgetComponent.h"

// MiniMap
#include "GameFramework/Actor.h"
#include "Components/SceneCaptureComponent2D.h"
#include "PaperSpriteComponent.h"
#include "UI/MiniMapWidget.h"

// te
#include "GameFramework/Actor.h"

// Animation
#include "../Animation/PlayerAnimInstance.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "UI/PlayerBarWidget.h"

// hp
#include "Components/ProgressBar.h"

#include "../Base/Managers/SoundManager.h"
#include "../Base/Managers/EffectManager.h"
#include "NiagaraSystem.h"
#include "NiagaraFunctionLibrary.h"
#include "NiagaraComponent.h"

#include "Components/AudioComponent.h"
#include "Components/DecalComponent.h"

// Sets default values
AMyPlayer::AMyPlayer()
{
	PrimaryActorTick.bCanEverTick = true;

	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f);

	_springArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	_camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	_inventoryComponent = CreateDefaultSubobject<UInventoryComponent>(TEXT("Inventory"));

	//_upperBodyMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("UpperSkeletal"));
	_lowerBodyMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("LowerSkeletal"));
	_shoulderBodyMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("ShoulderSkeletal"));
	_swordBodyMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SwordSkeletal"));
	_shieldBodyMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("ShieldSkeletal"));

	_springArm->SetupAttachment(RootComponent);
	_camera->SetupAttachment(_springArm);

	_springArm->TargetArmLength = 500.0f;
	_springArm->SetRelativeRotation(FRotator(-35.0f, 0.0f, 0.0f));

	// MiniMap test
	_MiniMapspringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("MiniSpringArm"));
	_MiniMapspringArm->SetupAttachment(RootComponent);
	_MiniMapspringArm->SetWorldRotation(FRotator::MakeFromEuler(FVector(0.0f, -90.0f, 0.0f)));
	_MiniMapspringArm->bUsePawnControlRotation = false;
	_MiniMapspringArm->bInheritPitch = false;
	_MiniMapspringArm->bInheritRoll = false;
	_MiniMapspringArm->bInheritYaw = false;

	_MiniMapCapture = CreateDefaultSubobject<USceneCaptureComponent2D>(TEXT("MiniCapture"));
	_MiniMapCapture->SetupAttachment(_MiniMapspringArm);

	_MiniMapCapture->ProjectionType = ECameraProjectionMode::Orthographic;
	_MiniMapCapture->OrthoWidth = 1024;

	_MinimapSprite = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("MinimapSprite"));
	_MinimapSprite->SetupAttachment(RootComponent);
	_MinimapSprite->SetWorldRotation(FRotator::MakeFromEuler(FVector(90.f, 0.f, -90.f)));
	//_MinimapSprite->SetWorldScale3D(FVector(0.5f));
	//_MinimapSprite->SetWorldLocation(FVector(0.f, 0.f, 300.f));
	_MinimapSprite->bVisibleInSceneCaptureOnly = true;

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> USM(TEXT("/Script/Engine.SkeletalMesh'/Game/ParagonGreystone/Characters/Heroes/Greystone/Source/Free_WhiteTiger_Detach/Free_Body_Face_Pos.Free_Body_Face_Pos'"));
	if (USM.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(USM.Object);
	}

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> LSM(TEXT("/Script/Engine.SkeletalMesh'/Game/ParagonGreystone/Characters/Heroes/Greystone/Source/Free_WhiteTiger_Detach/Free_Body_Bottom_Pos.Free_Body_Bottom_Pos'"));
	if (LSM.Succeeded())
	{
		_lowerBodyMesh->SetSkeletalMesh(LSM.Object);
	}

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> SHSM(TEXT("/Script/Engine.SkeletalMesh'/Game/ParagonGreystone/Characters/Heroes/Greystone/Source/Free_WhiteTiger_Detach/Free_Body_Arms_Pos.Free_Body_Arms_Pos'"));
	if (SHSM.Succeeded())
	{
		_shoulderBodyMesh->SetSkeletalMesh(SHSM.Object);
	}

	// static ConstructorHelpers::FObjectFinder<USkeletalMesh> SWSM(TEXT("/Script/Engine.SkeletalMesh'/Game/ParagonGreystone/Characters/Heroes/Greystone/Source/WhiteTiger_Detach/Sward_Pos.Sward_Pos'"));
	// if (SWSM.Succeeded())
	// {
	// 	_swordBodyMesh->SetSkeletalMesh(SWSM.Object);
	// }

	// static ConstructorHelpers::FObjectFinder<USkeletalMesh> SSM(TEXT("/Script/Engine.SkeletalMesh'/Game/ParagonGreystone/Characters/Heroes/Greystone/Source/WhiteTiger_Detach/Shield_Pos.Shield_Pos'"));
	// if (SSM.Succeeded())
	// {
	// 	_shieldBodyMesh->SetSkeletalMesh(SSM.Object);
	// }

	_lowerBodyMesh->SetupAttachment(GetMesh());
	_shoulderBodyMesh->SetupAttachment(GetMesh());
	_swordBodyMesh->SetupAttachment(GetMesh());
	_shieldBodyMesh->SetupAttachment(GetMesh());

	GetMesh()->SetRelativeLocationAndRotation(FVector(0.0f, 0.0f, -88.0f), FRotator(0.0f, -90.0f, 0.0f));

	//_parkourComp = CreateDefaultSubobject<UParkourComponent_Test>(TEXT("ParkourComponent"));

	static ConstructorHelpers::FClassFinder<UStatWidget> StatClass(
		TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/Blueprint/UI/PlayerStat_UI.PlayerStat_UI_C'"));
	if (StatClass.Succeeded())
	{
		_statWidget = CreateWidget<UStatWidget>(GetWorld(), StatClass.Class);
	}

	// MiniMap
	static ConstructorHelpers::FClassFinder<UMiniMapWidget> MinuMap(
		TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/Blueprint/UI/MiniMap_UI.MiniMap_UI_C'"));

	if (MinuMap.Succeeded())
	{
		_MiniMap = CreateWidget<UMiniMapWidget>(GetWorld(), MinuMap.Class);
	}

	static ConstructorHelpers::FClassFinder<UCameraShakeBase> CS(TEXT("/Script/Engine.Blueprint'/Game/Blueprint/Player/CamerShake_BP.CamerShake_BP_C'"));
	if (CS.Succeeded())
	{
		_cameraShakeClass = CS.Class;
	}

	static ConstructorHelpers::FClassFinder<AMeteorDecal> MD(TEXT("/Script/Engine.Blueprint'/Game/Blueprint/VFX/MeteorDecal_Test_BP.MeteorDecal_Test_BP_C'"));
	if (MD.Succeeded())
	{
		_decal = MD.Class;
	}

	static ConstructorHelpers::FClassFinder<AFireball> FB(TEXT("/Script/Engine.Blueprint'/Game/Blueprint/Player/FireBall_02_BP.FireBall_02_BP_C'"));
	if (FB.Succeeded())
	{
		_fireball = FB.Class;
	}

	static ConstructorHelpers::FClassFinder<UUserWidget> PlBar(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/Blueprint/UI/PlayerBar_UI.PlayerBar_UI_C'"));
	if (PlBar.Succeeded())
	{
		WidgetClass = PlBar.Class;
	}

	static ConstructorHelpers::FClassFinder<ADecalActor> DA(TEXT("/Script/Engine.Blueprint'/Game/Blueprint/VFX/SkillRangeDecal_BP.SkillRangeDecal_BP_C'"));
	if (DA.Succeeded())
	{
		SkillDecalActor = DA.Class;
	}

	if (WidgetClass)
	{
		_Widget = CreateWidget<UPlayerBarWidget>(GetWorld(), WidgetClass);
		if (_Widget)
		{
			_Widget->AddToViewport();
		}
	}

	_dashDistance = 1000.f;
	_dashSpeed = 3000.f;
	bIsDashing = false;
	DashDuration = _dashDistance / _dashSpeed;
	DashTimeElapsed = 0.f;
}

// Called when the game starts or when spawned
void AMyPlayer::BeginPlay()
{
	Super::BeginPlay();

	if (_statWidget)
	{
		_statWidget->AddToViewport();
		_statWidget->SetVisibility(ESlateVisibility::Hidden);
	}

	if (_MiniMap)
	{
		_MiniMap->AddToViewport();
	}

	AMyPlayerController *MyController = Cast<AMyPlayerController>(GetController());
	if (MyController != nullptr)
	{
		_skillWidgetInstance = MyController->SkillWidgetInstance;
	}
	SkillOnCooldown.Init(false, 4);

}

void AMyPlayer::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	//_StatCom->SetLevelInit(1);

	if (_Widget)
	{
		auto PlWidget = Cast<UPlayerBarWidget>(_Widget);
		if (PlWidget)
		{
			float CurrentHP = _StatCom->GetCurHp();
			float CurrentMP = _StatCom->GetCurMp();
			float CurrentEXP = _StatCom->GetExp();

			// 플레이어 스탯
			UE_LOG(LogTemp, Warning, TEXT("Current HP: %f, Current MP: %f, Current EXP: %f"), CurrentHP, CurrentMP, CurrentEXP);

			_StatCom->_PlHPDelegate.AddUObject(PlWidget, &UPlayerBarWidget::SetPlHPBar);
			_StatCom->_PlMPDelegate.AddUObject(PlWidget, &UPlayerBarWidget::SetPlMPBar);
			_StatCom->_PlEXPDelegate.AddUObject(PlWidget, &UPlayerBarWidget::SetPlExpBar);
		}
	}

	ItemEquipped.AddDynamic(this, &AMyPlayer::EquipItem);

	_KnightanimInstance = Cast<UPlayerAnimInstance>(GetMesh()->GetAnimInstance());
	if (_KnightanimInstance->IsValidLowLevelFast())
	{
		_KnightanimInstance->OnMontageEnded.AddDynamic(this, &AMyPlayer::OnAttackEnded);
		_KnightanimInstance->_attackDelegate.AddUObject(this, &ACreature::AttackHit);
		_KnightanimInstance->_deathDelegate_Knight.AddUObject(this, &AMyPlayer::Disable);
	}
}

// Called every frame
void AMyPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if(_StatCom->IsDead())
		return;

	UpdateCamera(DeltaTime);

	if (bIsDashing)
	{
		PerformDash(DeltaTime);
	}

	if (_Widget)
	{
		auto PlWidget = Cast<UPlayerBarWidget>(_Widget);
		if (PlWidget)
		{
			int32 PlMaxHp = _StatCom->GetMaxHp();
			int32 PlMaxMp = _StatCom->GetMaxMp();
			int32 PlCurHp = _StatCom->GetCurHp();
			int32 PlCurMp = _StatCom->GetCurMp();

			float HPPercent = float(PlCurHp) / float(PlMaxHp);
			float MPPercent = float(PlCurMp) / float(PlMaxMp);

			float NewHPScaleX = float(PlMaxHp) / 1000.0f;
			float NewMPScaleX = float(PlMaxMp) / 50.0f;

			if (_StatCom->GetMaxHp() > _StatCom->GetCurHp())
			{
				PlWidget->Pl_HPBar->SetPercent(HPPercent);
				PlWidget->Pl_HPBar->SetRenderScale(FVector2D(NewHPScaleX, 3.0f));
			}

			if (_StatCom->GetMaxMp() > _StatCom->GetCurMp())
			{
				PlWidget->Pl_MPBar->SetPercent(MPPercent);
				PlWidget->Pl_MPBar->SetRenderScale(FVector2D(NewMPScaleX, 3.0f));
			}
		}
	}
}

float AMyPlayer::TakeDamage(float Damage, struct FDamageEvent const &DamageEvent, AController *EventInstigator, AActor *DamageCauser)
{
	Super::TakeDamage(Damage, DamageEvent, EventInstigator, DamageCauser);
	return 0.0f;
}

// Called to bind functionality to input
void AMyPlayer::SetupPlayerInputComponent(UInputComponent *PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent *EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputComponent->BindAction(_moveAction, ETriggerEvent::Triggered, this, &AMyPlayer::Move);
		EnhancedInputComponent->BindAction(_lookAction, ETriggerEvent::Triggered, this, &AMyPlayer::Look);
		EnhancedInputComponent->BindAction(_jumpAction, ETriggerEvent::Started, this, &AMyPlayer::JumpA);
		EnhancedInputComponent->BindAction(_attackAction, ETriggerEvent::Started, this, &AMyPlayer::AttackA);
		EnhancedInputComponent->BindAction(_skill1Action, ETriggerEvent::Started, this, &AMyPlayer::Skill1);
		EnhancedInputComponent->BindAction(_skill2Action, ETriggerEvent::Started, this, &AMyPlayer::Skill2);
		EnhancedInputComponent->BindAction(_skill3Action, ETriggerEvent::Started, this, &AMyPlayer::Skill3);
		EnhancedInputComponent->BindAction(_skill4Action, ETriggerEvent::Started, this, &AMyPlayer::Skill4);
		EnhancedInputComponent->BindAction(_mouseAction, ETriggerEvent::Triggered, this, &AMyPlayer::Mouse);
		EnhancedInputComponent->BindAction(_StatOpenAction, ETriggerEvent::Started, this, &AMyPlayer::StatUIOpen);
		EnhancedInputComponent->BindAction(_InvenOpenAction, ETriggerEvent::Started, this, &AMyPlayer::InvenUIOpen);
		EnhancedInputComponent->BindAction(_guardAction, ETriggerEvent::Started, this, &AMyPlayer::GuardStart);
		EnhancedInputComponent->BindAction(_guardAction, ETriggerEvent::Completed, this, &AMyPlayer::GuardEnd);
		EnhancedInputComponent->BindAction(_LockOnAction, ETriggerEvent::Started, this, &AMyPlayer::LockOn);
	}
}

void AMyPlayer::OnMonsterHit(class AMonster *HitMonster, const FHitResult &Hit)
{
	if (HitMonster)
	{
		FVector LaunchDirection = (HitMonster->GetActorLocation() - GetActorLocation()).GetSafeNormal();
		HitMonster->LaunchFromPlayer(LaunchDirection);
	}
}

void AMyPlayer::UpdateCamera(float DeltaTime)
{
	if (_lockOnMonster)
	{
		if (_lockOnMonster->_StatCom->IsDead())
		{
			_lockOnMonster = nullptr;
			_fixedCamera = false;
			return;
		}
		_fixedCamera = true;

		FVector LockedOnLocation = _lockOnMonster->GetActorLocation();
		LockedOnLocation.Z -= 150.f;
		const FRotator LookAtRotation = UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), LockedOnLocation);
		const FRotator InterpRotation = UKismetMathLibrary::RInterpTo(GetController()->GetControlRotation(), LookAtRotation, DeltaTime, 10.f);
		GetController()->SetControlRotation(FRotator(InterpRotation.Pitch, InterpRotation.Yaw, GetController()->GetControlRotation().Roll));
	}
}

void AMyPlayer::EquipItem(AEquipItem *equipitem)
{
	SetEquipItem(equipitem->GetEquipType(), equipitem);
}

void AMyPlayer::GetItem(ABaseItem *item)
{
	if (item == nullptr)
		return;

	_inventoryComponent->AddItem(0, item);
}

void AMyPlayer::SetEquipItem(EItemType equiptype, AEquipItem *equipitem)
{
	if (_EquipItems.Contains(equiptype))
	{
		// TODO
		return;
	}
	else
	{
		_EquipItems.Add(equiptype, equipitem);
	}
	// TODO:Update UI
}

FString AMyPlayer::GetSwingSoundName() const
{
	return "SwingSound_Sword_01";
}

FString AMyPlayer::GetHitSoundName() const
{
	return "TakeSound_Sword_01";
}

FString AMyPlayer::GetGuardOn() const
{
	return "ShieldGuard_On";
}

FString AMyPlayer::GetGuardOff() const
{
	return "ShieldGuard_Off";
}

FString AMyPlayer::GetSkillSound01() const
{
	return "Skill01_Sound";
}

FString AMyPlayer::GetSkillSound02() const
{
	return "Skill02_Sound";
}

FString AMyPlayer::GetSkillParticleEffect02() const
{
	return "NS_Meteor";
}

FString AMyPlayer::GetPlayerAttackHitEffect() const
{
	return "P_Greystone_Novaborn_Primary_Impact";
}

FString AMyPlayer::GetSkillSound03() const
{
	return "Skill03_Sound_Begin_Cue";
}

FString AMyPlayer::GetSkillSound03Shout() const
{
	return "Skill03_Shout";
}

FString AMyPlayer::GetPlayerSkillEffect04_Start() const
{
	return "NS_Skill04_Start";
}

FString AMyPlayer::GetPlayerSkillEffect04_Durring() const
{
	return "NS_Priest_Sphere";
}

FString AMyPlayer::GetSkillSound04Start() const
{
	return "Skill04_Sound_Start";
}

FString AMyPlayer::GetSkillSound04Durring() const
{
	return "Skill04_Sound_02_during";
}

FString AMyPlayer::GetUIBaseSound() const
{
	return "BaseUISound_02_Cue";
}

FString AMyPlayer::GetLevelUpSound() const
{
	return "LevelupSound_Cue";
}




void AMyPlayer::Move(const FInputActionValue &value)
{
	if (bIsGuarding)
		return;
	FVector2D MovementVector = value.Get<FVector2D>();

	_moveVector = MovementVector;

	AddMovementInput(GetActorForwardVector(), MovementVector.Y);
	AddMovementInput(GetActorRightVector(), MovementVector.X);
}

void AMyPlayer::Look(const FInputActionValue &value)
{
	if (_fixedCamera)
		return;
	FVector2D LookAxisVector = value.Get<FVector2D>();

	AddControllerYawInput(LookAxisVector.X);
	AddControllerPitchInput(LookAxisVector.Y);
}

void AMyPlayer::JumpA(const FInputActionValue &value)
{
	bool isPressed = value.Get<bool>();

	if (isPressed)
	{
		if (!_isAttacking)
			ACharacter::Jump();
	}
}

void AMyPlayer::AttackA(const FInputActionValue &value)
{
	bool isPressed = value.Get<bool>();

	if (isPressed && _isAttacking == false && _KnightanimInstance != nullptr)
	{
		 if (bIsSkillReadyToCast) 
        {
            bIsSkillReadyToCast = false;

            GetWorld()->GetTimerManager().ClearTimer(TimerHandle_UpdateDecal);
			
            if (SpawnedDecalActor)
            {
                SpawnedDecalActor->Destroy();
                SpawnedDecalActor = nullptr;
            }

            ConfirmSkillLocation();
			return;
        }

		if (bIsGuarding)
			bIsGuarding = false;
		_KnightanimInstance->PlayAttackMontage();
		_isAttacking = true;

		_curAttackIndex %= 4;
		_curAttackIndex++;

		_KnightanimInstance->JumpToSection(_curAttackIndex);
	}
}

void AMyPlayer::Skill1(const FInputActionValue &value)
{
	bool isPressed = value.Get<bool>();

	if (isPressed && _skillWidgetInstance != nullptr)
	{
		if (SkillOnCooldown[0])
			return;
		else
		{
			SkillOnCooldown[0] = true;
			bIsDashing = true;

			FVector2D MovementInput = _moveVector;
			UE_LOG(LogTemp, Warning, TEXT("%f"), GetVelocity().Size());

			if (GetVelocity().Size() > 300.f)
			{
				FVector Forward = GetActorForwardVector() * MovementInput.Y;
				FVector Right = GetActorRightVector() * MovementInput.X;
				DashDirection = (Forward + Right).GetSafeNormal();
			}
			else
			{
				DashDirection = GetActorForwardVector();
			}

			DashTimeElapsed = 0.f;
			_skillWidgetInstance->StartCooldown(0, 5.0f);

			UPlayerAnimInstance *PlayerAnimInstance = Cast<UPlayerAnimInstance>(GetMesh()->GetAnimInstance());
			if (PlayerAnimInstance)
			{
				PlayerAnimInstance->PlaySkill01Montage();
			}
			SoundManager->PlaySound(*GetSkillSound01(), _hitPoint);

			if (_StatCom->GetInt() >= 40)
			{
				FVector TeleportLocation = GetActorLocation() + DashDirection * _dashSpeed * 1.0f;
				SetActorLocation(TeleportLocation, true);

				bIsDashing = false;
			}
		}
	}
}

void AMyPlayer::Skill2(const FInputActionValue &value)
{
    bool isPressed = value.Get<bool>();

    if (isPressed)
    {
        if (_skillWidgetInstance != nullptr && !SkillOnCooldown[1]) 
        {
			APlayerController *PlayerController = Cast<APlayerController>(GetController());
			
			if(SpawnedDecalActor)
			{
				bIsSkillReadyToCast = false;
				SpawnedDecalActor->Destroy();
				SpawnedDecalActor =  nullptr;
				PlayerController->bShowMouseCursor = false;
				PlayerController->SetInputMode(FInputModeGameOnly());
				return;
			}

            if (SkillDecalActor && !SpawnedDecalActor)
            {
                SpawnedDecalActor = GetWorld()->SpawnActor<ADecalActor>(SkillDecalActor);
                if (SpawnedDecalActor)
                {
                    SpawnedDecalActor->SetLifeSpan(0);
                }
            }


            if (PlayerController)
            {
                bool bIsCursorVisible = PlayerController->bShowMouseCursor;
                PlayerController->bShowMouseCursor = true;
                PlayerController->SetInputMode(FInputModeGameAndUI().SetHideCursorDuringCapture(false));
            }

            bIsSkillReadyToCast = true;

            GetWorld()->GetTimerManager().SetTimer(TimerHandle_UpdateDecal, this, &AMyPlayer::UpdateDecalLocation, 0.01f, true);
        }
    }
}

void AMyPlayer::UpdateDecalLocation()
{
    AMyPlayerController *PlayerController = Cast<AMyPlayerController>(GetController());
    if (PlayerController && SpawnedDecalActor)
    {
        FHitResult HitResult;
        PlayerController->GetHitResultUnderCursor(ECC_Visibility, false, HitResult);

        if (HitResult.bBlockingHit)
        {
			if(HitResult.ImpactNormal.Z > 0.5f)
			{
				 FVector NewLocation = HitResult.ImpactPoint;
            	TargetSkillLocation = NewLocation;
				TargetSkillLocation.Z += 1.0f;
            	SpawnedDecalActor->SetActorLocation(TargetSkillLocation);
			}
        }
    }
}

void AMyPlayer::ConfirmSkillLocation()
{
    if (SkillOnCooldown[1])
        return;

    SkillOnCooldown[1] = true;

    FActorSpawnParameters SpawnParams;
    SpawnParams.Owner = this;
    SpawnParams.Instigator = GetInstigator();

    AMyPlayerController *PlayerController = Cast<AMyPlayerController>(GetController());
    if (PlayerController)
    {
        PlayerController->bShowMouseCursor = false;
        PlayerController->SetInputMode(FInputModeGameOnly());
    }

    FVector MeteorStartLocation = GetActorLocation() + FVector(0, 0, 5000.0f);
    FVector DecalLocation = TargetSkillLocation;

    int MeteorCount = (_StatCom->GetInt()) / 10;

    AMeteorDecal *CenterMeteorDecal = GetWorld()->SpawnActor<AMeteorDecal>(_decal, DecalLocation, FRotator::ZeroRotator, SpawnParams);
    if (CenterMeteorDecal)
    {
        CenterMeteorDecal->StartMeteor(MeteorStartLocation, DecalLocation, 3.0f);
    }

    for (int i = 0; i < MeteorCount - 1; i++)
    {
        float Angle = (i * (360.0f / (MeteorCount - 1))) * (PI / 180.0f);
        float Radius = 900.0f;

        FVector SpawnLocation = DecalLocation;
        SpawnLocation.X += FMath::Cos(Angle) * Radius;
        SpawnLocation.Y += FMath::Sin(Angle) * Radius;

        AMeteorDecal *MeteorDecal = GetWorld()->SpawnActor<AMeteorDecal>(_decal, SpawnLocation, FRotator::ZeroRotator, SpawnParams);
        if (MeteorDecal)
        {
            MeteorDecal->StartMeteor(MeteorStartLocation, SpawnLocation, 3.0f);
        }
    }

    _skillWidgetInstance->StartCooldown(1, 5.0f);

    UPlayerAnimInstance *PlayerAnimInstance = Cast<UPlayerAnimInstance>(GetMesh()->GetAnimInstance());
    if (PlayerAnimInstance)
    {
        PlayerAnimInstance->PlaySkill02Montage();
    }

    SoundManager->PlaySound(*GetSkillSound02(), _hitPoint);
}






void AMyPlayer::Skill3(const FInputActionValue &value)
{
	bool isPressed = value.Get<bool>();

	if (isPressed && _skillWidgetInstance != nullptr)
	{
		if (SkillOnCooldown[2])
			return;
		else
		{
			SkillOnCooldown[2] = true;
			_skillWidgetInstance->StartCooldown(2, 5.0f);
			if (_fireball != nullptr)
			{
				SoundManager->PlaySound(*GetSkillSound03(), this->GetActorLocation());
				SoundManager->PlaySound(*GetSkillSound03Shout(), this->GetActorLocation());

				UPlayerAnimInstance* PlayerAnimInstance = Cast<UPlayerAnimInstance>(GetMesh()->GetAnimInstance());
				if (PlayerAnimInstance)
				{
					PlayerAnimInstance->PlaySkill03Montage();
				}



				int FireballCount = _StatCom->GetInt() / 10;
				FRotator spawnRotation = GetActorRotation();

				for (int i = 0; i < FireballCount; i++)
				{
					float Angle = (i * (360.0f / FireballCount)) * (PI / 180.0f);
					float Radius = 500.0f;

					FVector spawnLocation = GetActorLocation() + GetActorForwardVector() * 50.0f;
					spawnLocation.X += FMath::Cos(Angle) * Radius;
					spawnLocation.Y += FMath::Sin(Angle) * Radius;
					AFireball *Fireball = GetWorld()->SpawnActor<AFireball>(_fireball, spawnLocation, spawnRotation);

					if (Fireball)
					{
						Fireball->InitializeOrbit(Radius, Angle, FireballCount);
					}
				}
			}
		}
	}
}

void AMyPlayer::Skill4(const FInputActionValue &value)
{
	bool isPressed = value.Get<bool>();

	if (isPressed && _skillWidgetInstance != nullptr)
	{
		if (SkillOnCooldown[3])
			return;
		else
		{
			_StatCom->SetStatBoost(_StatCom->GetInt());

			SkillOnCooldown[3] = true;
			_skillWidgetInstance->StartCooldown(3, 10.0f);

			EffectManager->Play(*GetPlayerSkillEffect04_Start(), GetActorLocation());
			SoundManager->PlaySound(*GetSkillSound04Start(), GetActorLocation());
				

			EffectManager->PlayOnSkeletalMesh(*GetPlayerSkillEffect04_Durring(), _lowerBodyMesh, "root");
			//SoundManager->PlaySound(*GetSkillSound04Durring(), GetActorLocation());
			//SoundManager->StopSound(*GetSkillSound04Durring());
			SoundManager->PlaySoundWithDuration(*GetSkillSound04Durring(), GetActorLocation(), 17.9f);

		
		}
	}
}

void AMyPlayer::Mouse(const FInputActionValue &value)
{
	APlayerController *PlayerController = Cast<APlayerController>(GetController());

	if (PlayerController)
	{
		bool bIsCursorVisible = PlayerController->bShowMouseCursor;

		if (bIsCursorVisible)
		{
			PlayerController->bShowMouseCursor = false;
			PlayerController->SetInputMode(FInputModeGameOnly());
		}
		else
		{
			PlayerController->bShowMouseCursor = true;
			PlayerController->SetInputMode(FInputModeGameAndUI().SetHideCursorDuringCapture(false));
		}
	}
}

void AMyPlayer::GuardEnd(const FInputActionValue &value)
{
	bIsGuarding = false;

	UPlayerAnimInstance *PlayerAnimInstance = Cast<UPlayerAnimInstance>(GetMesh()->GetAnimInstance());
	if (PlayerAnimInstance)
	{
		PlayerAnimInstance->PlayGuardMontage(bIsGuarding);
	}
}

void AMyPlayer::LockOn(const FInputActionValue &value)
{
	bool isPressed = value.Get<bool>();

	if (isPressed)
	{
		if (_lockOnMonster)
		{
			_lockOnMonster = nullptr;
			_fixedCamera = false;
			return;
		}
		else
		{
			FHitResult HitResult;
			FVector Start = GetActorLocation();
			FVector ForwardVector = GetActorForwardVector();
			float LockOnDistance = 2000.0f;
			float LockOnAngle = 60.0f;
			float HalfAngle = LockOnAngle / 2.0f;

			for (float AngleOffset = -HalfAngle; AngleOffset <= HalfAngle; AngleOffset += 5.0f)
			{
				FQuat Rotation = FQuat::MakeFromEuler(FVector(0.0f, 0.0f, AngleOffset));
				FVector End = Start + (Rotation.RotateVector(ForwardVector) * LockOnDistance);

				FCollisionQueryParams CollisionParams;
				CollisionParams.bTraceComplex = true;
				CollisionParams.AddIgnoredActor(this);
				DrawDebugLine(GetWorld(), Start, End, FColor::Green, false, 2.0f, 0, 1.0f);

				if (GetWorld()->LineTraceSingleByChannel(HitResult, Start, End, ECC_Pawn, CollisionParams))
				{
					DrawDebugLine(GetWorld(), Start, End, FColor::Red, false, 2.0f, 0, 1.0f);
					AMonster *monster = Cast<AMonster>(HitResult.GetActor());
					if (monster != nullptr)
					{
						UE_LOG(LogTemp, Warning, TEXT("LockOnMonster"));
						_lockOnMonster = monster;
						break;
					}
				}
			}
		}
	}
}

void AMyPlayer::GuardStart(const FInputActionValue &value)
{
	bIsGuarding = true;

	// Animation
	UPlayerAnimInstance *PlayerAnimInstance = Cast<UPlayerAnimInstance>(GetMesh()->GetAnimInstance());
	if (PlayerAnimInstance)
	{
		PlayerAnimInstance->PlayGuardMontage(bIsGuarding);
	}
}

// cheol
void AMyPlayer::StatUIOpen(const FInputActionValue &value)
{
	bool isPressed = value.Get<bool>();

	UE_LOG(LogTemp, Error, TEXT("StatUI Errow"));

	SoundManager->PlaySound(*GetUIBaseSound(), GetActorLocation());

	if (isPressed && _statWidget != nullptr)
	{
		if (_statWidget->IsVisible())
		{
			_statWidget->SetVisibility(ESlateVisibility::Hidden);
		}
		else
		{
			_statWidget->UpdateStatDisplay();
			_statWidget->SetVisibility(ESlateVisibility::Visible);
		}
	}
}

void AMyPlayer::InvenUIOpen(const FInputActionValue &value)
{
	bool isPressed = value.Get<bool>();

	auto invenUI = UIManager->GetInventoryUI();

	SoundManager->PlaySound(*GetUIBaseSound(), GetActorLocation());

	if (isPressed && invenUI != nullptr)
	{
		UIManager->ToggleUI(UI_LIST::Inventory);
	}
}

void AMyPlayer::PerformDash(float DeltaTime)
{
	if (DashTimeElapsed < DashDuration)
	{
		FVector DashVelocity = DashDirection * _dashSpeed * DeltaTime;
		AddActorWorldOffset(DashVelocity, true);

		DashTimeElapsed += DeltaTime;
	}
	else
	{
		bIsDashing = false;
	}
}

void AMyPlayer::StartScreenShake()
{
	static float InitialShakeStrength = 0.1f;
	static float MaxShakeStrength = 10.0f;
	static float IncreaseAmount = 3.0f;
	static float Duration = 1.0f;
	static float ElapsedTime = 0.0f;

	if (_cameraShakeClass)
	{
		UGameplayStatics::GetPlayerCameraManager(this, 0)->StartCameraShake(_cameraShakeClass, InitialShakeStrength);
	}

	ElapsedTime += GetWorld()->GetDeltaSeconds();

	float CurrentShakeStrength = FMath::Lerp(InitialShakeStrength, MaxShakeStrength, FMath::Clamp(ElapsedTime / Duration, 0.0f, 1.0f));

	if (ElapsedTime < Duration)
	{
		UGameplayStatics::GetPlayerCameraManager(this, 0)->StartCameraShake(_cameraShakeClass, CurrentShakeStrength);
	}
	else
	{
		UGameplayStatics::GetPlayerCameraManager(this, 0)->StartCameraShake(_cameraShakeClass, MaxShakeStrength * 2.0f);
		GetWorld()->GetTimerManager().ClearTimer(ScreenShakeTimerHandle);
		ElapsedTime = 0.0f;
	}
}

void AMyPlayer::SavePlayerState()
{
	UMyPlayerSaveGame* SaveGameInstance = Cast<UMyPlayerSaveGame>(UGameplayStatics::CreateSaveGameObject(UMyPlayerSaveGame::StaticClass()));

	if (GetMesh() && GetMesh()->GetSkeletalMeshAsset())
	{
		SaveGameInstance->BodyMeshName = GetMesh()->GetSkeletalMeshAsset()->GetPathName();
	}

	if (_lowerBodyMesh && _lowerBodyMesh->GetSkeletalMeshAsset())
	{
		SaveGameInstance->LowerBodyMeshName = _lowerBodyMesh->GetSkeletalMeshAsset()->GetPathName();
	}
	if (_shoulderBodyMesh && _shoulderBodyMesh->GetSkeletalMeshAsset())
	{
		SaveGameInstance->ShoulderBodyMeshName = _shoulderBodyMesh->GetSkeletalMeshAsset()->GetPathName();
	}
	if (_swordBodyMesh && _swordBodyMesh->GetSkeletalMeshAsset())
	{
		SaveGameInstance->SwordBodyMeshName = _swordBodyMesh->GetSkeletalMeshAsset()->GetPathName();
	}
	if (_shieldBodyMesh && _shieldBodyMesh->GetSkeletalMeshAsset())
	{
		SaveGameInstance->ShieldBodyMeshName = _shieldBodyMesh->GetSkeletalMeshAsset()->GetPathName();
	}

	UGameplayStatics::SaveGameToSlot(SaveGameInstance, TEXT("PlayerSaveSlot"), 0);
}

void AMyPlayer::LoadPlayerState()
{
	UMyPlayerSaveGame* LoadGameInstance = Cast<UMyPlayerSaveGame>(UGameplayStatics::LoadGameFromSlot(TEXT("PlayerSaveSlot"), 0));
	if (LoadGameInstance)
	{
		if (!LoadGameInstance->BodyMeshName.IsEmpty())
		{
			GetMesh()->SetSkeletalMesh(LoadObject<USkeletalMesh>(nullptr, *LoadGameInstance->BodyMeshName));
		}
		if (!LoadGameInstance->LowerBodyMeshName.IsEmpty())
		{
			_lowerBodyMesh->SetSkeletalMesh(LoadObject<USkeletalMesh>(nullptr, *LoadGameInstance->LowerBodyMeshName));
		}
		if (!LoadGameInstance->ShoulderBodyMeshName.IsEmpty())
		{
			_shoulderBodyMesh->SetSkeletalMesh(LoadObject<USkeletalMesh>(nullptr, *LoadGameInstance->ShoulderBodyMeshName));
		}
		if (!LoadGameInstance->SwordBodyMeshName.IsEmpty())
		{
			_swordBodyMesh->SetSkeletalMesh(LoadObject<USkeletalMesh>(nullptr, *LoadGameInstance->SwordBodyMeshName));
		}
		if (!LoadGameInstance->ShieldBodyMeshName.IsEmpty())
		{
			_shieldBodyMesh->SetSkeletalMesh(LoadObject<USkeletalMesh>(nullptr, *LoadGameInstance->ShieldBodyMeshName));
		}
	}
}