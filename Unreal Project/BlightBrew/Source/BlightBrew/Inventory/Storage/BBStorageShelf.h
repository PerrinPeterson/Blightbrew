// Copyright © Too Many Eyes , 2022 - 2023

#pragma once

#include "CoreMinimal.h"
#include "BBStorageContainer.h"
#include "BBStorageShelf.generated.h"

/**
 * 
 */
class UBoxComponent;
class UBBInventorySlotNew;
UCLASS(Blueprintable)
class BLIGHTBREW_API ABBStorageShelf : public ABBStorageContainer
{
	GENERATED_BODY()
	
public:
	ABBStorageShelf();

	//Interactable Related
	virtual void OnFocus(AActor* InstigatingActor) override;
	virtual void OnInteract(AActor* InstigatingActor) override;

	FORCEINLINE virtual void SetFocusText(FText text) override { FocusText = text; }
	FORCEINLINE virtual FText GetFocusText() override { return FocusText; }
	FORCEINLINE TArray<UBBInventorySlotNew*> GetStorageSlots() { return StorageSlots; }
	FORCEINLINE void SetNeedsUpdate(bool b) { bNeedsUpdate = b; }

	//Storage Related
	virtual TArray<ABBBaseItem*> GetItems() override;
	virtual TArray<TSubclassOf<ABBBaseItem>> GetItemClasses() override;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		TArray<UStaticMeshComponent*> StorageSlotMeshs;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		TArray<UBoxComponent*> StorageSlotBoundsBoxs;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		TArray<UBBInventorySlotNew*> StorageSlots;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		int32 storageSlotNum = 6;
protected:
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;
	
	/*UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Focus)
		FText FocusText;*/
	bool bNeedsUpdate = false;
};
