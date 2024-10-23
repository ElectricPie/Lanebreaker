// Fill out your copyright notice in the Description page of Project Settings.


#include "MInions/MinionController.h"

#include "Minion.h"
#include "Components/SphereComponent.h"
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

void AMinionController::BeginPlay()
{
	Super::BeginPlay();

	if (!HasAuthority())
		return;

	if (AMinion* Minion = Cast<AMinion>(GetPawn()))
	{
		Minion->GetAggroRadiusSphere()->OnComponentBeginOverlap.AddDynamic(this, &AMinionController::OnMinionAggroRadiusBegin);
		Minion->GetAggroRadiusSphere()->OnComponentEndOverlap.AddDynamic(this, &AMinionController::OnMinionAggroRadiusEnd);
	}
}

void AMinionController::OnMoveCompleted(FAIRequestID RequestID, const FPathFollowingResult& Result)
{
	Super::OnMoveCompleted(RequestID, Result);

	const float DistanceToTarget = (GetPawn()->GetActorLocation() - CurrentTarget->GetActorLocation()).Length();
	if (Result.IsSuccess() || DistanceToTarget < WaypointAcceptanceRadius)
	{
		MoveToNextWaypoint();
	}
	
}

void AMinionController::MoveToNextWaypoint()
{
	if (Waypoints.IsEmpty())
	{
		UE_LOG(LogTemp, Warning, TEXT("No Waypoints left"));
		CurrentTarget = nullptr;
		return;
	}

	AActor* Target;
	Waypoints.Dequeue(Target);
	CurrentTarget = Target;

	FAIMoveRequest MoveRequest;
	MoveRequest.SetGoalActor(Target);
	MoveRequest.SetAcceptanceRadius(WaypointAcceptanceRadius);
	
	MoveTo(MoveRequest);
}

void AMinionController::OnMinionAggroRadiusBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor == GetPawn())
		return;

	if (AMinion* Minion = Cast<AMinion>(OtherActor))
	{
		if (const AMinionController* MinionController = Cast<AMinionController>(Minion->GetController()))
		{
			// Check if on enemy team (Team 0 is no team so all are enemy)
			if (Team == 0 || MinionController->Team != Team)
			{
				EnemiesInRange.Add(Minion);
			}
		}
	}
}

void AMinionController::OnMinionAggroRadiusEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	EnemiesInRange.Remove(OtherActor);
}
