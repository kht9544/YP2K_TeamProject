#include "MyPlayer.h"
#include "Components/CapsuleComponent.h"
#include "Components/SkeletalMeshComponent.h"
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
#include "MyDecal.h"
#include "Kismet/KismetMathLibrary.h"

// chelo
#include "Component/StatComponent.h"
#include "UI/StatWidget.h"
#include "Components/WidgetComponent.h"

//MiniMap
#include "GameFramework/Actor.h"
#include "Components/SceneCaptureComponent2D.h"
#include "PaperSpriteComponent.h"
#include "UI/MiniMapWidget.h"

// te
#include "GameFramework/Actor.h"

// Animation
#include "../Animation/PlayerAnimInstance.h"
#include "../Animation/Knight_AnimInstance.h"

// Sets default values
AMyPlayer::AMyPlayer()
{
	PrimaryActorTick.bCanEverTick = true;

	_springArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	_camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));

	//_upperBodyMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("UpperSkeletal"));
	_lowerBodyMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("LowerSkeletal"));
	_shoulderBodyMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("ShoulderSkeletal"));
	_swordBodyMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SwordSkeletal"));
	_shieldBodyMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("ShieldSkeletal"));

	_springArm->SetupAttachment(GetCapsuleComponent());
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
	_MinimapSprite->SetWorldScale3D(FVector(0.5f));
	_MinimapSprite->SetWorldLocation(FVector(0.f, 0.f, 300.f));
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

	// cheol
	_StatCom = CreateDefaultSubobject<UStatComponent>(TEXT("StatCom"));

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

	static ConstructorHelpers::FClassFinder<AMyDecal> MD(TEXT("/Script/Engine.Blueprint'/Game/Blueprint/VFX/Decal_BP.Decal_BP_C'"));
	if (MD.Succeeded())
	{
		_decal = MD.Class;
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

	if (_StatCom)
	{
		_StatCom->SetLevelInit(1);
	}

	ItemEquipped.AddDynamic(this,&AMyPlayer::EquipItem);
}

// Called every frame
void AMyPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (bIsDashing)
	{
		PerformDash(DeltaTime);
	}
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
	}
}


void AMyPlayer::OnMonsterHit(class ANormalMonster *HitMonster, const FHitResult &Hit)
{
	if (HitMonster)
	{
		FVector LaunchDirection = (HitMonster->GetActorLocation() - GetActorLocation()).GetSafeNormal();
		HitMonster->LaunchFromPlayer(LaunchDirection);
	}
}

void AMyPlayer::EquipItem(AEquipItem* equipitem)
{
	SetEquipItem(equipitem->GetEquipType(),equipitem);
}

void AMyPlayer::SetEquipItem(EItemType equiptype, AEquipItem* equipitem)
{
    if (_EquipItems.Contains(equiptype))
    {
		//TODO 
        return;
    }
    else
    {
        _EquipItems.Add(equiptype, equipitem);
	}
	// TODO:Update UI
}

void AMyPlayer::Move(const FInputActionValue &value)
{
	FVector2D MovementVector = value.Get<FVector2D>();

	_moveVector = MovementVector;
	AddMovementInput(GetActorForwardVector(), MovementVector.Y);
	AddMovementInput(GetActorRightVector(), MovementVector.X);
}

void AMyPlayer::Look(const FInputActionValue &value)
{
	FVector2D LookAxisVector = value.Get<FVector2D>();

	AddControllerYawInput(LookAxisVector.X);
	AddControllerPitchInput(LookAxisVector.Y);
}

void AMyPlayer::JumpA(const FInputActionValue &value)
{
	bool isPressed = value.Get<bool>();

	if (isPressed)
	{
		ACharacter::Jump();
	}
}

void AMyPlayer::AttackA(const FInputActionValue &value)
{
	bool isPressed = value.Get<bool>();
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

			if (GetVelocity().Size() > 0.1f)
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
		}
	}
}

void AMyPlayer::Skill2(const FInputActionValue &value)
{
	bool isPressed = value.Get<bool>();

	if (isPressed && _skillWidgetInstance != nullptr)
	{
		if (SkillOnCooldown[1])
			return;
		else
		{
			SkillOnCooldown[1] = true;

			FActorSpawnParameters SpawnParams;
			SpawnParams.Owner = this;
			SpawnParams.Instigator = GetInstigator();
			FVector DecalLocation = GetActorLocation() + GetActorForwardVector() * 1000.0f;
			DecalLocation.Z = 0.0f;

			AMyDecal *Decal = GetWorld()->SpawnActor<AMyDecal>(_decal, DecalLocation, FRotator::ZeroRotator, SpawnParams);
			GetWorld()->GetTimerManager().SetTimer(ScreenShakeTimerHandle, this, &AMyPlayer::StartScreenShake, 0.1f, true);
			GetWorld()->GetTimerManager().SetTimer(MeteorTimerHandle, this, &AMyPlayer::CastMeteor, 3.0f, false);
			_skillWidgetInstance->StartCooldown(1, 5.0f);
		}
	}
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
			SkillOnCooldown[3] = true;
			_skillWidgetInstance->StartCooldown(3, 10.0f);
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

// cheol
void AMyPlayer::StatUIOpen(const FInputActionValue &value)
{
	bool isPressed = value.Get<bool>();

	UE_LOG(LogTemp, Error, TEXT("StatUI Errow"));

	if (isPressed && _statWidget != nullptr)
	{
		if (_statWidget->IsVisible())
		{
			_statWidget->SetVisibility(ESlateVisibility::Hidden);
		}
		else
		{
			_statWidget->HPUpdate(_StatCom->GetMaxHp());
			_statWidget->MPUpdate(_StatCom->GetMaxMp());
			_statWidget->STRUpdate(_StatCom->GetStr());
			_statWidget->DEXUpdate(_StatCom->GetDex());
			_statWidget->INTUpdate(_StatCom->GetInt());
			_statWidget->BonusPointUpdate(_StatCom->GetBonusPoint());
			_statWidget->PlLevelUpdate(_StatCom->GetLevel());
			_statWidget->SetVisibility(ESlateVisibility::Visible);
		}
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

void AMyPlayer::CastMeteor()
{
}

// void AMyPlayer::CheckForClimbableWall()
// {
// 	FVector Start = GetActorLocation();
// 	FVector ForwardVector = GetActorForwardVector();
// 	FVector End = Start + (ForwardVector * 100.0f);

// 	FHitResult HitResult;
// 	FCollisionQueryParams Params;
// 	Params.AddIgnoredActor(this);

// 	bool bHit = GetWorld()->LineTraceSingleByChannel(HitResult, Start, End, ECC_Visibility, Params);

// 	if (bHit && HitResult.bBlockingHit)
// 	{
// 		if (!_parkourComp->bIsClimbing)
// 		{
// 			// 벽타기 시작
// 			_parkourComp->StartClimbing(HitResult.ImpactNormal);
// 		}
// 	}
// 	else
// 	{
// 		if (_parkourComp->bIsClimbing)
// 		{
// 			// 벽이 없으므로 벽타기 멈추기
// 			_parkourComp->StopClimbing();
// 		}
// 	}
// }
