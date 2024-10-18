// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TopDownPlayerController.generated.h"

class APlayerPawn;
class UInputMappingContext;
class UInputAction;

struct FInputActionValue;

/**
 * 
 */
UCLASS()
class ATopDownPlayerController : public APlayerController
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;

private:
	void Move(const FInputActionValue& Value);
	void SetModifierOneActive(bool bNewIsActive) { ModifierOneActive = bNewIsActive; }

private:
	UPROPERTY(EditAnywhere, Category="Input")
	TObjectPtr<UInputMappingContext> MappingContext;
	UPROPERTY(EditAnywhere, Category="Input")
	TObjectPtr<UInputAction> MoveAction;
	UPROPERTY(EditAnywhere, Category="Input")
	TObjectPtr<UInputAction> ModifierOneAction;
	UPROPERTY(EditAnywhere, Category="Movement")
	float IncreasedMoveSpeedModifier = 2.f;

	bool ModifierOneActive;
};

