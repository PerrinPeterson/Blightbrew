// Copyright © Too Many Eyes , 2022
/*The shell for an AI designed by Perrin, Created 10-29-2023 by Perrin.
* To be developed by Xander
*
* The AI's primary use is to walk around the shop and buy items. This is a simple shell without pathing logic.
* This AI can;
*	- Use the shops list of Storage Containers to find items to buy.
*	- Adds the items to its inventory.
*	- Sparkles when the AI has found the item it(s) wants to buy.
*	- Can be interacted with by the player to buy items, giving the player money
*	- Alter it's shopping list based on the ShopperID it is given.
*
* In this shell, there is also logic to be able to barter with the AI. It's not usable without UI, but the logic is there.
*
* Unique to the shell, it will have an IsActivated bool, this bool will tell the AI to start shopping. Once the AI has run through all the steps
* it will reset itself and wait for the bool to be set to true again. The shop will have a trigger that will set the bool to true when the player
* interacts with it, for now.
*/
#pragma once

#include "CoreMinimal.h"
#include "BlightBrew/Characters/AI/BBAICharacterBase.h"
#include "../Gameplay/BBInterface.h"
#include "BBShopper.generated.h"

class ABBStorageContainer;
//Forward Declarations
class ABBBaseItem;

UENUM(BlueprintType)
enum class EBBShopperTraits : uint8
{
	
	/** Occasionally drops items on the floor */
	MESSY, 
	/** Will try to buy items for as little as possible, even items that are not on the list */
	CHEAP, 
	/** Has a chance to not buy anything at all */ 
	WINDOWSHOPPER, 
	/** Will buy items that are not on the list */
	BORED, 
	/** Maxes out the Spendy stat, inceases cost effect. */
	WEALTHY, 
	/** Minimizes the Spendy stat */
	POOR, 
	/** Will increase the quantity of items the AI wants to buy by 2 each */
	MONTHLY, 

	NUM		UMETA(Hidden) //This is used to get the number of traits
};

USTRUCT(BlueprintType)
struct FBBShopperID
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BlightBrew|Shopper")
		FString ShopperName;

	//Map of items, with their quantity, that the AI wants to buy
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BlightBrew|Shopper")
		TMap<TSubclassOf<ABBBaseItem>, int32> ShoppingList;

	/*Social stats
	* These stats will be used for a number of things, but the main use is to determine how much the AI will haggle with the player.*/
	
	/** The chance the AI wants to buy more or fewer items, max is 100 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BlightBrew|Shopper")
		int32 Bulk = 0;

	/** The chance the AI wants to spend more or less money, max is 100 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BlightBrew|Shopper")
		int32 Spendy = 0;
	
	/** The effect that the cost has on the AI's decision to buy the item, max is 100 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BlightBrew|Shopper")
		int32 CostEffect = 0;
	
	/** The AI's base resistance to haggling max is 100 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BlightBrew|Shopper")
		int32 BarterResistance = 0;
	
	/** The shoppers traits, these will be used to determine how the AI will interact with the player and the shop */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BlightBrew|Shopper")
		TMap<EBBShopperTraits, bool> Traits;

	/** Happiness, if this drops below 0 the AI will leave the shop, if it hits 100 the AI will become a returning customer */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BlightBrew|Shopper")
		int32 Happiness = 100;

	/** A reference to the shop that the AI is in */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "BlightBrew|Shopper")
		class ABBShopManager* Shop;

	/** A list of Shelves that the AI has visited */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "BlightBrew|Shopper")
		TArray<ABBStorageContainer*> VisitedShelves;

		
	
	
};

UCLASS()
class BLIGHTBREW_API ABBShopper : public ABBAICharacterBase
{
	GENERATED_BODY()
public:
		//The mesh for the shell
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Blightbrew|Shopper", meta = (AllowPrivateAccess = "true"))
		class UStaticMeshComponent* ShopperMesh;

	//The ID for the shopper, this will be used to determine what the AI will buy
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BlightBrew|Shopper")
		FBBShopperID ShopperID;


public:
	// Sets default values for this character's properties
	ABBShopper();
	virtual void Init() override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	//Interface Requirements
	FORCEINLINE virtual void SetFocusText(FText text) override { FocusText = text; }

	FORCEINLINE virtual FText GetFocusText() override { return FocusText; }
	virtual void OnFocus(AActor* InstigatingActor) override;
	virtual void OnInteract(AActor* InstigatingActor) override;

	//Shopper Specific
	//Handles bartering the items value
	bool Barter(int64 newValue, int64 shopValue);
	bool Sell();
	
	void CheckShelf();
	bool WantsItem(TSubclassOf<ABBBaseItem> item);
	void PullFromInventory(class UBBInventorySlotNew* storageSlot);

	bool Interact();

	FORCEINLINE void AddVisitedShelf(ABBStorageContainer* shelf) { ShopperID.VisitedShelves.Add(shelf); }
	
	
	//Shoppers Inventory Component
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "BlightBrew|Shopper")
		class UBBInventoryComponent* InventoryComponent;

	bool m_isWaiting;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BlightBrew|Shopper")
		bool m_hasShopped;

};
