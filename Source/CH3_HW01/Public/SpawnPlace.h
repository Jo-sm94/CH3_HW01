﻿// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SpawnPlace.generated.h"

UCLASS()
class CH3_HW01_API ASpawnPlace : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASpawnPlace();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Init")
	int32 WheelSpawn;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Init")
	int32 BarrelSpawn;

	FVector Center;
	FVector BarrelRange;
	FVector WheelRange;
};
