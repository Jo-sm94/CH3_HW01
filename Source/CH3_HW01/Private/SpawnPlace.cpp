#include "SpawnPlace.h"
#include "Barrel.h"
#include "Wheel.h"

// Sets default values
ASpawnPlace::ASpawnPlace()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

    WheelSpawn = 3;
    BarrelSpawn = 10;

    Center = FVector(1340.0f, 920.0f, 0.0f);
    BarrelRange = FVector(1100.0f, 600.0f, 0.0f);
    WheelRange = FVector(500.0f, 550.0f, 0.0f);
}

void ASpawnPlace::BeginPlay()
{
	Super::BeginPlay();
	
    UWorld* World = GetWorld();
    if (!World) return;

    for (int32 i = 0; i < BarrelSpawn; i++)
    {
        float X = FMath::RandRange(Center.X - BarrelRange.X, Center.X + BarrelRange.X);
        float Y = FMath::RandRange(Center.Y - BarrelRange.Y, Center.Y + BarrelRange.Y);
        float Z = Center.Z;

        FVector SpawnLocation(X, Y, Z);
        FRotator SpawnRotation = FRotator::ZeroRotator;

        ABarrel* NewBarrel = World->SpawnActor<ABarrel>(
            ABarrel::StaticClass(),
            SpawnLocation,
            SpawnRotation
        );
    }

    for (int32 i = 0; i < WheelSpawn; i++)
    {
        float X = FMath::RandRange(Center.X - WheelRange.X, Center.X + WheelRange.X);
        float Y = FMath::RandRange(Center.Y - WheelRange.Y, Center.Y + WheelRange.Y);
        float Z = Center.Z;

        FVector SpawnLocation(X, Y, 70.0f);
        FRotator SpawnRotation = FRotator::ZeroRotator;

        AWheel* NewWheel = World->SpawnActor<AWheel>(
            AWheel::StaticClass(),
            SpawnLocation,
            SpawnRotation
        );
    }
}
