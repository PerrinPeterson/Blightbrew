// Copyright © Too Many Eyes , 2022


#include "BlightBrew/AI/Spawners/BBAISpawnerBase.h"

#include "NavigationSystem.h"
#include "BlightBrew/Characters/AI/BBAICharacterBase.h"
#include "BlightBrew/Characters/AI/Fauna/BBFaunaAICharacterBase.h"
#include "BlightBrew/Characters/AI/Fauna/BBFaunaAIController.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ABBAISpawnerBase::ABBAISpawnerBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


	SpawnRadius = 500.0f;
	MaxSpawnAmount = 20;
}

// Called when the game starts or when spawned
void ABBAISpawnerBase::BeginPlay()
{
	Super::BeginPlay();


	for(int i = 0; i < MaxSpawnAmount; i++)
	{
		int index = FMath::RandRange(0, AIClasses.Num() - 1);
		FActorSpawnParameters SpawnParameters;
		SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButDontSpawnIfColliding;
		SpawnParameters.Owner = this;

		FNavLocation Location;
		const UNavigationSystemV1* NavSystem = UNavigationSystemV1::GetCurrent(GetWorld());
		NavSystem->GetRandomPointInNavigableRadius(GetActorLocation(), SpawnRadius, Location);

		FVector SpawnLocation = Location.Location;
		FRotator SpawnRotation;

		ManagedAI.Add(Cast<ABBAICharacterBase>(GetWorld()->SpawnActor(
			AIClasses[index],
			&SpawnLocation,
			&SpawnRotation,
			SpawnParameters)));

		//	FAUNA 
		if(ABBFaunaAICharacterBase* fauna = Cast<ABBFaunaAICharacterBase>(ManagedAI[i]))
		{
			ABBFaunaAIController* NewController = Cast<ABBFaunaAIController>(GetWorld()->SpawnActor(
				fauna->GetControllerClass(),
				&SpawnLocation,
				&SpawnRotation,
				SpawnParameters));

			if(NewController != nullptr)
			{
				GetWorld()->AddController(NewController);

				NewController->Possess(ManagedAI[i]);
				
			}

		}
	}
}

// Called every frame
void ABBAISpawnerBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

