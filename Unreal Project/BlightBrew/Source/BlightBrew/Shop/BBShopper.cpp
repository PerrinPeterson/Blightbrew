// Copyright © Too Many Eyes , 2022


#include "BBShopper.h"
#include "../Inventory/Storage/BBStorageContainer.h"
#include "../Inventory/BBInventorySlotNew.h"
#include "../Inventory/BBInventoryComponent.h"
#include "BlightBrew/Items/BBBaseItem.h"
#include "BBShopManager.h"
#include "BlightBrew/Characters/Player/BBPlayerCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/CharacterMovementComponent.h"

// Sets default values
ABBShopper::ABBShopper()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


	Init();

	//Init();
}

void ABBShopper::Init()
{
	Super::Init();

	FocusText = FText::FromString(ShopperID.ShopperName);

	ShopperMesh = CreateDefaultSubobject<UStaticMeshComponent>("Static Mesh");
	ShopperMesh->SetupAttachment(RootComponent);

	InventoryComponent = CreateDefaultSubobject<UBBInventoryComponent>("Inventory Component");
	m_hasShopped = true;
	m_isWaiting = false;

}

// Called when the game starts or when spawned
void ABBShopper::BeginPlay()
{
	Super::BeginPlay();

	GetCharacterMovement()->MaxWalkSpeed = 200.0f;
}

// Called every frame
void ABBShopper::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	//if(!m_hasShopped)
	//	CheckShelf();
}

// Called to bind functionality to input
void ABBShopper::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ABBShopper::OnFocus(AActor* InstigatingActor)
{
	Super::OnFocus(InstigatingActor);

	if (m_isWaiting)
	{
		SetFocusText(FText::FromString(ShopperID.ShopperName));
	}
	else
	{
		SetFocusText(FText::FromString(ShopperID.ShopperName + " (BUSY)"));
	}
}

void ABBShopper::OnInteract(AActor* InstigatingActor)
{
	Super::OnInteract(InstigatingActor);

	if(InstigatingActor->IsA(ABBPlayerCharacter::StaticClass()))
	{
		if (m_isWaiting)
		{
			////Open Dialog
			////Add the sold items to the Economy Managers memory
			////For now, they'll buy everything they picked up, no bartering
			//for (UBBInventorySlotNew* slot : InventoryComponent->GetInventorySlots())
			//{
			//	if (slot->GetItemClass())
			//	{
			//		ABBPlayerCharacter* player = (ABBPlayerCharacter*)InstigatingActor;
			//		//Need to replace the 10 with the desired price, set in the book, and after the barter
			//		ShopperID.Shop->BuyItem(player, slot->GetItemClass(), slot->GetStackSize(), 10);
			//	}
			//}
			//m_isWaiting = false;
		}
		else
		{
			//Play a voiceline or something
			UGameplayStatics::PlaySoundAtLocation(this, JumpFX, GetActorLocation());
		}
	}


}

//Value is the new value you're asking for
bool ABBShopper::Barter(int64 newValue, int64 shopValue)
{
	if (newValue < shopValue)
	{
		return true;
	}
	//Calculate the percent increase
	int64 percentIncrease = ((newValue - shopValue) / shopValue) * 100;
	//Take this plus the barter resistance.
	int64 barterSkill = ShopperID.BarterResistance;
	int64 barterChance = percentIncrease + barterSkill;
	//Roll a random number between 0 and 100
	int64 roll = FMath::RandRange(0, 100);
	//If the roll is greater than the barter chance, the barter is successful
	if (roll > barterChance)
	{
		return true;
	}
	return false;
	//The rest of the barter logic goes in here, It's increadibly conviluted though so I'll do it as part of polish.
}

bool ABBShopper::Sell()
{

	bool hasSold = false;

	for (UBBInventorySlotNew* slot : InventoryComponent->GetInventorySlots())
	{
		if (slot->GetItemClass())
		{
			TArray<AActor*> FoundActors;
			UGameplayStatics::GetAllActorsOfClass(GetWorld(), ABBPlayerCharacter::StaticClass(), FoundActors);

			if (ABBPlayerCharacter* player = Cast< ABBPlayerCharacter>(FoundActors[0]))
			{
				//Need to replace the 10 with the desired price, set in the book, and after the barter
				ShopperID.Shop->BuyItem(player, slot->GetItemClass(), slot->GetStackSize(), ShopperID.Shop->GetShopItemValue(slot->GetItemClass()));
				m_isWaiting = false;
				hasSold = true;
			}

		}
	}

	return hasSold;
}

void ABBShopper::CheckShelf()
{
	//Checks the shelf in front of it, for debug purposes it'll check all the shelves in the shop area
	//Use something like this, the storage shelves will have their own function to check if they have the item for the shopper
	/*ABBStorageShelf* shelf = (ABBStorageShelf)hitActor;
	* if(shelf)
	* {
	*	shelf->OnInteract(this);
	* }
	*/
	
#pragma region Debug
	//Debug code to check all the shelves in the shop area
	TArray<ABBStorageContainer*> shelves;
	shelves = ShopperID.Shop->GetStorageContainerArray();
	
	for (ABBStorageContainer* shelf : shelves)
	{
		shelf->OnInteract(this);
	}
	m_hasShopped = true;
#pragma endregion
	
}

bool ABBShopper::WantsItem(TSubclassOf<ABBBaseItem> item)
{
	//Check the item against the items in the shopping list
	
	if (ShopperID.ShoppingList.Contains(item))
	{
		//Check if the item is cheaper, or more expensive than the EconomyManager says it should be
		//If it's cheaper, buy it
		//If it's more expensive, roll to see if they buy it
		//If they don't buy it, remove it from the list
		
		int64 shopCost;
		int64 actualValue;
		
		ShopperID.Shop->GetCosts(item, shopCost, actualValue);
		if (shopCost <= actualValue)
		{
			//The item is cheaper than the economy Manager says it is
			return true;
		}
		else if (shopCost > actualValue)
		{
			//Find the percent increase in cost, and the value increase, and roll the higher of the two
			int64 percentIncrease = ((shopCost - actualValue) / actualValue) * 100;
			int64 valueIncrease = shopCost - actualValue;
			int64 roll = FMath::RandRange(0, 100);
			if (percentIncrease < valueIncrease)
			{
				if (roll > percentIncrease)
				{
					//The item is more expensive than the economy Manager says it is, but the shopper still bought it
					return true;
				}
				else
				{
					//The item is more expensive than the economy Manager says it is, and the shopper didn't buy it
					ShopperID.ShoppingList.Remove(item);
					return false;
				}
			}
			else
			{
				if (roll > valueIncrease)
				{
					//The item is more expensive than the economy Manager says it is, but the shopper still bought it
					return true;
				}
				else
				{
					//The item is more expensive than the economy Manager says it is, and the shopper didn't buy it
					ShopperID.ShoppingList.Remove(item);
					return false;
				}
			}
		}
	}
	return false;
	
}

void ABBShopper::PullFromInventory(UBBInventorySlotNew* storageSlot)
{
	int64 grabAmount = ShopperID.ShoppingList[storageSlot->GetItemClass()];
	int64 grabbedAmount = storageSlot->GetStackSize();
	TSubclassOf<ABBBaseItem> item = storageSlot->GetItemClass();
	storageSlot->Decrement(grabAmount);
	grabbedAmount -= storageSlot->GetStackSize();
	
	if (grabAmount == 0)
	{
		//That item is no longer wanted
		ShopperID.ShoppingList.Remove(item);
	}
	else
	{
		//Update the amount wanted
		ShopperID.ShoppingList[item] = grabAmount;
	}
	
	InventoryComponent->AddToInventory(item.GetDefaultObject(), grabbedAmount);
	
}

bool ABBShopper::Interact()
{
	FHitResult hitResult;
	FVector traceStart = GetActorLocation();
	FVector traceEnd = traceStart + (GetControlRotation().Vector() * 500.0f);
	FCollisionQueryParams params;
	params.AddIgnoredActor(this);

	GetWorld()->LineTraceSingleByChannel(hitResult, traceStart, traceEnd, ECC_WorldDynamic, params);

	/*DrawDebugLine(GetWorld(),
		traceStart,
		traceEnd,
		FColor::Magenta,
		false,
		1,
		0,
		5);*/

	if (hitResult.GetActor())
	{
		if (IBBInterface* interactable = Cast<IBBInterface>(hitResult.GetActor()))
		{
			FString outputMessage = ShopperID.ShopperName + " interacted with: " + interactable->GetFocusText().ToString();
			//UE_LOG(LogTemp, Warning, TEXT("%s"), *outputMessage);
			interactable->OnInteract(this);

			return true;
		}	//ENDIF

	}	//ENDIF

	return false;
}

