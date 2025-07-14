#include "Wheel.h"
#include "Components/BoxComponent.h"

AWheel::AWheel()
{

	PrimaryActorTick.bCanEverTick = true;

	MoveSpeed = FMath::RandRange(500, 1000);
	RotationSpeed = MoveSpeed / 5;
	
	//RotationSpeed = 120.0f;
	//MoveSpeed = 500.0f;
	
	MaxRange = FVector(1000.0f, 0.0f, 0.0f);
	Forward = true;

	SceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("SceneRoot"));
	SetRootComponent(SceneRoot);

	StaticMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComp"));
	StaticMeshComp->SetupAttachment(SceneRoot);

	static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshAsset(TEXT("/Game/Nimikko_WesternTown/Assets/Props/SM_WagonWheel_01.SM_WagonWheel_01"));

	if (MeshAsset.Succeeded())
	{
		StaticMeshComp->SetStaticMesh(MeshAsset.Object);
	}
}

void AWheel::BeginPlay()
{
	Super::BeginPlay();

	OriginLocation = GetActorLocation();
	SetActorLocation(OriginLocation);
}

void AWheel::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!FMath::IsNearlyZero(RotationSpeed))
	{
		if (Forward)
		{
			AddActorLocalRotation(FRotator(-RotationSpeed * DeltaTime, 0.0f, 0.0f));
		}
		else
		{
			AddActorLocalRotation(FRotator(RotationSpeed * DeltaTime, 0.0f, 0.0f));
		}

	}

	FVector CurrentLocation = GetActorLocation();
	FVector TargetLocation = OriginLocation + (Forward ? MaxRange : -MaxRange);
	FVector Direction = (TargetLocation - CurrentLocation).GetSafeNormal();
	FVector NewLocation = CurrentLocation + (Direction * MoveSpeed * DeltaTime);
	SetActorLocation(NewLocation, true);

	if (FVector::Dist(CurrentLocation, TargetLocation) < 10.f)
	{
		Forward = !Forward;
	}
}
