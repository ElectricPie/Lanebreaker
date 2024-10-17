// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Minion.generated.h"


class UArrowComponent;
class UCapsuleComponent;
class UStaticMeshComponent;

UCLASS()
class AMinion : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AMinion();

private:
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UCapsuleComponent> CapsuleComponent;

#if WITH_EDITORONLY_DATA
	/** Component shown in the editor only to indicate character facing */
	UPROPERTY()
	TObjectPtr<UArrowComponent> ArrowComponent;
#endif
	
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UStaticMeshComponent> MeshComponent;
};
