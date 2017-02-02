// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankTrack.h"
#include "TankMovementComponent.h"

void UTankMovementComponent::Initialize(UTankTrack* LeftTrackToSet, UTankTrack* RightTrackToSet)
{
	if (!LeftTrackToSet || !RightTrackToSet) return;
	this->LeftTrack = LeftTrackToSet;
	this->RightTrack = RightTrackToSet;
}

void UTankMovementComponent::IntendMoveForward(float Throw)
{
	if (!this->LeftTrack || !this->RightTrack) return;
	UE_LOG(LogTemp, Warning, TEXT("IntendMoveForward %f"), Throw);

	this->LeftTrack->SetThrottile(Throw);
	this->RightTrack->SetThrottile(Throw);
}
