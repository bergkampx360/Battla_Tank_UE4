// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "Tank.h"
#include "TankAimingComponent.h"
#include "TankPlayerController.h"

#pragma region UE 4 functions

//Called when the game starts
void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();
	auto ControlledTank = GetControlledTank();
	if (!ControlledTank) {
		UE_LOG(LogTemp, Error, TEXT("PlayerController not possesing a tank"));
		return;
	}
	auto AimingComponent = ControlledTank->FindComponentByClass<UTankAimingComponent>();
	if (AimingComponent) {
		FoundAimingComponent(AimingComponent);
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("PLayer controller cant find aiming component at BeginPlay!"));
	}
}

//Called every frame
void ATankPlayerController::Tick(float DeltaTime)
{
	// Super
	Super::Tick(DeltaTime);
	AimTowardsCrosshair();

}

#pragma endregion

#pragma region ATankPlayerController functions

ATank* ATankPlayerController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

void ATankPlayerController::AimTowardsCrosshair()
{
	if (!GetControlledTank()) return;
	FVector HitLocation;	//Out parameter
	if (GetSightRayHitLocation(HitLocation)) //Has a side-effect is going to line trace
	{
		//Tell controlled tank to aim at this point
		GetControlledTank()->AimAt(HitLocation);
	}
}

void ATankPlayerController::SetCrossHairLocation(float X, float Y)
{
	CrossHairXLocation = X;
	CrossHairYLocation = Y;
	UE_LOG(LogTemp, Warning, TEXT("SetCrossHairLocation called. NewX: %f, NewY: %f"), X, Y);
}


//Get world location if line trace through cross hair
bool ATankPlayerController::GetSightRayHitLocation(FVector& HitLocation) const
{
	//Find the cross hair position in pixel coordinates
	int32 ViewportSizeX, ViewportSizeY;
	GetViewportSize(ViewportSizeX, ViewportSizeY);
	FVector2D ScreenLocation = FVector2D(ViewportSizeX * CrossHairXLocation, ViewportSizeY * CrossHairYLocation);
	// "De-project" the screen position of the crass hair to a world direction
	FVector LookDirection;
	if (GetLookDirection(ScreenLocation, LookDirection))
	{
		// Line-trace along the look direction, and see what we hit (up to max range)
		return GetLookVectorHitLocation(LookDirection, HitLocation);
	}
	return false;
}

bool ATankPlayerController::GetLookDirection(FVector2D ScreenLocation, FVector& LookDirection) const
{
	FVector CameraWorldLocation;
	return DeprojectScreenPositionToWorld(ScreenLocation.X, ScreenLocation.Y, CameraWorldLocation, LookDirection);
}

bool ATankPlayerController::GetLookVectorHitLocation(FVector LookDirection, FVector& HitLocation) const
{
	FHitResult HitResult;
	auto StartLocation = PlayerCameraManager->GetCameraLocation();
	auto EndLocation = StartLocation + (LookDirection * LineTraceRange);
	//If line trace succeeds
	if (GetWorld()->LineTraceSingleByChannel(HitResult, StartLocation, EndLocation, ECollisionChannel::ECC_Visibility)) {
		// Set hit location
		HitLocation = HitResult.Location;
		return true;
	}
	HitLocation = FVector::ZeroVector;
	return false;
}

#pragma endregion
