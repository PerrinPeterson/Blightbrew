// Copyright © Too Many Eyes , 2022


#include "BBInventorySlotDep.h"
#include "../Items/BBBaseItem.h"

// Sets default values
ABBInventorySlot::ABBInventorySlot()
{
    // Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ABBInventorySlot::BeginPlay()
{
    Super::BeginPlay();

}

// Called every frame
void ABBInventorySlot::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

bool ABBInventorySlot::Increment(int64& num)
{
    if (StackSize == 0 || ItemClass == nullptr)
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

bool ABBInventorySlot::Decrement(int64& num)
{
    if (StackSize == 0 || ItemClass == nullptr)
    {
        return false;
    }
    if (StackSize < num)
    {
        num -= StackSize;
        //Item->Destroy();
        Reset();
        return true;
    }
    if ((StackSize - num) == 0)
    {
        //Item->Destroy();
        Reset();
        return true;
    }

    StackSize -= num;
    num = 0;
    return true;
}

void ABBInventorySlot::Reset()
{
    MaxStackSize = 0;
    StackSize = 0;
    //Item = nullptr;
    ItemClass = nullptr;
}

bool ABBInventorySlot::SetToItem(ABBBaseItem* item, int64& num)
{
    if (item && num > 0)
    {
        //Item = item;
        ItemClass = item->GetClass();
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

FString ABBInventorySlot::GetItemName()
{
    if (ItemClass)
        return ItemClass.GetDefaultObject()->GetItemName();
    else
        return FString();
}

bool ABBInventorySlot::UseItem(AActor* instagatingActor)
{
    /*if (Item)
    {
        if (Item->OnUse(BBControlType::CONSUME, instagatingActor))
        {
            int64 num = 1;
            Decrement(num);
            return true;
        }
        else if (Item->OnUse(BBControlType::THROW, instagatingActor))
        {
            int64 num = 1;
            Decrement(num);
            return true;
        }
    }*/

    if (ItemClass)
    {
        if (ItemClass.GetDefaultObject()->OnUse(BBControlType::CONSUME, instagatingActor))
        {
            int64 num = 1;
            Decrement(num);
            return true;
        }
        else if ((ItemClass.GetDefaultObject()->OnUse(BBControlType::THROW, instagatingActor)))
        {
            int64 num = 1;
            Decrement(num);
            return true;
        }
    }
    return false;
}


