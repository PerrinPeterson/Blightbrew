// Copyright © Too Many Eyes , 2022


#include "BBCraftingStation.h"
#include "../Inventory/BBInventorySlotNew.h"
#include "../Characters/Player/BBPlayerCharacter.h"
#include "../UI/BBHUD.h"

// Sets default values
ABBCraftingStation::ABBCraftingStation()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("Mesh Component");
	SetRootComponent(MeshComponent);

}

// Called when the game starts or when spawned
void ABBCraftingStation::BeginPlay()
{
	Super::BeginPlay();

	for (int i = 0; i < CraftingSlotNum; i++)
	{
		CraftingSlots.Add(NewObject<UBBInventorySlotNew>());
	}
	ProductSlot = NewObject<UBBInventorySlotNew>();

	m_focusText = FText::FromString("Crafting Station");
}

// Called every frame
void ABBCraftingStation::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

//If theis returns false, the bottle is wrong, and the items wont be consumed, if the entire recipe is wrong, the items will be consumed.
bool ABBCraftingStation::Craft()
{
	//Cycle through the map of recipies
	for (const auto& recipe : CraftingBook)
	{
		//If the recipe fully, or partially matches.
		if (recipe.Key.ItemOne.GetDefaultObject()->GetItemName() == CraftingSlots[0]->GetItemName())
			if (recipe.Key.ItemTwo.GetDefaultObject()->GetItemName() == CraftingSlots[1]->GetItemName())
				if (recipe.Key.ItemThree.GetDefaultObject()->GetItemName() == CraftingSlots[2]->GetItemName())
					if (recipe.Value == true)
					{
						//Probably ned to change this now... We use a different logic for spawning items.
						//FActorSpawnParameters SpawnParams = FActorSpawnParameters();
						//SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
						//FTransform transform;
						//ABBBaseItem* craftedItem = (ABBBaseItem*)GetWorld()->SpawnActor(recipe.Key.ItemThree.GetDefaultObject()->StaticClass(), &transform, SpawnParams);
						int64 num = 1;
						if (ProductSlot->SetToItem(recipe.Key.OutputItem.GetDefaultObject(), num))
						{
							for (int j = 0; j < CraftingSlots.Num(); j++)
							{
								num = 1;
								CraftingSlots[j]->Decrement(num);
							}
						}
						return true;
					}
					else
					{
						return false;
					}



	}
	//If the recipe is wrong.
	for (int i = 0; i < CraftingSlots.Num(); i++)
	{
		int64 num = 1;
		CraftingSlots[i]->Decrement(num);
	}
	return true;
}

void ABBCraftingStation::OnFocus(AActor* InstagatingActor)
{
}

void ABBCraftingStation::OnInteract(AActor* InstagatingActor)
{
	//Cast the actor to a player character.
	ABBPlayerCharacter* player = Cast<ABBPlayerCharacter>(InstagatingActor);
	//If the cast was successful.
	if (player)
	{
		//Open the crafting screen.
		player->GetHUD()->ToggleCrafting(CraftingBook, this);
		player->RefreshHudVisibility();
		player->ToggleInputMode(EInputMode::GameAndUI);
	}

}

void ABBCraftingStation::SetFocusText(FText text)
{
	m_focusText = text;
}

FText ABBCraftingStation::GetFocusText()
{
	return m_focusText;
}


