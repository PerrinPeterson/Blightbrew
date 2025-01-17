// Copyright © Too Many Eyes , 2022

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "BBInventorySlotNew.generated.h"

/*
* 
* 
*/
class ABBBaseItem;
UCLASS(BlueprintType, Blueprintable)
class BLIGHTBREW_API UBBInventorySlotNew : public UObject
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	UBBInventorySlotNew();

public:
	
	bool Increment(int64& num);
	bool Decrement(int64& num);

	void Reset();
	bool SetToItem(ABBBaseItem* item, int64& num);

	ABBBaseItem* GetItem();
	TSubclassOf<ABBBaseItem> GetItemClass();
	FString GetItemName();

	int64 GetStackSize() { return StackSize; }
	int64& GetStackSizeRef() { return StackSize; }
	int64 GetMaxStackSize() { return MaxStackSize; }

	bool UseItem(AActor* instagatingActor);


private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		int64 StackSize;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		int64 MaxStackSize;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		TSubclassOf<ABBBaseItem> Item;
};
