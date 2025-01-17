// Copyright © Too Many Eyes , 2022 - 2023
/*Rewards Chest, Designed by Perrin Peterson, 04/02/2023
* This actor is a shop element, it's main purpose is to allow the player to interface with the shop. It will provide the UI with the nessisary information.
* This Actor needs to;
*	- Be interactable
*	- Have a UI with several pages
*		- The first page is the management page, allowing the player to open the shop.
*		- The second is the Catalogue, allowing the player to set items they've stocked on the shelves.
*		- The third is the Ordering page, allowing the player to buy bottles for crafting
*		- The last is the history page, allowing the player to see up to 50 previous sales.
*/
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Blightbrew/Gameplay/BBInterface.h"
#include "BBShopBook.generated.h"

UCLASS()
class BLIGHTBREW_API ABBShopBook : public AActor, public IBBInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABBShopBook();

	//Interactable
	virtual void OnFocus(AActor* InstigatingActor) override;
	virtual void OnInteract(AActor* InstigatingActor) override;
	UFUNCTION(NotBlueprintable)
		virtual void SetFocusText(FText text) override;
	UFUNCTION(NotBlueprintable)
		virtual FText GetFocusText() override;

	//Components
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BlightBrew|Shop|Book") //Needs to be a skeletal mesh for the animations to take effect
		class UStaticMeshComponent* BookMesh;
	
	//Properties
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BlightBrew|Shop|Book") //Needs to be visible for the animations to take effect
		bool bIsBeingUsed;

	//References
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BlightBrew|Shop|Book") //The shop that this book belongs to
		TSoftObjectPtr<class ABBShopManager> Shop;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BlightBrew|Shop|Book") //The UI that this book will open, this is a brand new idea to instead control the UI from this class.
		class UBBShopBookWidget* ShopBookUI;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	FText m_focusText;

};
