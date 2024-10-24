// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttributeHelpers.h"
#include "AbilitySystemComponent.h"
#include "StandardAttributeSet.generated.h"

/**
 * 
 */
UCLASS()
class UStandardAttributeSet : public UAttributeSet
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadOnly, Category="Health")//, ReplicatedUsing=OnRep_Health)
	FGameplayAttributeData Health;
	ATTRIBUTE_ACCESSORS(UStandardAttributeSet, Health);

	UPROPERTY(BlueprintReadOnly, Category="Health")//, ReplicatedUsing=OnRep_Health)
	FGameplayAttributeData MaxHealth;
	ATTRIBUTE_ACCESSORS(UStandardAttributeSet, MaxHealth);

};
