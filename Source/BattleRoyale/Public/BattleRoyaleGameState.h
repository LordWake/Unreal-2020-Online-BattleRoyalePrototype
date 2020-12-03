//+-------------------------------------------------------+
//| Project   : BattleRoyaleExample						  				
//| Author    : github.com/LordWake					 	  		
//+-------------------------------------------------------+
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "BattleRoyaleGameState.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FWinnerFound);

UCLASS()
class BATTLEROYALE_API ABattleRoyaleGameState : public AGameStateBase
{
	GENERATED_BODY()

public:

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	UPROPERTY(ReplicatedUsing = OnRep_Winner, Transient, BlueprintReadOnly, Category = "Game State")
	class ABattleRoyalePlayerState* Winner = nullptr;

	UFUNCTION()
	void OnRep_Winner();

	UPROPERTY(BlueprintAssignable, Category = "Game State")
	FWinnerFound OnWinnerFound;
	
};
