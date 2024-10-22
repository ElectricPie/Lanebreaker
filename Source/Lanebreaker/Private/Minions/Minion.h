// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Minion.generated.h"


class UFloatingPawnMovement;
class UArrowComponent;
class UCapsuleComponent;
class USkeletalMeshComponent;

UCLASS()
class AMinion : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AMinion();
	virtual void Tick(float DeltaSeconds) override;

private:
	void RotateToMovement();
	void KeepGrounded();
	
private:
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UCapsuleComponent> CapsuleComponent;
#if WITH_EDITORONLY_DATA
	/** Component shown in the editor only to indicate character facing */
	TObjectPtr<UArrowComponent> ArrowComponent;
#endif
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USkeletalMeshComponent> MeshComponent;
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UFloatingPawnMovement> FloatingPawnMovementComponent;
};
