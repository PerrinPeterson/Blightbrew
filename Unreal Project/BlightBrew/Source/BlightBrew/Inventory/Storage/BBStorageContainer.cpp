// Copyright © Too Many Eyes , 2022


#include "BBStorageContainer.h"

// Sets default values
ABBStorageContainer::ABBStorageContainer()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BodyMesh = CreateDefaultSubobject<UStaticMeshComponent>("Body Mesh");
	SetRootComponent(BodyMesh);

}

void ABBStorageContainer::OnFocus(AActor* InstigatingActor)
{
	//Super::OnFocus(InstigatingActor);
}

void ABBStorageContainer::OnInteract(AActor* InstigatingActor)
{

}

TArray<ABBBaseItem*> ABBStorageContainer::GetItems()
{
	return TArray<ABBBaseItem*>();
}

TArray<TSubclassOf<ABBBaseItem>> ABBStorageContainer::GetItemClasses()
{
	return TArray<TSubclassOf<ABBBaseItem>>();
}

// Called when the game starts or when spawned
void ABBStorageContainer::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABBStorageContainer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

