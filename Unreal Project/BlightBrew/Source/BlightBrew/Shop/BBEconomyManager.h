// Copyright © Too Many Eyes , 2022

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "BBEconomyManager.generated.h"

/*Economy Manager, Designed by Perrin Peterson, 02/16/2023
* This class is a singleton that will be used to manage the economy of the game.
* This class needs to;
*	- Have an item passed to it, pre selling, and return the value of the item, based on the global currency value and the item's value
*	- Have an item passed to it, post selling, and effect the value of that item based on overselling.
*	- Have an item passed to it, post selling, and effect the value of that item based on underselling.
*	- Populate a list of items that can be sold, and a list of items that can be bought in the shop book, by taking all the blueprints in a specific folder, and adding them to the list.
*/
class ABBBaseItem;
UCLASS(EditInlineNew, BlueprintType, Blueprintable)
class BLIGHTBREW_API UBBEconomyManager : public UObject
{
	GENERATED_BODY()
	
public:
	//Construct
	UBBEconomyManager();

	void BeginPlay();
	
	

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Economy | Debug")
		TMap<ABBBaseItem*, int64> ItemValueMap;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Economy | Debug")
		TMap<ABBBaseItem*, int64> ItemMaxValueMap;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Economy | Debug")
		TMap<ABBBaseItem*, int64> ItemMinValueMap;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Economy | Debug")
		TMap<ABBBaseItem*, float> ItemPercentMultiplierMap;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Economy | Debug")
		TMap<ABBBaseItem*, int64> SellingHistoryMap;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Economy | Customise")
		float GolbalCurrencyValue = 0.5;
	
	//*If the player only sells 1 type of item all day, the multiplier will decrease by this amount.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Economy | Customise")
		int64 OnlyOneItemPunishment = 100;

	//*The amount of the one item the player needs to sell, in order for the economy to be effected, otherwise random fluctuations will be the only thing that happens.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Economy | Customise")
		int64 ThresholdForEconomyToBeEffected = 10;

	//*At the end of every day, this number of items will have their value randomly changed by a random amount between the min and max values.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Economy | Customise")
		int64 NumItemsToRandomlyEffect = 3;
	
	//*Percent value
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Economy | Customise")
		int64 MaxRandomFluctuation = 30;
	
	//*Percent value
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Economy | Customise")
		int64 MinRandomFluctuation = -10;

	//*If an item isn't sold, how much percent should it go up per other item sold.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Economy | Customise")
		int64 StagnentItemBonus = 1;

	//*The percent decrease for the most sold item in a day.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Economy | Customise")
		int64 MostSoldPercentDecrease = 30;

	//*The percent decrease for the least sold item in a day.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Economy | Customise")
		int64 LeastSoldPercentIncrease = 30;

#pragma region Debug
	//*Click the checkbox to refresh item values.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Economy | Debug")
		bool RefreshItemValues = false;
#pragma endregion

public:
	int64 GetItemValue(ABBBaseItem* item);
	void SoldItems(ABBBaseItem* item, int64 num);
	//Should only be called once a day, preferably.
	void UpdateValues();
	//For other classes to call, to get a few items, as this class has ALL the items in the game.
	void GetRandomItems(int32 num, TArray<ABBBaseItem*>& items);
	//For other classes to call, to get all the items, as this class has ALL the items in the game.
	void GetAllItems(TArray<TSubclassOf<ABBBaseItem>>& items);
	
};
