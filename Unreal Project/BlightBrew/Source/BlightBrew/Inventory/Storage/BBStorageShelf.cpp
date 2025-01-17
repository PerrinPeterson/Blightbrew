// Copyright © Too Many Eyes , 2022 - 2023


#include "BBStorageShelf.h"
#include "../BBInventorySlotNew.h"
#include "Components/BoxComponent.h"
#include "../../Items/BBBaseItem.h"
#include "../../Characters/Player/BBPlayerCharacter.h"
#include "../../Shop/BBShopper.h"

void ABBStorageShelf::BeginPlay()
{
	Super::BeginPlay();
	SetFocusText(FText::FromString("Shelf"));
	for (int i = 0; i < storageSlotNum; i++)
	{
		UBBInventorySlotNew* slot = NewObject<UBBInventorySlotNew>(this, FName(*FString::Printf(TEXT("StorageSlot%d"), i)));
		StorageSlots.Add(slot);
	}
}

void ABBStorageShelf::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	if (bNeedsUpdate) // This needs to be optimised, A LOT
	{
		//We need to set the meshs to their items, or null if they don't have an item
		for (int i = 0; i < storageSlotNum; i++)
		{
			UStaticMeshComponent* mesh = StorageSlotMeshs[i];
			UBoxComponent* box = StorageSlotBoundsBoxs[i];
			if (StorageSlots[i]->GetItem())
			{
				mesh->SetRelativeScale3D(StorageSlots[i]->GetItem()->GetRootComponent()->GetRelativeScale3D());
				mesh->SetStaticMesh(StorageSlots[i]->GetItem()->MeshComponent->GetStaticMesh());
				mesh->SetMaterial(0, StorageSlots[i]->GetItem()->MeshComponent->GetMaterial(0));
				
				int attempts = 0;
				FVector size = mesh->Bounds.GetBox().GetSize() * mesh->GetRelativeScale3D();
				
				while ((size.X > box->GetScaledBoxExtent().X
					|| size.Y > box->GetScaledBoxExtent().Y
					|| size.Z > box->GetScaledBoxExtent().Z)
					&& attempts <= 3)
				{

					attempts++;
					FVector currentScale = mesh->GetRelativeScale3D();
					FVector newScale = currentScale / 2;
					mesh->SetRelativeScale3D(newScale);
					size = mesh->Bounds.GetBox().GetSize() * mesh->GetRelativeScale3D();
				}
			}
			else
			{
				mesh->SetStaticMesh(nullptr);
			}
		}
	}
}

ABBStorageShelf::ABBStorageShelf()
{
	for (int i = 0; i < storageSlotNum; i++)
	{
		UStaticMeshComponent* mesh = CreateDefaultSubobject<UStaticMeshComponent>(FName(*FString::Printf(TEXT("StorageSlotMesh%d"), i)));
		mesh->SetupAttachment(RootComponent);
		UBoxComponent* box = CreateDefaultSubobject<UBoxComponent>(FName(*FString::Printf(TEXT("StorageSlotBoundsBox%d"), i)));
		box->SetupAttachment(mesh);
		StorageSlotMeshs.Add(mesh);
		StorageSlotBoundsBoxs.Add(box);
	}
}

void ABBStorageShelf::OnFocus(AActor* InstigatingActor)
{
	Super::OnFocus(InstigatingActor);
}

void ABBStorageShelf::OnInteract(AActor* InstigatingActor)
{
	//Player Logic
	ABBPlayerCharacter* player = Cast<ABBPlayerCharacter>(InstigatingActor);
	if (player)
	{
		player->GetHUD()->ToggleStorage(this);
		player->RefreshHudVisibility();
		player->ToggleInputMode(EInputMode::GameAndUI);
	}

	//Shopper Logic
	ABBShopper* shopper = Cast<ABBShopper>(InstigatingActor);
	if (shopper)
	{
		UBBInventoryComponent* inventory = shopper->InventoryComponent;
		for (int i = 0; i < storageSlotNum; i++)
		{
			if (shopper->WantsItem(StorageSlots[i]->GetItemClass()))
			{
				shopper->PullFromInventory(StorageSlots[i]);
			}
		}
		bNeedsUpdate = true;
	}
}

TArray<ABBBaseItem*> ABBStorageShelf::GetItems()
{
	TArray<ABBBaseItem*> items;
	for (UBBInventorySlotNew* slot : StorageSlots)
	{
		if (slot->GetItem() != nullptr)
		{
			items.Add(slot->GetItem());
		}
	}
	return items;
}

TArray<TSubclassOf<ABBBaseItem>> ABBStorageShelf::GetItemClasses()
{
	TArray<TSubclassOf<ABBBaseItem>> itemClasses;
	for (UBBInventorySlotNew* slot : StorageSlots)
	{
		if (slot->GetItem() != nullptr)
		{
			itemClasses.Add(slot->GetItemClass());
		}
	}
	return itemClasses;
}
