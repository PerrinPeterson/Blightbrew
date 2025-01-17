// Copyright © Too Many Eyes , 2022


#include "BBInventoryComponent.h"
#include "BBInventorySlotNew.h"
#include "../Items/BBBaseItem.h"
#include "../Characters/Player/BBPlayerCharacter.h"

// Sets default values for this component's properties
UBBInventoryComponent::UBBInventoryComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;


	// ...
}


// Called when the game starts
void UBBInventoryComponent::BeginPlay()
{
	Super::BeginPlay();

	//DEPRICATED now uses new InventorySlots
	//FActorSpawnParameters SpawnParams = FActorSpawnParameters();
	//SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
	//SpawnParams.Name = FName("InventorySlot");
	//FTransform transform;
	/*MouseSlot = (ABBInventorySlot*)GetWorld()->SpawnActor(ABBInventorySlot::StaticClass(), &transform, SpawnParams);

	for (int i = 0; i < InventorySize; i++)
	{
		InventorySlots.Add((ABBInventorySlot*)GetWorld()->SpawnActor(ABBInventorySlot::StaticClass(), &transform, SpawnParams));
	}

	for (int i = 0; i < QuickSlotSize; i++)
	{
		QuickSlots.Add((ABBInventorySlot*)GetWorld()->SpawnActor(ABBInventorySlot::StaticClass(), &transform, SpawnParams));
	}*/

	MouseSlot = NewObject<UBBInventorySlotNew>();

	for (int i = 0; i < InventorySize; i++)
	{
		InventorySlots.Add(NewObject<UBBInventorySlotNew>());
	}

	for (int i = 0; i < QuickSlotSize; i++)
	{
		QuickSlots.Add(NewObject<UBBInventorySlotNew>());
	}

	
}


// Called every frame
void UBBInventoryComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

bool UBBInventoryComponent::AddToInventory(ABBBaseItem* item, int64& num)
{
	//TODO:Add Debug Logging to watch for errors in the code.
	//Adds items to inventory, returns false if there are still items in the stack it was pulling from, or if it failed for any reason, and edits the reference to the amount left over.
	if (item == nullptr)
		return false;
	if (num == 0)
		return false;

	for (int i = 0; i < InventorySize; i++)
	{
		//If the slot is empty, or is the same item
		//TODO: Implement ItemIDs to compare with, as items 'can' have the same names. This is a later Perrin issue.
		if (InventorySlots[i]->GetItem() == nullptr || InventorySlots[i]->GetItemName() == item->GetItemName())
		{
			if (InventorySlots[i]->GetItem() == nullptr)
			{
				if (InventorySlots[i]->SetToItem(item, num))
					if (num == 0)
						return true;
			}
			else if (InventorySlots[i]->GetItemName() == item->GetItemName())
			{
				if (InventorySlots[i]->Increment(num))
				{
					//item->Destroy();
					if (num == 0)
						return true;
				}
			}

		}
	}
	return false;
}

bool UBBInventoryComponent::RemoveFromInventory(ABBBaseItem* item, int64 num)
{
	//TODO:Add Debug Logging to watch for errors in the code.
	//Removes items from inventory, returns false if there are not enough items in the inventory, or if it failed for any reason.
	if (item == nullptr)
		return false;
	if (num == 0)
		return false;

	TArray<int64> indexs;
	int64 stackAmountFound = 0;
	for (int i = 0; i < InventorySize; i++)
	{
		//If the slot is the same item
		//TODO: Implement ItemIDs to compare with, as items 'can' have the same names. This is a later Perrin issue.
		if (InventorySlots[i]->GetItemName() == item->GetItemName())
		{
			indexs.Add(i);
			stackAmountFound += InventorySlots[i]->GetStackSize();
		}
		if (stackAmountFound >= num)
		{
			for (int j = 0; j < indexs.Num(); j++)
			{
				//This will loop through and decriment ALL the stacks till the amount reaches 0
				if (InventorySlots[indexs[j]]->Decrement(num))
					if (num == 0)
						return true;
			}
		}
	}
	return false;
}

TArray<int64> UBBInventoryComponent::GetStackSizes()
{
	TArray<int64> stackSizes;

	for (int i = 0; i < InventorySize; i++)
	{
		stackSizes.Add(InventorySlots[i]->GetStackSize());
	}
	return stackSizes;
}

int64 UBBInventoryComponent::GetStackSize(int64 index)
{
	return InventorySlots[index]->GetStackSize();
}

int64 UBBInventoryComponent::GetStackSize(ABBBaseItem* item)
{
	int64 stackSizeTotal = 0;
	for (int i = 0; i < InventorySize; i++)
	{
		if (item->GetItemName() == InventorySlots[i]->GetItemName())
		{
			stackSizeTotal += InventorySlots[i]->GetStackSize();
		}
	}
	return stackSizeTotal;
}

TArray<int64> UBBInventoryComponent::GetIndexesOfItem(ABBBaseItem* item)
{
	TArray<int64> itemIndexs;
	if (item != nullptr)
	{
		return itemIndexs;
	}
	for (int i = 0; i < InventorySize; i++)
	{
		if (item->GetItemName() == InventorySlots[i]->GetItemName())
		{
			itemIndexs.Add(i);
		}
	}
	return itemIndexs;
}

void UBBInventoryComponent::EmptyInventorySlot(int64 index)
{
	InventorySlots[index]->Reset();
}

bool UBBInventoryComponent::MoveToSlot(UBBInventorySlotNew* outSlot, UBBInventorySlotNew* inSlot)
{
	//Error Checking
	/*
	* If the slots are null
	* If the item we're moving is null
	* If the slot we're moving to isn't empty (will call CombineStacks, if applicable)
	*/
#pragma region ErrorChecking
	if (outSlot == nullptr || inSlot == nullptr)
		return false;
	if (outSlot->GetItem() == nullptr)
		return false;
	if (inSlot->GetItem() != nullptr)
		if (inSlot->GetItemName() != outSlot->GetItemName())
			return false;
		else
			if (CombineStacks(outSlot, inSlot))
				return true;
#pragma endregion
	//This function will actually do the logic of setting the item in the destination, pushing the amount all the way to the stack size limit and no further, AND it will change the orginal stacks size.
	inSlot->SetToItem(outSlot->GetItem(), outSlot->GetStackSizeRef());
	if (outSlot->GetStackSize() == 0)
	{
		outSlot->Reset();
	}
	return true;
}

bool UBBInventoryComponent::MoveToSlot(int64 outSlotIndex, int64 inSlotIndex)
{
	//Error Checking
	/*
	* If the Index's break the bounds of the TArray
	* If the slots the index's point at are null
	* If the item we're moving is null
	* If the slot we're moving to isn't empty (will call CombineStacks, if applicable)
	*/
#pragma region ErrorChecking
	if (outSlotIndex >= InventorySize || inSlotIndex >= InventorySize || outSlotIndex < 0 || inSlotIndex < 0)
		return false;
	if (InventorySlots[outSlotIndex] == nullptr || InventorySlots[inSlotIndex] == nullptr)
		return false;
	if (InventorySlots[outSlotIndex]->GetItem() == nullptr)
		return false;
	if (InventorySlots[inSlotIndex]->GetItem() != nullptr)
		if (InventorySlots[inSlotIndex]->GetItemName() != InventorySlots[outSlotIndex]->GetItemName())
			return false;
		else
			if (CombineStacks(InventorySlots[outSlotIndex], InventorySlots[inSlotIndex]))
				return true;
#pragma endregion

	//This function will actually do the logic of setting the item in the destination, pushing the amount all the way to the stack size limit and no further, AND it will change the orginal stacks size.
	InventorySlots[inSlotIndex]->SetToItem(InventorySlots[outSlotIndex]->GetItem(), InventorySlots[outSlotIndex]->GetStackSizeRef());
	if (InventorySlots[outSlotIndex]->GetStackSize() == 0)
	{
		InventorySlots[outSlotIndex]->Reset();
	}

	return true;
}

bool UBBInventoryComponent::SplitStack(UBBInventorySlotNew* outSlot, UBBInventorySlotNew* inSlot)
{
	if (outSlot == nullptr || inSlot == nullptr)
		return false;
	if (outSlot->GetItem() == nullptr)
		return false;
	if (inSlot->GetItem() != nullptr)
		return false;

	int64 halfStack = outSlot->GetStackSize() / 2;
	if (outSlot->Decrement(halfStack))
		return false;

	if (inSlot->SetToItem(outSlot->GetItem(), halfStack))
	{
		outSlot->Increment(halfStack);
		return false;
	}
	return true;
}

bool UBBInventoryComponent::SplitStack(int64 outSlot, int64 inSlot)
{
	if (outSlot >= InventorySize || inSlot >= InventorySize || outSlot < 0 || inSlot < 0)
		return false;
	if (InventorySlots[outSlot] == nullptr || InventorySlots[inSlot] == nullptr)
		return false;
	if (InventorySlots[outSlot]->GetItem() == nullptr)
		return false;
	if (InventorySlots[inSlot]->GetItem() != nullptr)
		return false;

	int64 halfStack = InventorySlots[outSlot]->GetStackSize() / 2;
	if (InventorySlots[outSlot]->Decrement(halfStack))
		return false;

	if (InventorySlots[inSlot]->SetToItem(InventorySlots[outSlot]->GetItem(), halfStack))
	{
		InventorySlots[outSlot]->Increment(halfStack);
		return false;
	}
	return true;
}

bool UBBInventoryComponent::SwapStacks(UBBInventorySlotNew* outSlot, UBBInventorySlotNew* inSlot)
{
	ABBBaseItem* inItem = inSlot->GetItem();
	int64 inItemStackSize = inSlot->GetStackSize();
	inSlot->Reset();
	if (!(inSlot->SetToItem(outSlot->GetItem(), outSlot->GetStackSizeRef())))
	{
		////UE_LOG(LogTemp, Warning, TEXT("InventoryComponent failed to set a destination slot to a new item, so returned false."));
		return false;
	}

	outSlot->Reset();
	if (!(outSlot->SetToItem(inItem, inItemStackSize)))
	{
		////UE_LOG(LogTemp, Warning, TEXT("InventoryComponent failed to set a destination slot to a new item, so returned false."));
		return false;
	}
	return true;
}

bool UBBInventoryComponent::SwapStacks(int64 outSlot, int64 inSlot)
{
	ABBBaseItem* inItem = InventorySlots[inSlot]->GetItem();
	int64 inItemStackSize = InventorySlots[inSlot]->GetStackSize();
	InventorySlots[inSlot]->Reset();
	if (!(InventorySlots[inSlot]->SetToItem(InventorySlots[outSlot]->GetItem(), InventorySlots[outSlot]->GetStackSizeRef())))
	{
		////UE_LOG(LogTemp, Warning, TEXT("InventoryComponent failed to set a destination slot to a new item, so returned false."));
		return false;
	}

	InventorySlots[outSlot]->Reset();
	if (!(InventorySlots[outSlot]->SetToItem(inItem, inItemStackSize)))
	{
		////UE_LOG(LogTemp, Warning, TEXT("InventoryComponent failed to set a destination slot to a new item, so returned false."));
		return false;
	}
	return true;
}

bool UBBInventoryComponent::CombineStacks(UBBInventorySlotNew* outSlot, UBBInventorySlotNew* inSlot)
{
	if (outSlot == nullptr || inSlot == nullptr)
		return false;
	if (outSlot->GetItem() == nullptr)
		return false;
	if (inSlot->GetItem() == nullptr)
		MoveToSlot(outSlot, inSlot);
	if (outSlot->GetItemName() != inSlot->GetItemName())
		return false;

	//Make sure we don't break the stack size barrier, this func should do it for us.
	if (inSlot->Increment(outSlot->GetStackSizeRef()))
	{
		if (outSlot->GetStackSize() == 0)
		{
			outSlot->Reset();
		}
		return true;
	}
	return false;
}

bool UBBInventoryComponent::CombineStacks(int64 outSlot, int64 inSlot)
{
	if (InventorySlots[outSlot] == nullptr || InventorySlots[inSlot] == nullptr)
		return false;
	if (InventorySlots[outSlot]->GetItem() == nullptr)
		return false;
	if (InventorySlots[inSlot]->GetItem() == nullptr)
		if (MoveToSlot(InventorySlots[outSlot], InventorySlots[inSlot]))
			return true;
	if (InventorySlots[outSlot]->GetItemName() != InventorySlots[inSlot]->GetItemName())
		return false;

	//Make sure we don't break the stack size barrier, this func should do it for us.
	if (InventorySlots[inSlot]->Increment(InventorySlots[outSlot]->GetStackSizeRef()))
	{
		if (InventorySlots[outSlot]->GetStackSize() == 0)
		{
			InventorySlots[outSlot]->Reset();
		}
		return true;
	}
	return false;
}

//Drops Single Items
bool UBBInventoryComponent::DropItem(UBBInventorySlotNew* slot)
{
	//Drops the item in the slot, and returns true if successful.
	if (slot == nullptr)
		return false;
	if (slot->GetItem() == nullptr)
		return false;
	if (slot->GetStackSize() == 0)
		return false;
	
	//Spawn the item in the world.
	FActorSpawnParameters spawnParams;
	spawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	FVector spawnLocation = GetOwner()->GetActorLocation();
	//push the item out a bit.
	spawnLocation += GetOwner()->GetActorForwardVector() * 100;
	ABBBaseItem* droppedItem = GetWorld()->SpawnActor<ABBBaseItem>(slot->GetItem()->GetClass(), spawnLocation, FRotator::ZeroRotator, spawnParams);
	if (droppedItem == nullptr)
		return false;
	int64 num = 1;
	if (slot->Decrement(num))
	{
		return true;
	}
	return false;
}

bool UBBInventoryComponent::DropItem(int64 slotIndex)
{
	return false;
}

void UBBInventoryComponent::SetInventorySize(int size)
{
	InventorySize = size;
}

ABBBaseItem* UBBInventoryComponent::GetItem(int64 slotIndex)
{
	return InventorySlots[slotIndex]->GetItem();
}

bool UBBInventoryComponent::UseItemInSlot(int64 index, AActor* instagatingActor)
{
	if (InventorySlots[index]->UseItem(instagatingActor))
		return true;
	return false;
}

bool UBBInventoryComponent::UseItemInQuickSlot(int64 index, AActor* instagatingActor)
{
	if (index < 0 || index > QuickSlots.Num())
		return false;
	if (QuickSlots[index]->UseItem(instagatingActor))
		return true;
	return false;
}
