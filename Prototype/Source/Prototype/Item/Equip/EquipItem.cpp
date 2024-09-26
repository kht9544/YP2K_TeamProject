#include "Item/Equip/EquipItem.h"
#include "../../Player/MyPlayer.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/SphereComponent.h"

// Sets default values
AEquipItem::AEquipItem()
{
    PrimaryActorTick.bCanEverTick = true;
    _skeletalComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Skeletal"));
    _skeletalComponent->SetCollisionProfileName(TEXT("NoCollision"));
    _skeletalComponent->SetupAttachment(_meshComponent);

    //_trigger = CreateDefaultSubobject<USphereComponent>(TEXT("OverlapSphere"));

    _trigger->SetSphereRadius(100.0f);
    _trigger->SetCollisionProfileName(TEXT("OverlapAllDynamic"));
}

// Called when the game starts or when spawned
void AEquipItem::BeginPlay()
{
    Super::BeginPlay();
    _trigger->OnComponentBeginOverlap.AddDynamic(this, &AEquipItem::OnOverlapBegin);
}

// Called every frame
void AEquipItem::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

void AEquipItem::OnOverlapBegin(UPrimitiveComponent *OverlappedComp, AActor *OtherActor, UPrimitiveComponent *OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult &SweepResult)
{
    auto Player = Cast<AMyPlayer>(OtherActor);
    if (Player)
    {
        UE_LOG(LogTemp, Warning, TEXT("%s"), *AttachSocketName.ToString());
        //_meshComponent->SetSimulatePhysics(false);
        AttachToComponent(Player->GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, AttachSocketName);
        SetOwner(Player);

        SetActorEnableCollision(false);
    }
}
