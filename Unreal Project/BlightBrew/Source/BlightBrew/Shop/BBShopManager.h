// Copyright © Too Many Eyes , 2022
/*The Shop Manager, Designed and Designed by Perrin Peterson on 01/29/2023
* The Shop Manager is the main class for the shop system. It is responsible for;
*	- Spawning shoppers
*	- Assigning shoppers a random ShopperID
*	- Getting the storage containers in it's area
*	- Keeping an array of the shelves, their contents, their locations, and their prices
*	- Working in tandam with an Economy Manager to determine the value of items
*
* As this version is going to have some debugging properties, while the shop is active, it will work with a single shopper, and will not spawn new ones.
* The shop will eventually will spawn shoppers based on a combination of a 'busyness' stat, and the popularity of the shop.
*/
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
//Blightbrew
#include "BBEconomyManager.h"
#include "BBShopper.h"
#include "BBShopManager.generated.h"

//Forward Declarations
class UBoxComponent;
class ABBStorageContainer;
class ABBBaseItem;
class ABBPlayerCharacter;


UCLASS()
class BLIGHTBREW_API ABBShopManager : public AActor
{
	GENERATED_BODY()

		//Area of the shop that the shoppers will exist in, and the area the shop will search for storage containers
	UPROPERTY(VisibleAnywhere, Category = "BlightBrew|Shop")
		class UBoxComponent* ShopArea;

#pragma region To be implemented
	//The area that the shoppers will spawn in
	UPROPERTY(VisibleAnywhere, Category = "BlightBrew|Shop")
		class UBoxComponent* SpawnArea;

	//The area that the shoppers will despawn in
	UPROPERTY(VisibleAnywhere, Category = "BlightBrew|Shop")
		class UBoxComponent* DespawnArea;

	//The area the shoppers will go to when they are done shopping and waiting for the player to interact with them
	UPROPERTY(VisibleAnywhere, Category = "BlightBrew|Shop")
		class UBoxComponent* WaitingArea;
#pragma endregion

	//The list of storage containers that the shop will search for items to buy
	UPROPERTY(VisibleAnywhere, Category = "BlightBrew|Shop")
		TArray<ABBStorageContainer*> StorageContainers;

	//The list of shoppers that the shop has spawned
	UPROPERTY(VisibleAnywhere, Category = "BlightBrew|Shop")
		TArray<ABBShopper*> Shoppers;

	//A list of pregenerated ShopperIDs that the shop can use to assign to shoppers, so we can add in custom shoppers
	UPROPERTY(EditAnywhere, Category = "BlightBrew|Shop")
		TArray<FBBShopperID> CustomShopperIDs;

	//A list of Return ShopperIDs that the shop can use to assign to shoppers, this is for random shoppers who happyness is above a certain threshold
	UPROPERTY(VisibleAnywhere, Category = "BlightBrew|Shop")
		TArray<FBBShopperID> ReturnShopperIDs;

	//The MAX number of shoppers that the shop can have at once
	UPROPERTY(EditAnywhere, Category = "BlightBrew|Shop")
		int32 MaxShoppers = 5;

	//The items the shoppers may look for, this is a list manually built, as making a system to generate this list would be too complex for the time we have
	UPROPERTY(EditAnywhere, Category = "BlightBrew|Shop")
		TArray<TSubclassOf<ABBBaseItem>> ShopItems;

	//Makes Shoppers spawn more regularilly
	UPROPERTY(EditAnywhere, Category = "BlightBrew|Shop")
		float Buisiness = 5.0f;

	//If the shop is open
	UPROPERTY(EditAnywhere, Category = "BlightBrew|Shop")
		bool IsOpen = false;

	//The chances of a shopper being a return shopper
	UPROPERTY(EditAnywhere, Category = "BlightBrew|Shop")
		uint64 ReturnShopperChance = 5;
	
	//The Chances of a shopper being a custom shopper
	UPROPERTY(EditAnywhere, Category = "BlightBrew|Shop")
		uint64 CustomShopperChance = 5;

	//The Chances of a shopper being a random shopper
	UPROPERTY(EditAnywhere, Category = "BlightBrew|Shop")
		uint64 RandomShopperChance = 90;

	//An array of Names that the shop can use to generate random shoppers
	UPROPERTY(EditAnywhere, Category = "BlightBrew|Shop")
		TArray<FString> ShopperNames;
	
	//The Internal map of items and their prices, this will be set by the shop book UI, and the items list wll expand based on the items in the storages
	UPROPERTY(VisibleAnywhere, Category = "BlightBrew|Shop")
		TMap<TSubclassOf<ABBBaseItem>, int64> ItemCatalog;

	//The items the shoppers may look for, this is a list manually built, as making a system to generate this list would be too complex for the time we have
	UPROPERTY(EditAnywhere, Category = "BlightBrew|Shop")
		TSubclassOf<ABBShopper> ShopperClass;

	UPROPERTY(EditAnywhere, Instanced, Category = "BlightBrew|Shop")
		UBBEconomyManager* EconomyManager;


	FTimerHandle SpawningTimerHandle;
	FTimerHandle TimerTimerHandle;

	float SpawningTimer;

#pragma region Debug
	//Click this in the editor to ask the shop to "open"
	UPROPERTY(EditAnywhere, Category = "BlightBrew|Shop")
		bool HasCheckedArea = false;
#pragma endregion
	
	

public:
	// Sets default values for this actor's properties
	ABBShopManager();

	//Get all the storage containers in the shop area
	void FindStorageContainers();

	//Called when the timer says its time to spawn a shopper
	void SpawnShopper();

	void DespawnShopper(ABBShopper* shopper);
	
	//Generates a random shopper ID
	FBBShopperID GenerateRandomShopperID();
	void GenerateShoppingList(FBBShopperID& ShopperID);
	int GetShopItemValue(TSubclassOf<ABBBaseItem> item);
	void SetShopItemValue(TSubclassOf<ABBBaseItem> item, int64 value);
	//Getters
	FORCEINLINE TArray<ABBStorageContainer*> GetStorageContainerArray() { return StorageContainers; }
	FORCEINLINE UBoxComponent* GetWaitingArea() { return WaitingArea; }
	FORCEINLINE UBoxComponent* GetDespawnArea() { return DespawnArea; }
	FORCEINLINE UBBEconomyManager* GetEconomyManager() { return EconomyManager; }
	FORCEINLINE TMap<TSubclassOf<ABBBaseItem>, int64> GetItemCatalog() { return ItemCatalog; }
	
	void BuyItem(ABBPlayerCharacter* player, TSubclassOf<ABBBaseItem> item, int64 amount, int64 costPerUnit);

	
#pragma region Debug, to be removed
	//Get the shoppers in the area
	void FindShoppers();

#pragma endregion
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void CheckSpawn();

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void GetCosts(TSubclassOf<ABBBaseItem> item, int64& shopPrice, int64& econManagerPrice);
	void SetShopOpenStatus(bool status) { IsOpen = status; }
	bool GetShopOpenStatus() { return IsOpen; }


};
