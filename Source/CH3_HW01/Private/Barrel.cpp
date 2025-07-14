#include "Barrel.h"
#include "Components/CapsuleComponent.h"

ABarrel::ABarrel()
{
	PrimaryActorTick.bCanEverTick = false;

	DelayTime = 3.0f;

	SceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("SceneRoot"));
	SetRootComponent(SceneRoot);

	StaticMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComp"));
	StaticMeshComp->SetupAttachment(SceneRoot);

	static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshAsset(TEXT("/Game/Nimikko_WesternTown/Assets/Furniture/SM_Barrel_01.SM_Barrel_01"));

	if (MeshAsset.Succeeded())
	{
		StaticMeshComp->SetStaticMesh(MeshAsset.Object);
	}

	CapsuleComp = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CapuleComp"));
	CapsuleComp->InitCapsuleSize(38.0f, 67.0f);
	CapsuleComp->SetRelativeLocation(FVector(0.0f, 0.0f, 48.0f));
	CapsuleComp->SetGenerateOverlapEvents(true);
	CapsuleComp->SetupAttachment(StaticMeshComp);
	
}

void ABarrel::BeginPlay()
{
	Super::BeginPlay();
	//SpawnLocation = FVector(1800.0f, 750.0f, 0.0f);
	SpawnLocation = GetActorLocation();
	SpawnRotator = GetActorRotation();
	SetActorLocation(SpawnLocation);
	SetActorScale3D(FVector(1.5f));
	CapsuleComp->OnComponentBeginOverlap.AddDynamic(this, &ABarrel::OnOverlap);

}


void ABarrel::OnOverlap(
	UPrimitiveComponent* OverlappedComp,
	AActor* OtherActor,
	UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex,
	bool bFromSweep,
	const FHitResult& SweepResult
)
{
	GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Green, FString::Printf(TEXT("Overlap!!!")));
	//GetWorld()->GetTimerManager().SetTimer(TimeHandle, this, &ABarrel::ReSpawn, DelayTime);

	UWorld* World = GetWorld();
	FVector loc = SpawnLocation;
	FRotator roc = SpawnRotator;
	World->GetTimerManager().SetTimer(TimeHandle, [World, loc, roc]()
		{
			if (World)
			{
				GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Green, FString::Printf(TEXT("ReSpawn!!!")));
				World->SpawnActor<ABarrel>(ABarrel::StaticClass(), loc, roc);
			}
		}, DelayTime, false);
	this->Destroy();
}

void ABarrel::ReSpawn()
{
	GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Green, FString::Printf(TEXT("ReSpawn!!!")));
	GetWorld()->SpawnActor<ABarrel>(ABarrel::StaticClass(), SpawnLocation, SpawnRotator);
}