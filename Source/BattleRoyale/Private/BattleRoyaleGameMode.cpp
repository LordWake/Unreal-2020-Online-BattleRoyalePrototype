// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "BattleRoyaleGameMode.h"
#include "BattleRoyaleHUD.h"
#include "BattleRoyaleCharacter.h"
#include "UObject/ConstructorHelpers.h"
#include "BattleRoyalePlayerController.h"
#include "BattleRoyalePlayerState.h"
#include "BattleRoyaleGameState.h"


ABattleRoyaleGameMode::ABattleRoyaleGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPersonCPP/Blueprints/FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	// use our custom HUD class
	HUDClass = ABattleRoyaleHUD::StaticClass();
}

void ABattleRoyaleGameMode::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);

	AlivePlayers.Add(Cast<ABattleRoyalePlayerController>(NewPlayer));

	FString playerName = "Player " + FString::FromInt(AlivePlayers.Num());

	NewPlayer->GetCharacter()->GetPlayerState()->SetPlayerName(playerName);
}

void ABattleRoyaleGameMode::PlayerDied(ABattleRoyaleCharacter* Killed, ABattleRoyaleCharacter* Killer)
{
	if (Killed)
	{
		if (ABattleRoyalePlayerController* PC = Cast<ABattleRoyalePlayerController>(Killed->GetController()))
			AlivePlayers.RemoveSingle(PC);

		if (AlivePlayers.Num() == 1 && AlivePlayers.IsValidIndex(0))
			WinnerFound(Cast<ABattleRoyalePlayerState>(AlivePlayers[0]->PlayerState));
	}
}

void ABattleRoyaleGameMode::WinnerFound(ABattleRoyalePlayerState* Winner)
{
	if (ABattleRoyaleGameState* MyGameState = GetGameState<ABattleRoyaleGameState>())
		MyGameState->Winner = Winner;
}
