// Copyright © Too Many Eyes , 2022


#include "BBInventorySlotNew.h"
#include "../Items/BBBaseItem.h"

UBBInventorySlotNew::UBBInventorySlotNew()
{

}

/*Increments a stack by the num. Things to keep in mind:
*   -Will not increment if slot is currently empty.
*   -Will not increment past the items max stack size.
* Once the incrementation is done, the function will set the reference to the num to the
* remaining amount, so the user can then increment more stacks.
*/
bool UBBInventorySlotNew::Increment(int64& num)
{
    if (StackSize == 0 || Item == nullptr)
    {
        return false;
    }
    if (StackSize >= MaxStackSize)
        return false;
    if ((StackSize + num) > MaxStackSize)
    {
        num -= (MaxStackSize - StackSize);
        StackSize = MaxStackSize;
        return true;
    }

    StackSize += num;
    num = 0;
    return true;
}

/*Decrements a stack by the num. Things to keep in mind:
*   -Will not decrement if slot is currently empty.
* If the slot hits 0 due the the decrement, the slot will reset.
* Once the decrementation is done, the function will set the reference to the num to the
* remaining amount, so the user can then decrement more stacks.
* 
* NEW IN THIS VERSION
* Decrement no longer calls destroy on the pointer to an ABBBaseItem.
* Cleanup of these actors should be dealt with on pickup from now on.
*/
bool UBBInventorySlotNew::Decrement(int64& num)
{
    if (StackSize == 0 || Item == nullptr)
    {
        return false;
    }
    if (StackSize < num)
    {
        num -= StackSize;
        Reset();
        return true;
    }
    if ((StackSize - num) == 0)
    {
        Reset();
        return true;
    }

    StackSize -= num;
    num = 0;
    return true;
}

void UBBInventorySlotNew::Reset()
{
    MaxStackSize = 0;
    StackSize = 0;
    Item = nullptr;
}

bool UBBInventorySlotNew::SetToItem(ABBBaseItem* item, int64& num)
{
    if (item && num > 0)
    {
        Item = item->GetClass();
        MaxStackSize = item->GetMaxStackSize();
        if (num < MaxStackSize)
        {
            StackSize = num;
            num = 0;
            return true;
        }
        else
        {
            StackSize = MaxStackSize;
            num -= MaxStackSize;
            return true;
        }
    }
    return false;
}

ABBBaseItem* UBBInventorySlotNew::GetItem()
{
    return Item.GetDefaultObject();
}

TSubclassOf<ABBBaseItem> UBBInventorySlotNew::GetItemClass()
{
	return Item;
}

FString UBBInventorySlotNew::GetItemName()
{
    if (Item)
        return Item.GetDefaultObject()->GetItemName();
    else
        return FString();
}

bool UBBInventorySlotNew::UseItem(AActor* instagatingActor)
{
    if (Item)
    {
        if (Item.GetDefaultObject()->OnUse(BBControlType::CONSUME, instagatingActor))
        {
            int64 num = 1;
            Decrement(num);
            return true;
        }
        else if ((Item.GetDefaultObject()->OnUse(BBControlType::THROW, instagatingActor)))
        {
            int64 num = 1;
            Decrement(num);
            return true;
        }
    }
    return false;
}
