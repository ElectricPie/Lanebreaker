// Fill out your copyright notice in the Description page of Project Settings.


#include "Minions/Minion.h"

#if WITH_EDITORONLY_DATA
#include "Components/ArrowComponent.h"
#endif // WITH_EDITORONLY_DATA
#include "Components/CapsuleComponent.h"

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

	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh Component"));
	if (MeshComponent)
	{
		MeshComponent->AlwaysLoadOnClient = true;
		MeshComponent->AlwaysLoadOnServer = true;
	}
}
