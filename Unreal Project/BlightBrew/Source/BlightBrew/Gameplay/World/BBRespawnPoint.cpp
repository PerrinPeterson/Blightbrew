// Copyright © Too Many Eyes , 2022 - 2023


#include "BBRespawnPoint.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
ABBRespawnPoint::ABBRespawnPoint()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	Mesh->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	RootComponent = Mesh;
	Mesh->SetHiddenInGame(true);
	
}

// Called when the game starts or when spawned
void ABBRespawnPoint::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABBRespawnPoint::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

