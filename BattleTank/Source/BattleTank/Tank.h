// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Pawn.h"
#include "Tank.generated.h"
class UTankBarrel;
class UTankTurret;
class UTankAimingComponent;
UCLASS()
class BATTLETANK_API ATank : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ATank();

	void AimAt(FVector HitLocation);

	UFUNCTION(BlueprintCallable, Category = "Setup")
		void SetBarrelReference(UTankBarrel* BarrelToSet);
	UFUNCTION(BlueprintCallable, Category = "Setup")
		void SetTurretReference(UTankTurret* TurretToSet);
	UFUNCTION(BlueprintCallable, Category = "Aiming")
	UTankAimingComponent* GetTankAimingComponent() const;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComp) override;

protected:
	UTankAimingComponent* TankAimingComponent = nullptr;
	UPROPERTY(EditAnywhere, Category = "Firing")
		float LaunchSpeed = 4000;

	UFUNCTION(BlueprintCallable, Category="Firing")
	void Fire();
};
