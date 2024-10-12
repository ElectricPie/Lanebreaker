// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/TopDownPlayerController.h"

#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "PlayerPawn.h"

void ATopDownPlayerController::BeginPlay()
{
	Super::BeginPlay();

	if (UEnhancedInputLocalPlayerSubsystem* InputSubsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		InputSubsystem->AddMappingContext(MappingContext, 0);
	}
}

void ATopDownPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent))
	{
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ATopDownPlayerController::Move);

		EnhancedInputComponent->BindAction(ModifierOneAction, ETriggerEvent::Started, this, &ATopDownPlayerController::SetModifierOneActive, true);
		EnhancedInputComponent->BindAction(ModifierOneAction, ETriggerEvent::Canceled, this, &ATopDownPlayerController::SetModifierOneActive, false);
		EnhancedInputComponent->BindAction(ModifierOneAction, ETriggerEvent::Completed, this, &ATopDownPlayerController::SetModifierOneActive, false);
	}
}

void ATopDownPlayerController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	PlayerPawn = Cast<APlayerPawn>(InPawn);
}

void ATopDownPlayerController::Move(const FInputActionValue& Value)
{
	const FVector2D MoveDirection = Value.Get<FVector2D>().GetSafeNormal();

	if (PlayerPawn)
	{
		float MoveSpeed = 1.f;
		if (ModifierOneActive)
		{
			MoveSpeed = IncreasedMoveSpeedModifier;
		}
		
		PlayerPawn->Move(MoveDirection, MoveSpeed);
	}
}