// Copyright © Too Many Eyes , 2022
// Copyright © Too Many Eyes , 2022

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "BBInventoryComponent.generated.h"

class UBBInventorySlotNew;
class ABBBaseItem;

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class BLIGHTBREW_API UBBInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UBBInventoryComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		int64 InventorySize = 10;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		int64 QuickSlotSize = 3;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		TArray<UBBInventorySlotNew*> InventorySlots;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		UBBInventorySlotNew* MouseSlot;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		TArray<UBBInventorySlotNew*> QuickSlots;
public:

	bool AddToInventory(ABBBaseItem* item, int64& num);
	bool RemoveFromInventory(ABBBaseItem* item, int64 num);
	

	TArray<int64> GetStackSizes();
	int64 GetStackSize(int64 index);
	int64 GetStackSize(ABBBaseItem* item);

	TArray<int64> GetIndexesOfItem(ABBBaseItem* item);

	//TODO: Add functions for Mouse and Quickslots
	void EmptyInventorySlot(int64 index);

	bool MoveToSlot(UBBInventorySlotNew* outSlot, UBBInventorySlotNew* inSlot);
	bool MoveToSlot(int64 outSlotIndex, int64 inSlotIndex);
	bool SplitStack(UBBInventorySlotNew* outSlot, UBBInventorySlotNew* inSlot);	
	bool SplitStack(int64 outSlot, int64 inSlot);							
	bool SwapStacks(UBBInventorySlotNew* outSlot, UBBInventorySlotNew* inSlot);	
	bool SwapStacks(int64 outSlot, int64 inSlot);							
	bool CombineStacks(UBBInventorySlotNew* outSlot, UBBInventorySlotNew* inSlot);
	bool CombineStacks(int64 outSlot, int64 inSlot);
	bool DropItem(UBBInventorySlotNew* slot);
	bool DropItem(int64 slotIndex);

	void SetInventorySize(int size);


	ABBBaseItem* GetItem(int64 slotIndex);

	bool UseItemInSlot(int64 index, AActor* instagatingActor);
	bool UseItemInQuickSlot(int64 index, AActor* instagatingActor);

		FORCEINLINE TArray<UBBInventorySlotNew*> GetQuickSlots() { return QuickSlots; }
		FORCEINLINE TArray<UBBInventorySlotNew*> GetInventorySlots() { return InventorySlots; }
		FORCEINLINE UBBInventorySlotNew* GetMouseSlot() { return MouseSlot; }
};
