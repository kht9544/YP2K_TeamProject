#include "MyPlayer.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Camera/CameraShakeBase.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "MyPlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "../UI/SkillWidget_test.h"
#include "../Monster/NormalMonster.h"

// Sets default values
AMyPlayer::AMyPlayer()
{
	PrimaryActorTick.bCanEverTick = true;

	_springArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	_camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));

	_springArm->SetupAttachment(GetCapsuleComponent());
	_camera->SetupAttachment(_springArm);

	_springArm->TargetArmLength = 500.0f;
	_springArm->SetRelativeRotation(FRotator(-35.0f, 0.0f, 0.0f));

	 static ConstructorHelpers::FObjectFinder<USkeletalMesh> PS(TEXT("/Script/Engine.SkeletalMesh'/Game/ParagonGreystone/Characters/Heroes/Greystone/Meshes/Greystone.Greystone'"));

	 if (PS.Succeeded())
	 {
	 	GetMesh()->SetSkeletalMesh(PS.Object);
	 }
	GetMesh()->SetRelativeLocationAndRotation(FVector(0.0f, 0.0f, -88.0f), FRotator(0.0f, -90.0f, 0.0f));

	static ConstructorHelpers::FClassFinder<UCameraShakeBase> CS(TEXT("/Script/Engine.Blueprint'/Game/Blueprint/Player/LegacyCamera_BP.LegacyCamera_BP_C'"));
	if (CS.Succeeded())
	{
		CameraShakeClass = CS.Class;
	}

	//_parkourComp = CreateDefaultSubobject<UParkourComponent_Test>(TEXT("ParkourComponent"));

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
	AMyPlayerController *MyController = Cast<AMyPlayerController>(GetController());
	if (MyController != nullptr)
	{
		_skillWidgetInstance = MyController->SkillWidgetInstance;
	}
}

void AMyPlayer::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	SkillOnCooldown.Init(false, 4);
	Equipment.Init(nullptr, 6);
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
	}
}

void AMyPlayer::OnMonsterHit(class ANormalMonster *HitMonster, const FHitResult &Hit)
{
	if (HitMonster)
	{
		FVector LaunchDirection = (HitMonster->GetActorLocation() - GetActorLocation()).GetSafeNormal();
		float LaunchStrength = HitMonster->GetLaunchLength();
		HitMonster->LaunchFromPlayer(LaunchDirection, LaunchStrength); // 몬스터 튕겨나가기
	}
}

void AMyPlayer::Move(const FInputActionValue &value)
{
	FVector2D MovementVector = value.Get<FVector2D>();

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
			DashDirection = GetActorForwardVector();
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

void AMyPlayer::StartScreenShake()
{
	static float InitialShakeStrength = 0.1f;
    static float MaxShakeStrength = 10.0f;
    static float IncreaseAmount = 3.0f; 
    static float Duration = 1.0f;
    static float ElapsedTime = 0.0f;

    if (CameraShakeClass)
    {
        UGameplayStatics::GetPlayerCameraManager(this, 0)->StartCameraShake(CameraShakeClass, InitialShakeStrength);
    }

    ElapsedTime += GetWorld()->GetDeltaSeconds();

    float CurrentShakeStrength = FMath::Lerp(InitialShakeStrength, MaxShakeStrength, ElapsedTime / Duration);

    if (ElapsedTime < Duration)
    {
        UGameplayStatics::GetPlayerCameraManager(this, 0)->StartCameraShake(CameraShakeClass, CurrentShakeStrength);
    }
    else
    {
        GetWorld()->GetTimerManager().ClearTimer(ScreenShakeTimerHandle);
        ElapsedTime = 0.0f;
    }
}

void AMyPlayer::CastMeteor()
{
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
