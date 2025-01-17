// Copyright © Too Many Eyes , 2022


#include "BBEconomyManager.h"
#include "../Items/BBBaseItem.h"
#include "AssetRegistryModule.h"

UBBEconomyManager::UBBEconomyManager()
{
}

void UBBEconomyManager::BeginPlay()
{
	//Get All the blueprints inheriting from ABBBaseItem, and add them to the list of items that can be sold.

	TSubclassOf<UObject> itemClass = ABBBaseItem::StaticClass();

	FAssetRegistryModule& AssetRegistryModule = FModuleManager::LoadModuleChecked<FAssetRegistryModule>(TEXT("AssetRegistry"));

	FARFilter Filter;
	Filter.ClassNames.Add(UBlueprintGeneratedClass::StaticClass()->GetFName());
	//For in editor purposes
	Filter.ClassNames.Add(UBlueprint::StaticClass()->GetFName());
	
	Filter.bRecursiveClasses = true;
	Filter.ClassNames.Add(itemClass->GetFName());
	TArray<FAssetData> AssetData;
	AssetRegistryModule.Get().GetAssets(Filter, AssetData);

	if (AssetData.Num() != 0)
	{
		//UE_LOG(LogTemp, Warning, TEXT("Found Asset List..."));
		for (FAssetData& data : AssetData)
		{
			UBlueprint* blueprint = Cast<UBlueprint>(data.GetAsset());
			UBlueprintGeneratedClass* generatedBlueprint = Cast<UBlueprintGeneratedClass>(data.GetAsset());
			if (blueprint)
			{
				ABBBaseItem* item = Cast<ABBBaseItem>(blueprint->GeneratedClass.GetDefaultObject());
				if (item)
				{
					if (item->GetBaseValue() > 0)
					{
						ItemValueMap.Add(item, item->GetBaseValue());
					}
				}
			}
			else if (generatedBlueprint)
			{
				ABBBaseItem* item = Cast<ABBBaseItem>(generatedBlueprint->GetDefaultObject());
				if (item)
				{
					if (item->GetBaseValue() > 0)
					{
						ItemValueMap.Add(item, item->GetBaseValue());
					}
				}
			}
		}


		//generate 2 more maps, one for a max value, one for a min value.
		//this will stop the player from increasing the value of an item too much, or decreasing it too much.
		for (auto& item : ItemValueMap)
		{
			//Max value
			int64 maxValue = item.Value * 2;
			//Just to allow the player a little bit of leeway, we'll make the max value is at least 3 more than the base value.
			if (maxValue < item.Value + 3)
				maxValue = item.Value + 3;
			ItemMaxValueMap.Add(item.Key, maxValue);

			//Min value
			int64 minValue = item.Value / 2;
			//To punish the player for overselling even the most worthless items, we'll make the min value at least 3 less than the base value.
			if (minValue > item.Value - 3)
				minValue = item.Value - 3;
			//Make sure its over 0, though.
			if (minValue <= 0)
				minValue = 1;
			ItemMinValueMap.Add(item.Key, minValue);
		}

		//Another map for a percent multiplier, to make the value of an item change based on how much of it is sold
		//This should be updated once a day, rather than every time the player sells something.
		//Limits are described above, but the percent multiplier should be free from limitations. Meaning things can stay at double value for a while, and also at half value.
		for (auto& item : ItemValueMap)
		{
			//Percent multiplier
			float percentMultiplier = 1.0f;
			ItemPercentMultiplierMap.Add(item.Key, percentMultiplier);
		}
	}

}

int64 UBBEconomyManager::GetItemValue(ABBBaseItem* item)
{
	//Needs to take into account the value of the dollar too.
	return ItemValueMap[item];
}

void UBBEconomyManager::SoldItems(ABBBaseItem* item, int64 num)
{
	//Adds to the history of items sold
	if (SellingHistoryMap.Contains(item))
		SellingHistoryMap[item] += num;
	else
		SellingHistoryMap.Add(item, num);
}


//Call at the end of the day, to update the values of items.
void UBBEconomyManager::UpdateValues()
{
	/*if (SellingHistoryMap.Num() == 0)
		return;*/

	//We'll need the total amount of items sold.
	int64 totalItemsSold = 0;
	for (auto& item : SellingHistoryMap)
		totalItemsSold += item.Value;

	if (totalItemsSold >= ThresholdForEconomyToBeEffected)
	{
		if (SellingHistoryMap.Num() == 1)
		{

			//If the player has sold more than 10 of the same item, we'll punish them by making the value of that item go down.
			//This is to prevent the player from just selling the same item over and over again.
			//We'll also make sure the value doesn't go below the min value.
			//We'll drop the value by the punishment percent. As this is a percent, and not a multiplier, we'll need to divide by 100.
			float currentValueMultiplier = ItemPercentMultiplierMap[SellingHistoryMap.begin()->Key];
			float newValueMultiplier = currentValueMultiplier - (OnlyOneItemPunishment / 100);

			ItemPercentMultiplierMap[SellingHistoryMap.begin()->Key] = newValueMultiplier;
			ItemValueMap[SellingHistoryMap.begin()->Key] = ItemValueMap[SellingHistoryMap.begin()->Key] * newValueMultiplier;
		}

		//For the second scenario, the player sells multiple items.
		else if (SellingHistoryMap.Num() > 1)
		{
			//We'll need to sort the map by the amount of items sold.
			//We'll use 2 Arrays, so we can use index 0 and 1 to get the most sold and second most sold items.
			TArray<ABBBaseItem*> sortedMap;
			TArray<int64> sortedMapValues;
			for (auto& item : SellingHistoryMap)
			{
				//If the array is empty, we'll just add the item.
				if (sortedMap.Num() == 0)
				{
					sortedMap.Add(item.Key);
					sortedMapValues.Add(item.Value);
				}
				else
				{
					//We'll loop through the array, and find the first item that has a lower value than the current item.
					//We'll then insert the current item before that item.
					for (int i = 0; i < sortedMap.Num(); i++)
					{
						if (item.Value > sortedMapValues[i])
						{
							sortedMap.Insert(item.Key, i);
							sortedMapValues.Insert(item.Value, i);
							break;
						}
					}
				}
			}
			//Now we have the most sold item, and the second most sold item.
			//We'll drop the most sold item by the MostSoldMultiplierDecrease.
			//We'll drop the second most sold item by half that amount.
			float currentValueMultiplier = ItemPercentMultiplierMap[sortedMap[0]];
			float newValueMultiplier = currentValueMultiplier - (MostSoldPercentDecrease / 100);
			ItemPercentMultiplierMap[sortedMap[0]] = newValueMultiplier;

			//We'll drop the second most sold item by half that amount.
			currentValueMultiplier = ItemPercentMultiplierMap[sortedMap[1]];
			newValueMultiplier = currentValueMultiplier - (MostSoldPercentDecrease / 200);
			ItemPercentMultiplierMap[sortedMap[1]] = newValueMultiplier;


			//If theres a least sold item, we'll increase its value by the LeastSoldMultiplierIncrease.
			if (sortedMap.Num() > 2)
			{
				currentValueMultiplier = ItemPercentMultiplierMap[sortedMap[sortedMap.Num() - 1]];
				newValueMultiplier = currentValueMultiplier + (LeastSoldPercentIncrease / 100);
				ItemPercentMultiplierMap[sortedMap[sortedMap.Num() - 1]] = newValueMultiplier;
			}
			//If theres a second least sold item, we'll increase its value by half that amount.
			if (sortedMap.Num() > 3)
			{
				currentValueMultiplier = ItemPercentMultiplierMap[sortedMap[sortedMap.Num() - 2]];
				newValueMultiplier = currentValueMultiplier + (LeastSoldPercentIncrease / 200);
				ItemPercentMultiplierMap[sortedMap[sortedMap.Num() - 2]] = newValueMultiplier;
			}
		}
		//We'll bump the price of everything not sold by the StagnentItemBonus.
		for (auto& item : ItemValueMap)
		{
			if (!SellingHistoryMap.Contains(item.Key))
			{
				float currentValueMultiplier = ItemPercentMultiplierMap[item.Key];
				float newValueMultiplier = currentValueMultiplier + ((StagnentItemBonus / 100) * totalItemsSold);
				ItemPercentMultiplierMap[item.Key] = newValueMultiplier;
			}
		}
	}
	
	//Lightly effect the multiplier of x random items
	for (int i = 0; i < NumItemsToRandomlyEffect; i++)
	{
		//Make a tArray of all the items
		TArray<ABBBaseItem*> allItems;
		for (auto& item : ItemValueMap)
		{
			allItems.Add(item.Key);
		}
		//Pick a random item
		ABBBaseItem* randomItem = allItems[FMath::RandRange(0, allItems.Num() - 1)];
		
		//We'll pick a random percent to change the multiplier by
		float randomPercent = FMath::RandRange(MinRandomFluctuation, MaxRandomFluctuation);
		float currentValueMultiplier = ItemPercentMultiplierMap[randomItem];
		float newValueMultiplier = currentValueMultiplier + (randomPercent / 100);
		ItemPercentMultiplierMap[randomItem] = newValueMultiplier;
	}

	//Loop through the maps and set the values based on the new multiplier
	for (auto& item : ItemValueMap)
	{
		item.Value = item.Value * ItemPercentMultiplierMap[item.Key];
		if (item.Value < ItemMinValueMap[item.Key])
			item.Value = ItemMinValueMap[item.Key];
		if (item.Value > ItemMaxValueMap[item.Key])
			item.Value = ItemMaxValueMap[item.Key];
	}
}

void UBBEconomyManager::GetRandomItems(int32 num, TArray<ABBBaseItem*>& items)
{
	//Use the internal map to get random items, create a TArray of all the items, then pick x random items from that array.
	TArray<ABBBaseItem*> allItems;
	for (auto& item : ItemValueMap)
	{
		allItems.Add(item.Key);
	}
	for (int i = 0; i < num; i++)
	{
		items.Add(allItems[FMath::RandRange(0, allItems.Num() - 1)]);
	}
}

void UBBEconomyManager::GetAllItems(TArray<TSubclassOf<ABBBaseItem>>& items)
{
	for (auto& item : ItemValueMap)
	{
		TSubclassOf<ABBBaseItem> itemClass = item.Key->GetClass();
		items.Add(itemClass);
	}
}
