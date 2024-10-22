// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "MinionController.generated.h"

/**
 * 
 */
UCLASS()
class AMinionController : public AAIController
{
	GENERATED_BODY()

public:
	/**
	 * @brief Assigns the waypoints to the minion to follow, will starting with first element
	 * @param NewWaypoints An array of actors to act as waypoints
	 */
	UFUNCTION(BlueprintCallable, Category="Minions")
	void SetWaypoints(const TArray<AActor*> NewWaypoints);

protected:
	virtual void OnMoveCompleted(FAIRequestID RequestID, const FPathFollowingResult& Result) override;

private:
	void MoveToNextWaypoint();
	
private:
	float WaypointAcceptanceRadius = 20.f;
	
	TQueue<AActor*> Waypoints;
	TWeakObjectPtr<AActor> CurrentTarget;
};