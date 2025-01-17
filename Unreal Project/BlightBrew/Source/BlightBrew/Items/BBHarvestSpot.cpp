// Copyright © Too Many Eyes , 2022


#include "BBHarvestSpot.h"
#include "../Characters/Player/BBPlayerCharacter.h"
#include "../Inventory/BBInventoryComponent.h"
#include "../../Engine/Classes/Kismet/GameplayStatics.h"
#include "../../Engine/Classes/Particles/ParticleSystemComponent.h"
#include "../../../../../Engine/Plugins/FX/Niagara/Source/Niagara/Public/NiagaraComponent.h"

// Sets default values
ABBHarvestSpot::ABBHarvestSpot()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	IsInteractable = true;

	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh Component"));
	MeshComponent->SetStaticMesh(BeforeHarvestMesh);
	SetRootComponent(MeshComponent);

	/*Emitter = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Partical Emitter"));
	Emitter->SetupAttachment(RootComponent);*/
	
	//SetFocusText(FText::FromString("Harvest"));

	NiagaraComponent = CreateDefaultSubobject<UNiagaraComponent>(TEXT("NiagaraComponent"));
	NiagaraComponent->SetupAttachment(RootComponent);
}

void ABBHarvestSpot::OnFocus(AActor* InstigatingActor)
{
}

void ABBHarvestSpot::OnInteract(AActor* InstigatingActor)
{
	//Make sure the interactor is a player
	ABBPlayerCharacter* player = Cast<ABBPlayerCharacter>(InstigatingActor);

	if (player && IsInteractable)
	{
		UBBInventoryComponent* inventory = player->GetInventoryComponent();
		GenerateLiniarAmountPullList();
		int32 numItemsToSpawn = 0;
		if (WeightedAmountPullList.Num() > 0)
			numItemsToSpawn = WeightedAmountPullList[FMath::RandRange(0, WeightedAmountPullList.Num() - 1)];

		GenerateLiniarWeightedPullList();
		for (int32 i = 0; i < numItemsToSpawn; i++)
		{
			//Add random item to inventory
			int64 numToAdd = 1;
			TSubclassOf<ABBBaseItem> itemClass = WeightedItemPullList[FMath::RandRange(0, WeightedItemPullList.Num() - 1)];
			inventory->AddToInventory(itemClass.GetDefaultObject(), numToAdd);
		}

		//Change to other Mesh
		MeshComponent->SetStaticMesh(AfterHarvestMesh);
		IsInteractable = false;
		//Add a "(Harvested)" prefix to the focus text
		FocusText = FText::FromString("(Harvested) " + FocusText.ToString());
		//Play the harvest sound
		UGameplayStatics::PlaySoundAtLocation(GetWorld(), HarvestSound, GetActorLocation());
		//Disable the emitter, Niagara style
		//Emitter->Deactivate();
		NiagaraComponent->Deactivate();
		//Set A timer to reactivate
		FTimerHandle TimerHandle;
		GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &ABBHarvestSpot::ReActivate, CooldownTime, false);
		
	}
}

void ABBHarvestSpot::SetFocusText(FText text)
{
	FocusText = text;
}

FText ABBHarvestSpot::GetFocusText()
{
	return FocusText;
}

// Called when the game starts or when spawned
void ABBHarvestSpot::BeginPlay()
{
	Super::BeginPlay();

	SetFocusText(FText::FromString(HarvestSpotName));

}

// Called every frame
void ABBHarvestSpot::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ABBHarvestSpot::GenerateLiniarWeightedPullList()
{
	//Clear the list
	WeightedItemPullList.Empty();

	//Loop through the list of items and add them to the weighted list
	for (FBBHarvestItemData HarvestItemData : PullList)
	{
		for (int32 i = 0; i < HarvestItemData.HarvestableWeight; i++)
		{
			WeightedItemPullList.Add(HarvestItemData.ItemClass);
		}
	}
}

void ABBHarvestSpot::GenerateLiniarAmountPullList()
{
	//Clear the list
	WeightedAmountPullList.Empty();

	//Generate the weighted list
	for (int32 i = MinItemsToSpawn; i <= MaxItemsToSpawn; i++)
	{
		for (int32 j = MaxItemsToSpawn - (i-1); j > 0; j--)
		{
			WeightedAmountPullList.Add(i);
		}
	}
}

void ABBHarvestSpot::ReActivate()
{
	//Change to other Mesh
	MeshComponent->SetStaticMesh(BeforeHarvestMesh);
	IsInteractable = true;
	//Remove the "(Harvested)" prefix to the focus text
	FocusText = FText::FromString(FocusText.ToString().RightChop(11));
	//Enable the emitter, Niagara Style
	//Emitter->Activate();
	NiagaraComponent->Activate();
}

