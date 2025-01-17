// Copyright © Too Many Eyes , 2022


#include "BBShopManager.h"
#include "Components/BoxComponent.h"
#include "../../Engine/Classes/Kismet/GameplayStatics.h"
//Brightbrew
#include "BBShopper.h"
#include "../Inventory/Storage/BBStorageContainer.h"
#include "BBEconomyManager.h"
#include "../Characters/Player/BBPlayerCharacter.h"

// Sets default values
ABBShopManager::ABBShopManager()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Shop Area is the root component
	ShopArea = CreateDefaultSubobject<UBoxComponent>(TEXT("ShopArea"));
	SetRootComponent(ShopArea);

	SpawnArea = CreateDefaultSubobject<UBoxComponent>(TEXT("SpawnArea"));
	SpawnArea->SetupAttachment(RootComponent);

	DespawnArea = CreateDefaultSubobject<UBoxComponent>(TEXT("DespawnArea"));
	DespawnArea->SetupAttachment(RootComponent);

	WaitingArea = CreateDefaultSubobject<UBoxComponent>(TEXT("WaitingArea"));
	WaitingArea->SetupAttachment(RootComponent);

	SpawningTimer = 1.0f;
}

void ABBShopManager::FindStorageContainers()
{
	//Search for actors within the shop area that are storage containers, This will need to be called on shop open, not on begin play
	StorageContainers.Empty();
	TArray<AActor*> FoundActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ABBStorageContainer::StaticClass(), FoundActors);
	for (AActor* Actor : FoundActors)
	{
		//Check if they're in the shop area
		if (ShopArea->IsOverlappingActor(Actor))
		{
			//If they are, add them to the array
			ABBStorageContainer* StorageContainer = Cast<ABBStorageContainer>(Actor);
			if (StorageContainer)
			{
				StorageContainers.Add(StorageContainer);
			}
		}
	}
	//Next, update the Catalog
	for (ABBStorageContainer* StorageContainer : StorageContainers)
	{
		TArray<TSubclassOf<ABBBaseItem>> items = StorageContainer->GetItemClasses();
		for (TSubclassOf<ABBBaseItem> item : items)
		{
			if (ItemCatalog.Contains(item) || item == nullptr)
			{
				continue;
			}
			else
			{
				ItemCatalog.Add(item, 0);
			}
		}
	}
	//We'll only allow the AI to pick up an item if the value is greater than 0, so it forces the player to pick a new value for the new items.


	HasCheckedArea = true;
}

void ABBShopManager::SpawnShopper()
{
	//Xanders play zone, the only thing I'll have is the randomiser logic, the rest is up to you
	//Random logic for the type of shopper uses a similar logic to my weighted randomiser in the harvest spots

	if (!IsOpen || Shoppers.Num() >= MaxShoppers)
	{
		return;
	}

	//Create an array of the chances
	FBBShopperID id;
	TArray<int> weightedList;
	for (int i = 0; i < ReturnShopperChance; i++)
	{
		weightedList.Add(0);
	}
	for (int i = 0; i < CustomShopperChance; i++)
	{
		weightedList.Add(1);
	}
	for (int i = 0; i < RandomShopperChance; i++)
	{
		weightedList.Add(2);
	}
	//Get a random number between 0 and the length of the array
	int choice = FMath::RandRange(0, weightedList.Num() - 1);

	switch (weightedList[choice])
	{
	case 0: //A return shopper
		//Get a random number between 0 and the length of the array
		choice = FMath::RandRange(0, ReturnShopperIDs.Num() - 1);
		if (!ReturnShopperIDs.IsEmpty())
		{
			id = ReturnShopperIDs[choice];
			id.Shop = this;
			break; //We only want to break if we've found a shopper, otherwise, we want to continue to the next case
		}
	case 1: //A custom shopper
		//Get a random number between 0 and the length of the array
		choice = FMath::RandRange(0, CustomShopperIDs.Num() - 1);
		if (!CustomShopperIDs.IsEmpty())
		{
			id = CustomShopperIDs[choice];
			id.Shop = this;
			break; //We only want to break if we've found a shopper, otherwise, we want to continue to the next case
		}
	case 2: //A random shopper
		//Get a random number between 0 and the length of the array
		id = GenerateRandomShopperID();
		break;
	default:
		break;
	}

	FActorSpawnParameters SpawnParameters;
	SpawnParameters.Owner = this;
	SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButDontSpawnIfColliding;

	FVector spawnLoc = SpawnArea->GetComponentLocation();
	FRotator spawnRot = SpawnArea->GetComponentRotation();

	if (ABBShopper* shopper =
		Cast<ABBShopper>(
			GetWorld()->SpawnActor
			(ShopperClass,
				&spawnLoc,
				&spawnRot,
				SpawnParameters)))
	{
		shopper->ShopperID = id;
		//shopper.list

		Shoppers.Add(shopper);
	}

#pragma region Debug Code, remove when spawning is implemented
	//Sets the final element of the shopper array to the generated shopper, good when the shoppers are static, not when they're spawning and despawning
//if (!Shoppers.IsEmpty())
//	Shoppers[Shoppers.Num() - 1]->ShopperID = id;
#pragma endregion


}

void ABBShopManager::DespawnShopper(ABBShopper* shopper)
{
	//	Search for the shopper in the array
	for (auto Shopper : Shoppers)
	{
		//	If the shopper is in the array
		if (Shopper == shopper)
		{
			//	Remove it from the array
			Shoppers.Remove(Shopper);
			//	Destroy it and it's controller
			Shopper->Destroy();
			//	Break out of the search
			break;
		}
	}
}

FBBShopperID ABBShopManager::GenerateRandomShopperID()
{
	FBBShopperID id;
	//Randomise the name from the array of names
	if (!ShopperNames.IsEmpty())
		id.ShopperName = ShopperNames[FMath::RandRange(0, ShopperNames.Num() - 1)];
	else
		id.ShopperName = "Bob";

	//populate the traits map
	for (int i = 0; i < (int)EBBShopperTraits::NUM; i++)
	{
		id.Traits.Add((EBBShopperTraits)i, false);
	}
	int numTraits = FMath::RandRange(1, (int)EBBShopperTraits::NUM);
	for (int i = 0; i < numTraits; i++)
	{
		//chance for the same trait to be added twice, that's fine, more variety
		int trait = FMath::RandRange(0, (int)EBBShopperTraits::NUM - 1);
		id.Traits[(EBBShopperTraits)trait] = true;
		//Check for traits that are mutually exclusive
		switch ((EBBShopperTraits)trait)
		{
		case EBBShopperTraits::WEALTHY:
			id.Traits[EBBShopperTraits::POOR] = false;
			break;
		case EBBShopperTraits::POOR:
			id.Traits[EBBShopperTraits::WEALTHY] = false;
			break;
		}
	}

	//Shopping list is handled by a different function, so that we can regenerate custom and return shoppers
	//Generate the other values
	id.BarterResistance = FMath::RandRange(20, 80);
	id.Bulk = FMath::RandRange(20, 80);
	id.CostEffect = FMath::RandRange(20, 80);
	id.Happiness = FMath::RandRange(20, 80);
	id.Spendy = FMath::RandRange(20, 80);
	id.Shop = this;

	//If checks to apply the traits
	if (id.Traits[EBBShopperTraits::WEALTHY])
	{
		id.Spendy = 100;
		id.CostEffect += 20;
	}
	if (id.Traits[EBBShopperTraits::POOR])
	{
		id.Spendy = 100;
		id.CostEffect -= 20;
	}


	GenerateShoppingList(id);

	return id;
}

void ABBShopManager::GenerateShoppingList(FBBShopperID& ShopperID)
{
	//clear the list
	ShopperID.ShoppingList.Empty();

	//Decide how many items to add to the list
	int numItems = FMath::RandRange(1, 5);
	if (ShopItems.Num() < numItems)
		numItems = ShopItems.Num();
	{
		for (int i = 0; i < numItems; i++)
		{
			//Get a random item from the list of items
			TSubclassOf<ABBBaseItem> item = ShopItems[FMath::RandRange(0, ShopItems.Num() - 1)];
			//Get a random amount of that item
			int amount = FMath::RandRange(1, (ShopperID.Bulk / 10) + 1);
			if (ShopperID.Traits[EBBShopperTraits::MONTHLY])
			{
				amount += 2;
			}
			//Add it to the list
			ShopperID.ShoppingList.Add(item, amount);
		}
	}
	HasCheckedArea = true;
}

int ABBShopManager::GetShopItemValue(TSubclassOf<ABBBaseItem> item)
{
	//Get the item from the map
	int64 value = 0;
	if (ItemCatalog.Contains(item))
	{
		value = ItemCatalog[item];
	}
	return value;
}

void ABBShopManager::SetShopItemValue(TSubclassOf<ABBBaseItem> item, int64 value)
{
	//Set the item in the map
	if (ItemCatalog.Contains(item))
		ItemCatalog[item] = value;
}


void ABBShopManager::BuyItem(ABBPlayerCharacter* player, TSubclassOf<ABBBaseItem> item, int64 amount, int64 costPerUnit)
{
	//Send the items to the economy manager
	EconomyManager->SoldItems(item.GetDefaultObject(), amount);
	//Give the player the money for the items
	//get the player
	if (player)
	{
		//give them the money
		player->SetCurrency(player->GetCurrency() + (amount * costPerUnit));
	}


}

//THIS IS A DEBUG FUNCTION, REMOVE/DON'T USE WHEN SPAWNING IS IMPLEMENTED
void ABBShopManager::FindShoppers()
{
	Shoppers.Empty();
	//Get the shoppers within the shop area
	TArray<AActor*> FoundActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ABBShopper::StaticClass(), FoundActors);
	for (AActor* Actor : FoundActors)
	{
		//Check if they're in the shop area
		if (ShopArea->IsOverlappingActor(Actor))
		{
			//If they are, add them to the array
			ABBShopper* shopper = Cast<ABBShopper>(Actor);
			if (shopper)
			{
				Shoppers.Add(shopper);
				SpawnShopper();
			}
		}
	}
	HasCheckedArea = true;
}

// Called when the game starts or when spawned
void ABBShopManager::BeginPlay()
{
	Super::BeginPlay();

	GetWorldTimerManager().SetTimer(TimerTimerHandle, this, &ABBShopManager::CheckSpawn, 5.0f, true);
	EconomyManager->BeginPlay();

	//We generate the ShopItems list here, because we need to wait for the economy manager to be ready
	//Get the items from the economy manager
	ShopItems.Empty();
	EconomyManager->GetAllItems(ShopItems);

}

void ABBShopManager::CheckSpawn()
{

	SpawningTimer = FMath::RandRange(2.0f / Buisiness, 10.0f / Buisiness);
	GetWorldTimerManager().SetTimer(SpawningTimerHandle, this, &ABBShopManager::SpawnShopper, SpawningTimer, false);
}

// Called every frame
void ABBShopManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//Debug Purposes
	if (!HasCheckedArea)
	{
		FindStorageContainers();
		//FindShoppers();
	}
	//Debug purposes, needs to happen daily instead, commenting out for the release, if I have time I'll fix it
	/*if (!EconomyManager->RefreshItemValues)
	{
		EconomyManager->RefreshItemValues = true;
		EconomyManager->UpdateValues();
	}*/
	//Hate This, but if I don't, the player needs to close and reopen the shop to see new items.
	for (ABBStorageContainer* StorageContainer : StorageContainers)
	{
		TArray<TSubclassOf<ABBBaseItem>> items = StorageContainer->GetItemClasses();
		for (TSubclassOf<ABBBaseItem> item : items)
		{
			if (ItemCatalog.Contains(item) || item == nullptr)
			{
				continue;
			}
			else
			{
				ItemCatalog.Add(item, 0);
			}
		}
	}


}

void ABBShopManager::GetCosts(TSubclassOf<ABBBaseItem> item, int64& shopPrice, int64& econManagerPrice)
{
	//Bug Fixed, shouldn't crash if a test item, or an item without a value is placed on a shelf.
	if (ShopItems.Contains(item))
	{
		//Should be replaced with a call to the book, later thing.
		shopPrice = ItemCatalog[item];

		econManagerPrice = EconomyManager->GetItemValue(item.GetDefaultObject());
	}
}

