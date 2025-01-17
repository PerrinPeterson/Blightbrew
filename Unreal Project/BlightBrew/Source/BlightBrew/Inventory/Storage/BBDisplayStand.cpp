// Copyright © Too Many Eyes , 2022

#include "BBDisplayStand.h"
#include "../../Characters/Player/BBPlayerCharacter.h"
#include "../BBInventorySlotNew.h"
#include "../BBInventoryComponent.h"
#include "../../Engine/Classes/Components/BoxComponent.h"
#include "../../Items/BBBaseItem.h"
#include "../../Shop/BBShopper.h"
#include "../BBInventoryComponent.h"

ABBDisplayStand::ABBDisplayStand()
{
    StorageSlotBoundsBox = CreateDefaultSubobject<UBoxComponent>("Storage Slot Bounds Box");
    StorageSlotBoundsBox->SetupAttachment(RootComponent);

    StorageSlotMesh = CreateDefaultSubobject<UStaticMeshComponent>("Storage Slot Mesh");
    StorageSlotMesh->SetupAttachment(StorageSlotBoundsBox);
}

TArray<ABBBaseItem*> ABBDisplayStand::GetItems()
{
    TArray<ABBBaseItem*> items;
    items.Add(StorageSlot->GetItem());
    return items;
}

TArray<TSubclassOf<ABBBaseItem>> ABBDisplayStand::GetItemClasses()
{
    TArray<TSubclassOf<ABBBaseItem>> items;
    items.Add(StorageSlot->GetItemClass());
    return items;
}


void ABBDisplayStand::OnInteract(AActor* InstagatingActor)
{
    Super::OnInteract(InstagatingActor);

    ABBPlayerCharacter* player = Cast<ABBPlayerCharacter>(InstagatingActor);
    if (player)
    {
        //Should be replaced with UI logic
        UBBInventorySlotNew* playerSlot = player->GetInventoryComponent()->GetInventorySlots()[0];
        //If the storageslot is full
        if (StorageSlot->GetItem())
        {
            //If the players 0 slot has an item
            if (playerSlot->GetItem())
            {
                //stack them, if they're the same item
                if (playerSlot->GetItem() == StorageSlot->GetItem())
                    player->GetInventoryComponent()->CombineStacks(playerSlot, StorageSlot);
                //otherwise, swap them
                else
                    player->GetInventoryComponent()->SwapStacks(playerSlot, StorageSlot);
            }
            //Otherwise, just move the item
            else
            {
                player->GetInventoryComponent()->MoveToSlot(StorageSlot, playerSlot);
            }
        }
        //If the storageslot is empty
        else
        {
            //And the player has an item in the 0 slot, move the item to the storage
            if (playerSlot->GetItem())
                player->GetInventoryComponent()->MoveToSlot(playerSlot, StorageSlot);
            //otherwise, do nothing
        }
    }

	ABBShopper* shopper = Cast<ABBShopper>(InstagatingActor);
    if (shopper)
    {
        UBBInventoryComponent* inventory = shopper->InventoryComponent;

        if (shopper->WantsItem(StorageSlot->GetItemClass()))
        {
			shopper->PullFromInventory(StorageSlot);
        }
       
    }
        

    if (StorageSlot->GetItem())
    {
        StorageSlotMesh->SetRelativeScale3D(StorageSlot->GetItem()->GetRootComponent()->GetRelativeScale3D());

        /*UE_LOG(LogTemp, Warning, TEXT("X Scale: %d"), StorageSlot->GetItem()->GetActorScale().X);
        UE_LOG(LogTemp, Warning, TEXT("X Scale 3D: %d"), StorageSlot->GetItem()->GetActorScale3D().X);*/
        //StorageSlotMesh->SetRelativeScale3D(FVector(1.0f, 1.0f, 1.0f));
        StorageSlotMesh->SetStaticMesh(StorageSlot->GetItem()->MeshComponent->GetStaticMesh());
        StorageSlotMesh->SetMaterial(0, StorageSlot->GetItem()->MeshComponent->GetMaterial(0));
        int attempts = 0;
        while (StorageSlotMesh->Bounds.GetBox().GetSize().X > StorageSlotBoundsBox->Bounds.GetBox().GetSize().X && attempts <= 3)
        {
            attempts++;
            FVector currentScale = StorageSlotMesh->GetRelativeScale3D();
            FVector newScale = currentScale / 2;
            StorageSlotMesh->SetRelativeScale3D(newScale);
            //UE_LOG(LogTemp, Warning, TEXT("Attempts: %d"), attempts);
        }
    }
    else
    {
        StorageSlotMesh->SetStaticMesh(nullptr);
    }
}

void ABBDisplayStand::OnFocus(AActor* InstigatingActor)
{
	Super::OnFocus(InstigatingActor);
}

void ABBDisplayStand::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);


}

void ABBDisplayStand::BeginPlay()
{
    StorageSlot = NewObject<UBBInventorySlotNew>();
}

