//+-------------------------------------------------------+
//| Project   : BattleRoyaleExample						  				
//| Author    : github.com/LordWake					 	  		
//+-------------------------------------------------------+


#include "BattleRoyaleGameState.h"
#include "Net/UnrealNetwork.h"

void ABattleRoyaleGameState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(ABattleRoyaleGameState, Winner);
}

void ABattleRoyaleGameState::OnRep_Winner()
{
	OnWinnerFound.Broadcast();
}
