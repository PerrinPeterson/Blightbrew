// Copyright © Too Many Eyes , 2022 - 2023
#include "BBRewardsChest.h"

//Unreal
#include "../../../../../Engine/Plugins/FX/Niagara/Source/Niagara/Public/NiagaraComponent.h"
#include "../Engine/Classes/Kismet/GameplayStatics.h"
#include "../Engine/Classes/Components/StaticMeshComponent.h"
#include "../Engine/Classes/GameFramework/ProjectileMovementComponent.h"
//Blightbrew
#include "BlightBrew/Characters/Player/BBPlayerCharacter.h"
#include "BlightBrew/Shop/BBEconomyManager.h"
#include "BlightBrew/Shop/BBShopManager.h"
#include "BlightBrew/Inventory/BBInventoryComponent.h"
#include "BlightBrew/Crafting/BBCraftingStation.h"
#include "BBRockTriggerSpot.h"

// Sets default values
ABBRewardsChest::ABBRewardsChest()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ChestMesh"));
	RootComponent = Mesh;

	ParticleEffect = CreateDefaultSubobject<UNiagaraComponent>(TEXT("ParticleEffect"));
	ParticleEffect->SetupAttachment(RootComponent);
	RevieledParticleEffect = CreateDefaultSubobject<UNiagaraComponent>(TEXT("RevieledParticleEffect"));
	RevieledParticleEffect->SetupAttachment(RootComponent);
	
	
}

// Called when the game starts or when spawned
void ABBRewardsChest::BeginPlay()
{
	Super::BeginPlay();

	//If the array of rock spots is empty, the chest is interactable
	if (PuzzleSpots.Num() == 0)
	{	
		Mesh->SetHiddenInGame(false);
		Mesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
		bIsInteractable = true;
	}
	else
	{
		Mesh->SetHiddenInGame(true);
		Mesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		bIsInteractable = false;
	}

	if (ParticleEffect && !bIsInteractable)
		ParticleEffect->Deactivate();

	if(RevieledParticleEffect)
		RevieledParticleEffect->Deactivate();

	m_focusText = FText::FromString("Press E to open");

}

// Called every frame
void ABBRewardsChest::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (PuzzleSpots.Num() == 0)
		return;
	if (bIsInteractable)
		return;
	if (bHasBeenLooted)
		return;

	//Check the plates to see if they're activated
	int activatedPlates = 0;
	for (TSoftObjectPtr<ABBRockTriggerSpot> plate : PuzzleSpots)
	{
		if (plate)
		{
			if (plate->IsTriggered())
				activatedPlates++;
		}
	}
	if (activatedPlates == PuzzleSpots.Num())
	{
		bIsInteractable = true;
		Mesh->SetHiddenInGame(false);
		Mesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
		if (ParticleEffect)
		{
			ParticleEffect->Activate();
		}
		//We'll fire a burst of the Revieled Particle effect
		if (RevieledParticleEffect)
		{
			RevieledParticleEffect->Activate();
			//Set a timer to deactivate the particle effect
			FTimerHandle timerHandle;
			GetWorld()->GetTimerManager().SetTimer(timerHandle, this, &ABBRewardsChest::DeactivateBurst, 0.5f, false);
		}
		//Play the sound
		if (RevieledSound)
		{
			UGameplayStatics::PlaySoundAtLocation(GetWorld(), RevieledSound, GetActorLocation());
		}
	}
}

void ABBRewardsChest::OnFocus(AActor* InstigatingActor)
{

}

void ABBRewardsChest::OnInteract(AActor* InstigatingActor)
{
	//Cast the instigating actor to a player character
	ABBPlayerCharacter* player = Cast<ABBPlayerCharacter>(InstigatingActor);
	if (player == nullptr)
		return;
	if (!bIsInteractable)
		return;

	//If we're randomizing the items
	if (bAddRandomItem)
	{
		if (MinRandomItems > MaxRandomItems)
			MinRandomItems = MaxRandomItems;
		int32 randomItemNum = FMath::RandRange(MinRandomItems, MaxRandomItems);
		//Grab the shop manager actor from the world, it has an econ manager we can use to get the items in the world
		ABBShopManager* shopManager = Cast<ABBShopManager>(UGameplayStatics::GetActorOfClass(GetWorld(), ABBShopManager::StaticClass()));
		if (shopManager)
		{
			//Get the econ manager from the shop manager
			UBBEconomyManager* econManager = shopManager->GetEconomyManager();
			if (econManager)
			{
				//Get the random Items
				TArray<ABBBaseItem*> randomItems;
				econManager->GetRandomItems(randomItemNum, randomItems);
				if (randomItems.Num() > 0)
				{
					//Add each of them to the players inventory
					for (int i = 0; i < randomItems.Num(); i++)
					{
						int64 num = 1;
						player->GetInventoryComponent()->AddToInventory(randomItems[i], num);
						if (num == 1)
						{
							//Set a timer to call ThrowLoot, this throws any excess loot up and into the air
							FTimerHandle timer;
							GetWorld()->GetTimerManager().SetTimer(timer, this, &ABBRewardsChest::ThrowLoot, LootThrowTime * m_throwQueNum + 0.1, false);
							m_throwQueNum++;
							m_lootToThrow.Add(randomItems[i]);
						}
					}
				}
			} // If EconManager
		} //If shopmanager
	}
	if (bAddRandomGold)
	{
		//Add the random gold to the players inventory
		int64 gold = FMath::RandRange(MinGold, MaxGold);
		player->SetCurrency(player->GetCurrency() + gold);
	}
	if (PredeterminedGoldToAdd > 0)
	{
		player->SetCurrency(player->GetCurrency() + PredeterminedGoldToAdd);
	}
	if (PredeterminedItemsToAdd.Num() > 0)
	{
		for (int i = 0; i < PredeterminedItemsToAdd.Num(); i++)
		{
			int64 num = 1;
			player->GetInventoryComponent()->AddToInventory(PredeterminedItemsToAdd[i].GetDefaultObject(), num);
			if (num == 1)
			{
				//Set a timer to call ThrowLoot, this throws any excess loot up and into the air
				FTimerHandle timer;
				GetWorld()->GetTimerManager().SetTimer(timer, this, &ABBRewardsChest::ThrowLoot, LootThrowTime * m_throwQueNum + 0.1, false);
				m_throwQueNum++;
				m_lootToThrow.Add(PredeterminedItemsToAdd[i].GetDefaultObject());
			}
		}
	}
	if (CraftedItemKnowledgeToAdd.Num() > 0)
	{
		//Grab all the Crafting Tables in the world
		TArray<AActor*> craftingTables;
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), ABBCraftingStation::StaticClass(), craftingTables);
		if (craftingTables.Num() > 0)
		{
			//Loop through all the crafting tables
			for (int i = 0; i < craftingTables.Num(); i++)
			{
				//Cast the actor to a crafting table
				ABBCraftingStation* craftingTable = Cast<ABBCraftingStation>(craftingTables[i]);
				if (craftingTable)
				{
					//Loop through all the items we want to add
					for (int j = 0; j < CraftedItemKnowledgeToAdd.Num(); j++)
					{
						//Loop through the recipies and find the one that matches the item we want to add
						for (auto& k : craftingTable->CraftingBook)
						{
							//If the recipie matches the item we want to add
							if (k.Key.OutputItem.GetDefaultObject() == CraftedItemKnowledgeToAdd[j].GetDefaultObject())
							{
								//Add the recipie to the players crafting knowledge
								k.Value = true;
							}
						}

					}
				}
			}
		}
	}
	ParticleEffect->Deactivate();
	bIsInteractable = false;
	bHasBeenLooted = true;
	//Play the loot sound
	UGameplayStatics::PlaySoundAtLocation(GetWorld(), InteractSound, GetActorLocation());
	m_focusText = FText::FromString("Looted");

}

void ABBRewardsChest::SetFocusText(FText text)
{
	m_focusText = text;
}

FText ABBRewardsChest::GetFocusText()
{
	return m_focusText;
}

void ABBRewardsChest::ThrowLoot()
{
	//Throws the item up and into the air, falling nearby
	if (m_lootToThrow.Num() == 0)
		return;
	ABBBaseItem* item = m_lootToThrow[0];

	if (item)
	{
		//get a location above the top middle of the chest
		FActorSpawnParameters spawnParams;
		spawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
		FVector location = GetActorLocation();
		location.Z += Mesh->Bounds.BoxExtent.Z;

		//Spawn the item
		ABBBaseItem* spawnedItem = GetWorld()->SpawnActor<ABBBaseItem>(item->GetClass(), location, FRotator::ZeroRotator, spawnParams);
		if(spawnedItem == nullptr)
			return;
		//Create our force vector
		FVector force = FVector(0, 0, LootThrowForce);
		//Add a random force to the x and y
		force.X += FMath::RandRange(-LootThrowForce, LootThrowForce);
		force.Y += FMath::RandRange(-LootThrowForce, LootThrowForce);
		//Add the force to the item
		spawnedItem->MeshComponent->AddImpulse(force, NAME_None, true);
	}
	m_lootToThrow.RemoveAt(0);
	
}

void ABBRewardsChest::DeactivateBurst()
{
	//Turns off the particle effect
	RevieledParticleEffect->Deactivate();
}

