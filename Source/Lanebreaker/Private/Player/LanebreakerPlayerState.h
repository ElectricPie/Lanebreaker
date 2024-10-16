// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "LanebreakerPlayerState.generated.h"

/**
 * 
 */
UCLASS()
class ALanebreakerPlayerState : public APlayerState
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintPure)
	int32 GetMoney() const { return Money; }
	UFUNCTION(BlueprintCallable)
	void OnServerSetMoney(const int32 NewMoneyAmount);

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty> & OutLifetimeProps) const override;

private:
	UPROPERTY(VisibleAnywhere, Replicated)
	int32 Money = 0.f;
};
