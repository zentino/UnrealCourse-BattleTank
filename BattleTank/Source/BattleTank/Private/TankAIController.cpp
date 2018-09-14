// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();

	ATank* AIControlledTank = GetAIControlledTank();
	if (AIControlledTank) 
	{
		UE_LOG(LogTemp, Warning, TEXT("AIController possessing: %s"), *(AIControlledTank->GetName()))
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("AIController not possessing a Tank"))
	}

}

ATank * ATankAIController::GetAIControlledTank() const
{
	return Cast<ATank>(GetPawn());
}
