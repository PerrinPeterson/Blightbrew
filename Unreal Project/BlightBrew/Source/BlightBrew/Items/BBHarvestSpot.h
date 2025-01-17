// Copyright © Too Many Eyes , 2022

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "../Gameplay/BBInterface.h"
#include "BBBaseItem.h"
#include "BBHarvestSpot.generated.h"


USTRUCT(BlueprintType)
struct BLIGHTBREW_API FBBHarvestItemData
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Harvest Item Data")
		TSubclassOf<ABBBaseItem> ItemClass;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Harvest Item Data")
		int32 HarvestableWeight;
};


class UNiagaraComponent;
UCLASS()
class BLIGHTBREW_API ABBHarvestSpot : public AActor, public IBBInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABBHarvestSpot();
	
	//The Visible Mesh
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Harvest Spot")
		UStaticMeshComponent* MeshComponent;

	//The Before Harvest Mesh
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Harvest Spot")
		UStaticMesh* BeforeHarvestMesh;
	
	//The After Harvest Mesh
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Harvest Spot")
		UStaticMesh* AfterHarvestMesh;
	
	//Minimum number of items to spawn
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Harvest Spot")
		int32 MinItemsToSpawn;
	
	//Maximum number of items to spawn
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Harvest Spot")
		int32 MaxItemsToSpawn;

	//The list of items that can be pulled from this harvest spot
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Harvest Spot")
		TArray<FBBHarvestItemData> PullList;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Harvest Spot")
		FString HarvestSpotName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Harvest Spot")
		FString HarvestSpotDescription;
	
	//Havest Sound
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Harvest Spot")
		USoundBase* HarvestSound;

	//This emitter sadly doesn't work with the particle system the designers made
	// FIX: create a "Spawn Point" component, and spawn the Niagara particle system there
	//Emitter
	/*UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Harvest Spot")
		UParticleSystemComponent* Emitter;*/

	//Niagara component
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Harvest Spot")
		UNiagaraComponent* NiagaraComponent;
	

	

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Harvest Spot")
		int32 CooldownTime;
	
	
public:
	
	//IBBInterface Overrides
	virtual void OnFocus(AActor* InstigatingActor) override;
	
	virtual void OnInteract(AActor* InstigatingActor) override;

	UFUNCTION(NotBlueprintable)
		virtual void SetFocusText(FText text) override;

	UFUNCTION(NotBlueprintable)
		virtual FText GetFocusText() override;
	

protected:
	
	FText FocusText;
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	TArray<int32> WeightedAmountPullList;
	TArray<TSubclassOf<ABBBaseItem>> WeightedItemPullList;

	bool IsInteractable;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//Fills the Weighted Item Pull List with a list of items that can be randomly pulled from to simulate a rarity system.
	void GenerateLiniarWeightedPullList();

	void GenerateLiniarAmountPullList();

	UFUNCTION()
	void ReActivate();
};
