// Copyright © Too Many Eyes , 2022

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "../Gameplay/BBInterface.h"
#include "../Items/BBBaseItem.h"
#include "BBCraftingStation.generated.h"


USTRUCT(Blueprintable, BlueprintType)
struct FBBCraftingRecipe
{
public:
    GENERATED_BODY()

	FBBCraftingRecipe() {}
	FBBCraftingRecipe(const FBBCraftingRecipe& Other) : ItemOne(Other.ItemOne), ItemTwo(Other.ItemTwo), ItemThree(Other.ItemThree), OutputItem(Other.OutputItem), isRepeat(Other.isRepeat) {}
    

	bool operator==(const FBBCraftingRecipe& B) const
	{
		return ItemOne == B.ItemOne && ItemTwo == B.ItemTwo && ItemThree == B.ItemThree && isRepeat == B.isRepeat;
	}

	bool operator!=(const FBBCraftingRecipe& B) const
	{
		return ItemOne != B.ItemOne || ItemTwo != B.ItemTwo || ItemThree != B.ItemThree || isRepeat == B.isRepeat;
	}
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
        TSubclassOf<ABBBaseItem> ItemOne;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
        TSubclassOf<ABBBaseItem> ItemTwo;
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
        TSubclassOf<ABBBaseItem> ItemThree;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
        TSubclassOf<ABBBaseItem> OutputItem;

    //*Check this if the recipe is a repeated, for example, for a throwable version of a consumable potion.
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
        bool isRepeat;

};

#if UE_BUILD_DEBUG
uint32 GetTypeHash(const FBBCraftingRecipe& Thing);
#else // optimize by inlining in shipping and development builds
FORCEINLINE uint32 GetTypeHash(const FBBCraftingRecipe& Thing)
{
    uint32 Hash = FCrc::MemCrc32(&Thing, sizeof(FBBCraftingRecipe));
    return Hash;
}
#endif

class UBBInventorySlotNew;
UCLASS(Blueprintable, BlueprintType)
class BLIGHTBREW_API ABBCraftingStation : public AActor, public IBBInterface
{
    GENERATED_BODY()

public:
    // Sets default values for this actor's properties
    ABBCraftingStation();

protected:
    // Called when the game starts or when spawned
    virtual void BeginPlay() override;

public:
    // Called every frame
    virtual void Tick(float DeltaTime) override;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Crafting")
        TMap<FBBCraftingRecipe, bool> CraftingBook;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
        UStaticMeshComponent* MeshComponent;
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
        TArray<UBBInventorySlotNew*> CraftingSlots;
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
        int64 CraftingSlotNum = 3;
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
        UBBInventorySlotNew* ProductSlot;

    bool Craft();

    //Interface Implementation
public:
    virtual void OnFocus(AActor* InstagatingActor) override;
    virtual void OnInteract(AActor* InstagatingActor) override;

    virtual void SetFocusText(FText text) override;
    virtual FText GetFocusText() override;

protected:
    FText m_focusText;

    
};
