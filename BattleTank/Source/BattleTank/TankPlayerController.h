// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/PlayerController.h"
#include "Tank.h"
#include "TankPlayerController.generated.h"

/**
 *
 */
UCLASS()
class BATTLETANK_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()
public:

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	ATank* GetControlledTank() const;
	//Start the tank moving the barrel so that a shot would it where the cross hair intersects the world
	void AimTowardsCrosshair();
	UFUNCTION(BlueprintCallable, Category="SunShine")
	void SetCrossHairLocation(float X, float Y);
private:
	//Return an OUT parameter, true if hit landscape
	bool GetSightRayHitLocation(FVector& HitLocation) const;
	float CrossHairXLocation = 0.5f;
	float CrossHairYLocation = 0.3333f;

};
