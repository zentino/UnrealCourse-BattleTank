// Fill out your copyright notice in the Description page of Project Settings.

#include "Kismet/GameplayStatics.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/Actor.h"
#include "TankAimingComponent.h"


// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

void UTankAimingComponent::AimAt(FVector HitLocation, float LaunchSpeed)
{
	if (!Barrel) { return; }

	FVector OutLaunchVelocity; // default initialized by 0
	FVector StartLocation = Barrel->GetSocketLocation(FName("Projectile")); // If it can't find the socket location, it returns the Barrel location

	// Calculate the OutLaunchVelocity
	bool GotSuggested = UGameplayStatics::SuggestProjectileVelocity(
		this,
		OutLaunchVelocity,
		StartLocation,
		HitLocation,
		LaunchSpeed,
		ESuggestProjVelocityTraceOption::OnlyTraceWhileAscending
	);

	if (GotSuggested)
	{
		auto AimDirection = OutLaunchVelocity.GetSafeNormal(); // LaunchVelocity -----> =>  LaunchDirection ->
		MoveBarrelTowards(AimDirection);
	}
	// If no solution found do nothing
}

void UTankAimingComponent::MoveBarrelTowards(FVector AimDirection)
{
	// Work-out differences between current barrel rotation, and AimDirection
	auto BarrelRotator = Barrel->GetForwardVector().Rotation();
	auto AimAsRotator = AimDirection.Rotation();
	auto DeltaRotator = AimAsRotator - BarrelRotator;
	UE_LOG(LogTemp, Warning, TEXT("DeltaRotator: %s"), *DeltaRotator.ToString());

	// Move the barrel the right amound this frame

	// Given a max elevation speed, and the frame time
}

void UTankAimingComponent::SetBarrelReference(UStaticMeshComponent * BarrelToSet)
{
	Barrel = BarrelToSet;
}



