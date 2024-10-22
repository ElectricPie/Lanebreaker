// Fill out your copyright notice in the Description page of Project Settings.


#include "MInions/MinionController.h"

#include "Navigation/PathFollowingComponent.h"

void AMinionController::SetWaypoints(const TArray<AActor*> NewWaypoints)
{
	if (!HasAuthority())
		return;

	if (NewWaypoints.Num() == 0)
		return;

	Waypoints.Empty();

	for (const auto& Waypoint : NewWaypoints)
	{
		Waypoints.Enqueue(Waypoint);
	}

	MoveToNextWaypoint();
}

void AMinionController::OnMoveCompleted(FAIRequestID RequestID, const FPathFollowingResult& Result)
{
	Super::OnMoveCompleted(RequestID, Result);

	if (Result.IsSuccess())
	{
		MoveToNextWaypoint();
	}
}

void AMinionController::MoveToNextWaypoint()
{
	if (Waypoints.IsEmpty())
	{
		UE_LOG(LogTemp, Warning, TEXT("No Waypoints left"));
		return;
	}
	
	AActor* Target;
	Waypoints.Dequeue(Target);

	FAIMoveRequest MoveRequest;
	MoveRequest.SetGoalActor(Target);
	
	MoveTo(MoveRequest);
}
