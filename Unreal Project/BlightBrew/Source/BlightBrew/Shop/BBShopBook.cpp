// Copyright © Too Many Eyes , 2022 - 2023


#include "BBShopBook.h"

//Unreal Includes
#include "Components/StaticMeshComponent.h"
//BlightBrew Includes
#include "BlightBrew/Characters/Player/BBPlayerCharacter.h"
#include "BlightBrew/Shop/BBShopManager.h"
#include "BlightBrew/UI/BBHUD.h"
#include "BlightBrew/UI/Shop/BBShopBookWidget.h"

// Sets default values
ABBShopBook::ABBShopBook()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BookMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BookMesh"));
	SetRootComponent(BookMesh);


	
}

void ABBShopBook::OnFocus(AActor* InstigatingActor)
{
}

void ABBShopBook::OnInteract(AActor* InstigatingActor)
{
	ABBPlayerCharacter* player = Cast<ABBPlayerCharacter>(InstigatingActor);
	if (player == nullptr)
		return;
	ShopBookUI = player->GetHUD()->GetShopBookWidget();
	if (Shop == nullptr)
	{
		return; //We 'Could' Search for the shop, but that would be a lot of work for a very small chance of it being nessisary.
	}
	//For debug purposes, if the shop hasn't got a UI, open/close the shop
	if (ShopBookUI == nullptr)
	{
		if (Shop->GetShopOpenStatus())
			Shop->SetShopOpenStatus(false);
		else
			Shop->SetShopOpenStatus(true);
		return;
	}

	//Hide the world widgets, show the shop book UI, disable player controls, all that jazz
	{
		bIsBeingUsed = true;
		//player->GetHUD()->SetIsMenuOpen(true);
		ShopBookUI->SetOwningBook(this);
		ShopBookUI->Toggle();
	}

}

void ABBShopBook::SetFocusText(FText text)
{
	m_focusText = text;
}

FText ABBShopBook::GetFocusText()
{
	return m_focusText;
}

// Called when the game starts or when spawned
void ABBShopBook::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void ABBShopBook::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

