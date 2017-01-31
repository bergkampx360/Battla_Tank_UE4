// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include "TankAimingComponent.generated.h"

class UTankBarrel; // Forward Declaration
class UTankTurret;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnChangingAimingSolution, bool, HasAimingSolution);

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class BATTLETANK_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UTankAimingComponent();
	UFUNCTION(BlueprintCallable, Category = "Aiming")
		bool GetbHasAimingSolution() const;

	UPROPERTY(BlueprintAssignable, Category = "Aiming")
		FOnChangingAimingSolution OnChangingAimingResult;

	void SetBarrelReference(UTankBarrel* BarrelToSet);
	void SetTurretReference(UTankTurret* TurretToSet);
	void AimAt(FVector HitLocation, float LaunchSpeed);
private:
	UTankBarrel* Barrel = nullptr;
	UTankTurret* Turret = nullptr;
	bool bHasAimingSolution = false;
	void MoveBarrelTowards(FVector AimDirection);
	void MoveTurretTowards(FVector AimDirection);
};
