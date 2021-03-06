// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Pawn.h"
#include "Tank.generated.h"
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnDeath);

UCLASS()
class BATTLETANK_API ATank : public APawn
{
	GENERATED_BODY()

public:
	virtual float TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;
	virtual void BeginPlay() override;
	// Return current health as a percentage of starting health between 0 and 1
	UFUNCTION(BlueprintPure, Category = "Health")
		float GetHealthPercent() const;

	FOnDeath OnDeath;
private:
	UPROPERTY(EditAnyWhere, Category = "Health")
		int32 StartingHelath = 100;
	UPROPERTY(VisibleAnywhere, Category = "Health")
		int32 CurrentHealth;
	// Sets default values for this pawn's properties
	ATank();
};
