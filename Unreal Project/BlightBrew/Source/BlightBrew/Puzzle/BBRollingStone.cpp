// Copyright © Too Many Eyes , 2022


#include "BBRollingStone.h"
#include "../../Engine/Classes/Kismet/GameplayStatics.h"
#include "Components/SphereComponent.h"
//Blightbrew
#include "../Characters/Player/BBPlayerCharacter.h"
#include "../Characters/CharacterComponents/BBStaminaComponent.h"


// Sets default values
ABBRollingStone::ABBRollingStone()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RevealableMesh->SetEnableGravity(false);
	RevealableMesh->SetSimulatePhysics(false);
	RevealableMesh->SetLinearDamping(1.0f);

	//Setup collision
	RollingStoneCollision = CreateDefaultSubobject<USphereComponent>(TEXT("RollingStoneCollision"));
	RollingStoneCollision->SetupAttachment(RevealableMesh);
	RollingStoneCollision->SetCollisionProfileName("OverlapAll");
	RollingStoneCollision->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
}

// Called when the game starts or when spawned
void ABBRollingStone::BeginPlay()
{
	Super::BeginPlay();
	
	m_player = Cast<ABBPlayerCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
}

// Called every frame
void ABBRollingStone::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	//if the player in the collision box, then the player can push the rolling stone
}


void ABBRollingStone::Roll(FVector Direction, float distance)
{
	//User this function to set a "rolling state" for the player, for animation purposes
}

void ABBRollingStone::Lock()
{
	RevealableMesh->SetEnableGravity(false);
	RevealableMesh->SetSimulatePhysics(false);
	bIsLocked = true;
}

void ABBRollingStone::RevealActor()
{
	if (bIsLocked)
		return;
	Super::RevealActor();
	RevealableMesh->SetEnableGravity(true);
	RevealableMesh->SetSimulatePhysics(true);
}

void ABBRollingStone::HideActor()
{
	if (bIsLocked)
		return;
	RevealableMesh->SetEnableGravity(false);
	RevealableMesh->SetSimulatePhysics(false);
	Super::HideActor();
}

