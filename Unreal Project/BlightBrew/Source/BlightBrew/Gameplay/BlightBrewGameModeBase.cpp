// Copyright Epic Games, Inc. All Rights Reserved.


#include "BlightBrewGameModeBase.h"

#include "BlightBrew/Characters/CharacterComponents/BBStaminaComponent.h"
#include "BlightBrew/Characters/Player/BBPlayerCharacter.h"
#include "GameFramework/PlayerStart.h"
#include "GameFramework/WorldSettings.h"
#include "UObject/ConstructorHelpers.h"
#include "Kismet/GameplayStatics.h"
#include "BlightBrew/Gameplay/World/BBRespawnPoint.h"

ABlightBrewGameModeBase::ABlightBrewGameModeBase()
{
	//TODO: GET THIS WORKING
	//static ConstructorHelpers::FClassFinder<ABBPlayerCharacter> PlayerPawnClassFinder(TEXT("BP_PlayerCharacter'/Content/Blueprints/Characters/Player/BP_PlayerCharacter.BP_PlayerCharacter_C'"));
	//if(PlayerPawnClassFinder.Succeeded())
	//{
	//	DefaultPawnClass = PlayerPawnClassFinder.Class;
	//}
	//else
	//{
	//	DefaultPawnClass = ABBPlayerCharacter::StaticClass();
	//}
}

void ABlightBrewGameModeBase::Debug(FString Command)
{
	TArray<AActor*> FoundActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ABBPlayerCharacter::StaticClass(), FoundActors);

	if (ABBPlayerCharacter* player = Cast< ABBPlayerCharacter>(FoundActors[0]))
	{
		if (Command == "Player.AddCurrency")
		{
			player->SetCurrency(player->GetCurrency() + 100);
		}

		if (Command == "Player.ModifyStamina")
		{
			player->GetStaminaComponent()->ModifyMaxStamina(250.0f, 10.0f);
		}

		if (Command == "PlayTest")
		{
			player->GetStaminaComponent()->ModifyMaxStamina(90000000.0f, 3600.0f);
		}
	}

}

void ABlightBrewGameModeBase::DilateTime(float amount)
{
	if (amount > 0)
	{
		GetWorldSettings()->SetTimeDilation(amount);
	}
}

void ABlightBrewGameModeBase::Unstuck()
{
	TArray<AActor*> FoundActors;
	TArray<AActor*> FoundActors2;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ABBPlayerCharacter::StaticClass(), FoundActors);
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ABBRespawnPoint::StaticClass(), FoundActors2);
	if (!FoundActors2.IsEmpty())
	{
		//Find the closest respawn point
		ABBRespawnPoint* closest = Cast<ABBRespawnPoint>(FoundActors2[0]);
		for (AActor* actor : FoundActors2)
		{
			if (ABBRespawnPoint* point = Cast<ABBRespawnPoint>(actor))
			{
				if (FVector::DistSquared(point->GetActorLocation(), FoundActors[0]->GetActorLocation()) < FVector::DistSquared(closest->GetActorLocation(), FoundActors[0]->GetActorLocation()))
				{
					closest = point;
				}
			}
		}
		if (ABBPlayerCharacter* player = Cast< ABBPlayerCharacter>(FoundActors[0]))
		{
			player->SetActorLocation(closest->GetActorLocation());
			return;
		}
	}

	UGameplayStatics::GetAllActorsOfClass(GetWorld(), APlayerStart::StaticClass(), FoundActors2);
	if (ABBPlayerCharacter* player = Cast< ABBPlayerCharacter>(FoundActors[0]))
	{
		if (APlayerStart* start = Cast< APlayerStart>(FoundActors2[0]))
		{
			player->SetActorLocation(start->GetActorLocation());
		}
	}
}
