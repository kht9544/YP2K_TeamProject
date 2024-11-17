// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/Dragon.h"
//-----추가-----
#include "Base/MyGameInstance.h"
#include "Player/MyPlayer.h"
#include "EngineUtils.h"
#include "GameFramework/PlayerController.h"

#include "../Animation/PlayerAnimInstance.h"
#include "../Animation/DragonAnimInstance.h"
#include "GameFramework/CharacterMovementComponent.h"

#include "Components/CapsuleComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "Kismet/GameplayStatics.h"
#include "MyPlayerController.h"



ADragon::ADragon()
{
	PrimaryActorTick.bCanEverTick = false;
	KnightInstance = nullptr;

    // 드래곤의 비행을 위해 중력 제거
    GetCharacterMovement()->GravityScale = 0.0f;

    GetCapsuleComponent()->InitCapsuleSize(100.0f, 150.0f);

   /* GetCharacterMovement()->bOrientRotationToMovement = true;
    GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f);*/
    
    _springArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
    _camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
    
    _springArm->SetupAttachment(RootComponent);
    _camera->SetupAttachment(_springArm);

    _springArm->TargetArmLength = 1200.0f;
    _springArm->SetRelativeRotation(FRotator(-35.0f, 0.0f, 0.0f));


    static ConstructorHelpers::FObjectFinder<USkeletalMesh> DragonMeshAsset(TEXT("/Script/Engine.SkeletalMesh'/Game/QuadrapedCreatures/MountainDragon/Meshes/SK_MOUNTAIN_DRAGON.SK_MOUNTAIN_DRAGON'"));
    if (DragonMeshAsset.Succeeded())
    {
        GetMesh()->SetSkeletalMesh(DragonMeshAsset.Object);
    }

    GetMesh()->SetRelativeLocation(FVector(0.0f, 0.0f, -90.0f)); // 예: 메쉬를 살짝 아래로 배치
    GetMesh()->SetRelativeRotation(FRotator(0.0f, -90.0f, 0.0f));


}

void ADragon::BeginPlay()
{
	Super::BeginPlay();

    for (TActorIterator<AMyPlayer> It(GetWorld()); It; ++It)
    {
        KnightInstance = *It;
        if (KnightInstance)
        {
            UE_LOG(LogTemp, Warning, TEXT("KnightInstance found and assigned!"));
            break;
        }
    }

    if (!KnightInstance)
    {
        UE_LOG(LogTemp, Error, TEXT("KnightInstance not found in the world!"));
        return;
    }

    // Dragon 초기화
    SetActorHiddenInGame(true);
    SetActorEnableCollision(false);
    _isTransformed = false;

}

void ADragon::TransformToHuman()
{
    if (!_isTransformed)
    {
        UE_LOG(LogTemp, Warning, TEXT("Not in transformed state, cannot revert!"));
        return;
    }

    if (!KnightInstance)
    {
        UE_LOG(LogTemp, Error, TEXT("KnightInstance does not exist, cannot revert to human state!"));
        return;
    }

    if (APlayerController* PC = Cast<APlayerController>(GetController()))
    {
        // 상태 복원
        KnightInstance->SetActorLocation(SavedLocation);
        KnightInstance->SetActorRotation(SavedRotation);

        // MyPlayer 활성화
        KnightInstance->SetActorHiddenInGame(false);
        KnightInstance->SetActorEnableCollision(true);

        // Dragon 비활성화
        SetActorHiddenInGame(true);
        SetActorEnableCollision(false);

        // 컨트롤 전환
        PC->Possess(KnightInstance);

        // 상태 업데이트
        _isTransformed = false;
        KnightInstance->_isTransformed = false;

        UE_LOG(LogTemp, Warning, TEXT("Transformed back to MyPlayer!"));
    }
}

void ADragon::TransformToDragon()
{
    if (_isTransformed)
    {
        UE_LOG(LogTemp, Warning, TEXT("Already transformed!"));
        return;
    }

    if (!KnightInstance)
    {
        UE_LOG(LogTemp, Error, TEXT("KnightInstance does not exist!"));
        return;
    }

    // MyPlayer에서 Dragon으로 복귀
    KnightInstance->TransformToDragon();
}

void ADragon::ToggleTransformation()
{
    if (_isTransformed) // 현재 변환된 상태이면 인간으로 복귀
    {
        TransformToHuman();
    }
    else // 그렇지 않으면 드래곤으로 변환
    {
        TransformToDragon();
    }
}

void ADragon::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);

    if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
    {
        EnhancedInputComponent->BindAction(_moveAction, ETriggerEvent::Triggered, this, &ADragon::Move);
        EnhancedInputComponent->BindAction(_lookAction, ETriggerEvent::Triggered, this, &ADragon::Look);
        EnhancedInputComponent->BindAction(_jumpAction, ETriggerEvent::Started, this, &ADragon::JumpA);     
        EnhancedInputComponent->BindAction(_Change, ETriggerEvent::Started, this, &ADragon::ToggleTransformation);
     
    }
}

void ADragon::Move(const FInputActionValue& value)
{
    // fly할때 isFalling 통해서 생각해볼것..
    FVector2D MovementVector = value.Get<FVector2D>();

    //_moveVector = MovementVector;

    AddMovementInput(GetActorForwardVector(), MovementVector.Y);
    AddMovementInput(GetActorRightVector(), MovementVector.X);
}

void ADragon::Look(const FInputActionValue& value)
{
    FVector2D LookAxisVector = value.Get<FVector2D>();

    AddControllerYawInput(LookAxisVector.X);
    AddControllerPitchInput(LookAxisVector.Y);
}

void ADragon::JumpA(const FInputActionValue& value)
{
    bool isPressed = value.Get<bool>();

    if (isPressed)
    {
        if (!_isAttacking)
            ACharacter::Jump();
    }
}

void ADragon::PostInitializeComponents()
{
    Super::PostInitializeComponents();

    // 애니메이션 인스턴스 클래스를 설정
    if (DragonAnimInstanceClass)
    {
        USkeletalMeshComponent* MeshComp = GetMesh();
        if (MeshComp)
        {
            MeshComp->SetAnimInstanceClass(DragonAnimInstanceClass);
        }
    }

    // 애니메이션 인스턴스 캐스팅
    _dragonAnimInstance = Cast<UDragonAnimInstance>(GetMesh()->GetAnimInstance());
    if (_dragonAnimInstance && _dragonAnimInstance->IsValidLowLevelFast())
    {
        // 애니메이션 몽타주 끝났을 때 처리할 델리게이트 연결
        _dragonAnimInstance->OnMontageEnded.AddDynamic(this, &ADragon::OnAttackEnded);

        // 드래곤 사망 델리게이트 연결
        _dragonAnimInstance->_deathDelegate_Dragon.AddUObject(this, &ADragon::Disable);
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("Failed to initialize _dragonAnimInstance for ADragon!"));
    }
}

void ADragon::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

}
