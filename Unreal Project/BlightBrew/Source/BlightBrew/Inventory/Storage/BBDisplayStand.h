// Copyright © Too Many Eyes , 2022

#pragma once

#include "CoreMinimal.h"
#include "BBStorageContainer.h"
#include "BBDisplayStand.generated.h"

/**
 * 
 */
class UBBInventorySlotNew;
class UBoxComponent;
UCLASS(Blueprintable)
class BLIGHTBREW_API ABBDisplayStand : public ABBStorageContainer
{
	GENERATED_BODY()
	
public:
	ABBDisplayStand();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		UStaticMeshComponent* StorageSlotMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		UBoxComponent* StorageSlotBoundsBox;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		UBBInventorySlotNew* StorageSlot;

	TArray<ABBBaseItem*> GetItems() override;
	TArray<TSubclassOf<ABBBaseItem>> GetItemClasses() override;
	virtual void OnInteract(AActor* InstagatingActor) override;
	virtual void OnFocus(AActor* InstigatingActor) override;

	FORCEINLINE virtual void SetFocusText(FText text) override { FocusText = text; }

	FORCEINLINE virtual FText GetFocusText() override { return FocusText; }

	virtual void Tick(float DeltaTime) override;
	virtual void BeginPlay() override;
};
