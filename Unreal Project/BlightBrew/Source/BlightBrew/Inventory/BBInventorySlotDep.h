// Copyright © Too Many Eyes , 2022

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BBInventorySlotDep.generated.h"

class ABBBaseItem;
UCLASS()
class BLIGHTBREW_API ABBInventorySlot : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ABBInventorySlot();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	bool Increment(int64& num);
	bool Decrement(int64& num);

	void Reset();

	bool SetToItem(ABBBaseItem* item, int64& num);

	ABBBaseItem* GetItem() { return ItemClass.GetDefaultObject(); }
	FString GetItemName();

	int64 GetStackSize() { return StackSize; }
	int64& GetStackSizeRef() { return StackSize; }
	int64 GetMaxStackSize() { return MaxStackSize; }
	TSubclassOf<ABBBaseItem> GetItemClass() { return ItemClass; }

	bool UseItem(AActor* instagatingActor);

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		int64 StackSize;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		int64 MaxStackSize;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		ABBBaseItem* Item;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		TSubclassOf<ABBBaseItem> ItemClass;

};