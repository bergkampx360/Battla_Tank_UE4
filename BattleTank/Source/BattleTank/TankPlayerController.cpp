// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
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
	UE_LOG(LogTemp, Warning, TEXT("PlayerController possesing %s"), *ControlledTank->GetName());

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
		UE_LOG(LogTemp, Warning, TEXT("Look direction: %s"), *HitLocation.ToString());
		//TODO: Tell controller tank to aim at this point
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
	// Line-trace along that look direction, and see what we hit (up to max range)
	
	return false;
}

#pragma endregion
