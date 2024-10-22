// Fill out your copyright notice in the Description page of Project Settings.


#include "Minions/Minion.h"

#if WITH_EDITORONLY_DATA
#include "Components/ArrowComponent.h"
#endif // WITH_EDITORONLY_DATA
#include "Components/CapsuleComponent.h"
#include "GameFramework/FloatingPawnMovement.h"

// Sets default values
AMinion::AMinion()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CapsuleComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule Component"));
	CapsuleComponent->InitCapsuleSize(34.0f, 88.0f);
	CapsuleComponent->SetCollisionProfileName(UCollisionProfile::Pawn_ProfileName);
	RootComponent = CapsuleComponent;

#if WITH_EDITORONLY_DATA
	ArrowComponent = CreateEditorOnlyDefaultSubobject<UArrowComponent>(TEXT("Arrow"));
	if (ArrowComponent)
	{
		ArrowComponent->ArrowColor = FColor(150, 200, 255);
		ArrowComponent->bTreatAsASprite = true;
		ArrowComponent->bIsScreenSizeScaled = true;
		ArrowComponent->SetSimulatePhysics(false);
		ArrowComponent->SetupAttachment(CapsuleComponent);
	}
#endif // WITH_EDITORONLY_DATA

	MeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh Component"));
	if (MeshComponent)
	{
		MeshComponent->AlwaysLoadOnClient = true;
		MeshComponent->AlwaysLoadOnServer = true;
		MeshComponent->SetupAttachment(CapsuleComponent);
	}

	FloatingPawnMovementComponent = CreateDefaultSubobject<UFloatingPawnMovement>(TEXT("Floating Pawn Movement"));
	FloatingPawnMovementComponent->MaxSpeed = 400.f;
	
	bCanAffectNavigationGeneration = true;
}

void AMinion::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	RotateToMovement();
	KeepGrounded();

	FRotator NewRotation = GetActorRotation();
	NewRotation.Pitch = 0.f;
	NewRotation.Roll = 0.f;
	SetActorRotation(NewRotation);
}

void AMinion::RotateToMovement()
{
	if (!FloatingPawnMovementComponent)
		return;

	const FVector Velocity = FloatingPawnMovementComponent->Velocity;
	if (Velocity.IsNearlyZero())
		return;

	const FRotator CurrentRotation = GetActorRotation();
	const FRotator TargetRotation = Velocity.Rotation();
	const FRotator NewRotation = FMath::RInterpTo(CurrentRotation, TargetRotation, GetWorld()->GetDeltaSeconds(), 5.f);
	SetActorRotation(NewRotation);
}

void AMinion::KeepGrounded()
{
	const FVector Start = GetActorLocation();
	const FVector End = Start - FVector(0.0f, 0.0f, 1000.0f); 

	FHitResult HitResult;
	FCollisionQueryParams CollisionParams;
	CollisionParams.AddIgnoredActor(this);

	if (GetWorld()->LineTraceSingleByChannel(HitResult, Start, End, ECC_Visibility, CollisionParams))
	{
		// Move the pawn's Z position to match the ground
		FVector NewLocation = GetActorLocation();
		NewLocation.Z = HitResult.Location.Z + CapsuleComponent->GetScaledCapsuleHalfHeight();
		SetActorLocation(NewLocation);
	}
}

