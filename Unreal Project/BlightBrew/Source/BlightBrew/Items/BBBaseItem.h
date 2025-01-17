// Copyright © Too Many Eyes , 2022

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "../Gameplay/BBInterface.h"
#include "BBBaseItem.generated.h"

UENUM()
enum class BBControlType
{
    CONSUME,
    THROW
};

//UPDATE TODO: Give the player two methods of dropping an item, A) pressing Q while "holding" the item. Option B) clicking outside the window in the UI (Needs to happen when Xander is done fixing UI.
//Semi-tick

class UProjectileMovementComponent;
UCLASS()
class BLIGHTBREW_API ABBBaseItem : public AActor, public IBBInterface
{
    GENERATED_BODY()

public:
    // Sets default values for this actor's properties
    ABBBaseItem();

    UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"), Category = "BlightBrew|Item")
        UStaticMeshComponent* MeshComponent;

    //Physics component
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"), Category = "BlightBrew|Item")
		UProjectileMovementComponent* ProjectileMovementComponent;
		

protected:
    // Called when the game starts or when spawned
    virtual void BeginPlay() override;

public:
    // Called every frame
    virtual void Tick(float DeltaTime) override;

public:
    UFUNCTION(NotBlueprintable)
        virtual void SetFocusText(FText text) override;

    UFUNCTION(NotBlueprintable)
        virtual FText GetFocusText() override;


    UFUNCTION(BlueprintCallable, Category = ItemDetails)
        UTexture2D* GetIcon() { return Icon; }
    UFUNCTION(BlueprintCallable, Category = ItemDetails)
        FString GetItemName() { return Name; }
    UFUNCTION(BlueprintCallable, Category = ItemDetails)
        FString GetItemDescription() { return Description; }
	UFUNCTION(BlueprintCallable, Category = ItemDetails)
		int32 GetBaseValue() { return BaseValue; }

public:

    virtual void OnFocus(AActor* InstigatingActor) override;
    virtual void OnInteract(AActor* InstigatingActor) override;
    virtual bool OnUse(BBControlType controlType, AActor* instagatingActor);

    int64 GetMaxStackSize() { return MaxStackSize; }


protected:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"), Category = "BlightBrew|Inventory")
        UTexture2D* Icon;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"), Category = "BlightBrew|Inventory")
        int64 MaxStackSize;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"), Category = "BlightBrew|Inventory")
        FString Name;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"), Category = "BlightBrew|Inventory")
        FString Description;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Focus)
        FText FocusText;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"), Category = "BlightBrew|Inventory")
		int32 BaseValue;

    //TODO: make a map of item ID's that need to be registered on runtime.
};
