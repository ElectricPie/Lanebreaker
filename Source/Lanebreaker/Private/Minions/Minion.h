// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "AbilitySystemInterface.h"
#include "Minion.generated.h"


class UStandardAttributeSet;
class UAbilitySystemComponent;
class UArrowComponent;
class UCapsuleComponent;
class UFloatingPawnMovement;
class USkeletalMeshComponent;
class USphereComponent;

UCLASS()
class AMinion : public APawn, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AMinion();
	virtual void Tick(float DeltaSeconds) override;

	USphereComponent* GetAggroRadiusSphere() { return AggroRadiusSphere; }

	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override { return AbilitySystemComponent; };
	UFUNCTION(BlueprintPure, Category="GAS")
	const UStandardAttributeSet* GetStandardAttributeSet();
	
protected:
	virtual void BeginPlay() override;
	
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
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USphereComponent> AggroRadiusSphere;
	
	UPROPERTY(EditAnywhere, Category="GAS")
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;
	UPROPERTY(EditAnywhere, Category="GAS")
	TObjectPtr<const UStandardAttributeSet> StandardAttributeSet;
};
