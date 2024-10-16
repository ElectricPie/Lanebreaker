// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/LanebreakerPlayerState.h"

#include "Net/UnrealNetwork.h"

void ALanebreakerPlayerState::OnServerSetMoney(const int32 NewMoneyAmount)
{
	if (HasAuthority())
	{
		Money = NewMoneyAmount;
	}
}

void ALanebreakerPlayerState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	
	DOREPLIFETIME_CONDITION(ALanebreakerPlayerState, Money, COND_OwnerOnly);
}
