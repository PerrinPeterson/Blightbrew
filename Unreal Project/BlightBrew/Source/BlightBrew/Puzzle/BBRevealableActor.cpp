// Copyright © Too Many Eyes , 2022


#include "BBRevealableActor.h"
#include "Components/StaticMeshComponent.h"
//Blightbrew


// Sets default values
ABBRevealableActor::ABBRevealableActor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RevealableMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("RevealableMesh"));
	RootComponent = RevealableMesh;

	RevealableMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	//Should hide the actor... We'll see
	RevealableMesh->SetHiddenInGame(true);

}

// Called when the game starts or when spawned
void ABBRevealableActor::BeginPlay()
{
	Super::BeginPlay();

}

void ABBRevealableActor::RevealActor()
{
	RevealableMesh->SetHiddenInGame(false);
	RevealableMesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
}

void ABBRevealableActor::HideActor()
{
	RevealableMesh->SetHiddenInGame(true);
	RevealableMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

// Called every frame
void ABBRevealableActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	/*if (bIsHidden && !RevealableMesh->bHiddenInGame)
	{
		HideActor();
	}
	else if (!bIsHidden && RevealableMesh->bHiddenInGame)
	{
		RevealActor();
	}*/

}

