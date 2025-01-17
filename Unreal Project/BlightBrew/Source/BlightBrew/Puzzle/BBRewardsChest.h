// Copyright © Too Many Eyes , 2022 - 2023
/*Rewards Chest, Designed by Perrin Peterson, 03/29/2023
* This actor is a puzzle element and serves as a rewards chest for the player.
* This Actor needs to;
*  - Have a revealable mesh, much like the Revealable Actors, but with different logic
*  - Have a particle effect that plays while it's interactable
*  - Have the ability to add;
*   - A random item to the player's inventory
*   - A random amount of gold to the player's inventory
*   - A predetermined item to the player's inventory
*   - A predetermined amount of gold to the player's inventory
*   - The 'Knowledge' to craft an item
*/

#pragma once
//Unreal
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
//Blightbrew
#include "../Gameplay/BBInterface.h"
//Generated
#include "BBRewardsChest.generated.h"

class ABBRockTriggerSpot;
class ABBBaseItem;
UCLASS()
class BLIGHTBREW_API ABBRewardsChest : public AActor, public IBBInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABBRewardsChest();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//Interactable
	virtual void OnFocus(AActor* InstigatingActor) override;
	virtual void OnInteract(AActor* InstigatingActor) override;
	UFUNCTION(NotBlueprintable)
		virtual void SetFocusText(FText text) override;
	UFUNCTION(NotBlueprintable)
		virtual FText GetFocusText() override;
	

	//Loot Variables
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BlightBrew|Puzzle|Loot")
		bool bAddRandomItem;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BlightBrew|Puzzle|Loot")
		int32 MinRandomItems;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BlightBrew|Puzzle|Loot")
		int32 MaxRandomItems;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BlightBrew|Puzzle|Loot")
		bool bAddRandomGold;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BlightBrew|Puzzle|Loot")
		int32 MinGold;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BlightBrew|Puzzle|Loot")
		int32 MaxGold;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BlightBrew|Puzzle|Loot")
		TArray <TSubclassOf<ABBBaseItem>> PredeterminedItemsToAdd;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BlightBrew|Puzzle|Loot")
		int32 PredeterminedGoldToAdd;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BlightBrew|Puzzle|Loot")
		TArray <TSubclassOf<ABBBaseItem>> CraftedItemKnowledgeToAdd;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BlightBrew|Puzzle|Loot")
		float LootThrowTime;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BlightBrew|Puzzle|Loot")
		float LootThrowForce;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BlightBrew|Puzzle|Loot")
		float LootThrowAngle;
	
	//Puzzle Variables
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BlightBrew|Puzzle")
		TArray<TSoftObjectPtr<ABBRockTriggerSpot>> PuzzleSpots;

	//Component Variables
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "BlightBrew|Puzzle|Components")
		class UStaticMeshComponent* Mesh;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "BlightBrew|Puzzle|Components")
		class UNiagaraComponent* ParticleEffect;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BlightBrew|Puzzle|Components") //Sound effect to play when the player interacts with the chest.
		class USoundBase* InteractSound;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BlightBrew|Puzzle|Components") //Sound effect when the chest is revield.
		class USoundBase* RevieledSound;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "BlightBrew|Puzzle|Components") //Particle effect to play when the chest is revealed.
		class UNiagaraComponent* RevieledParticleEffect;

	//Other Functions
	//Throws loot up into the air.
	void ThrowLoot();
	void DeactivateBurst();

protected:
	FText m_focusText;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BlightBrew|Puzzle")
		bool bIsSolved = false;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "BlightBrew|Puzzle")
		bool bIsInteractable = false;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "BlightBrew|Puzzle")
		bool bHasBeenLooted = false;
	int32 m_throwQueNum;
	TArray <ABBBaseItem*> m_lootToThrow;
	
};
