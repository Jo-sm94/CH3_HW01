#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Barrel.generated.h"


class UCapsuleComponent;

UCLASS()
class CH3_HW01_API ABarrel : public AActor
{
	GENERATED_BODY()
	
public:	

	ABarrel();

protected:
	virtual void BeginPlay() override;
	UFUNCTION()
	virtual void OnOverlap(
		UPrimitiveComponent* OverlappedComp, // 오버랩한 자기자신 (스피어 컴포넌트)
		AActor* OtherActor, // 부딫친 상대방의 액터
		UPrimitiveComponent* OtherComp, //OtherActor에 붙어있던 컴포넌트 (캡슐컴포넌트)
		int32 OtherBodyIndex,
		bool bFromSweep,
		const FHitResult& SweepResult
	);
	UFUNCTION()
	virtual void ReSpawn();


	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Option|Component")
	USceneComponent* SceneRoot;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Option|Component")
	UStaticMeshComponent* StaticMeshComp;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Option|Component")
	UCapsuleComponent* CapsuleComp;

	FTimerHandle TimeHandle;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Timer")
	float DelayTime;
	FVector SpawnLocation;
	FRotator SpawnRotator;
};
