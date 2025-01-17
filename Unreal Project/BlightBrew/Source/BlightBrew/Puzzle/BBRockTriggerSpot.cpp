// Copyright © Too Many Eyes , 2022


#include "BBRockTriggerSpot.h"
#include "Components/StaticMeshComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/SphereComponent.h"
//Blightbrew
#include "BBRollingStone.h"

// Sets default values
ABBRockTriggerSpot::ABBRockTriggerSpot()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	TriggerMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("TriggerMesh"));
	RootComponent = TriggerMesh;
	
	TriggerVolume = CreateDefaultSubobject<UCapsuleComponent>(TEXT("TriggerVolume"));
	TriggerVolume->SetupAttachment(RootComponent);

	RockPullSpot = CreateDefaultSubobject<USphereComponent>(TEXT("RockPullSpot"));
	RockPullSpot->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void ABBRockTriggerSpot::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABBRockTriggerSpot::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	//Check if a rock is in the trigger volume
	if (!m_bTriggered)
	{
		TArray<AActor*> OverlappingActors;
		TriggerVolume->GetOverlappingActors(OverlappingActors);
		for (AActor* Actor : OverlappingActors)
		{
			ABBRollingStone* RollingStone = Cast<ABBRollingStone>(Actor);
			if (RollingStone)
			{
				m_bTriggered = true;
				RollingStone->Lock();
				m_Rock = RollingStone;
				OnTrigger();
			}
		}
	}
	if (m_bTriggered && !m_bRockInPlace)
	{
		if (m_Rock)
		{
			FVector RockPullLocation = RockPullSpot->GetComponentLocation();
			FVector RockLocation = m_Rock->GetActorLocation();
			//RockPullLocation.Z = RockLocation.Z;
			FVector RockToPullSpot = RockPullLocation - m_Rock->GetActorLocation();

			if (RockToPullSpot.Size() < DistanceForgiveness)
			{
				m_bRockInPlace = true;
				m_Rock->SetActorLocation(RockPullLocation);
				m_Rock->SetActorRotation(RockPullSpot->GetComponentRotation());
			}
			else
			{

				m_Rock->SetActorLocation(FMath::VInterpTo(m_Rock->GetActorLocation(), RockPullLocation, DeltaTime, PullSpeed));
				m_Rock->SetActorRotation(FMath::RInterpTo(m_Rock->GetActorRotation(), RockPullSpot->GetComponentRotation(), DeltaTime, PullSpeed));
			}
		}
	}

}

void ABBRockTriggerSpot::OnTrigger()
{
	m_bTriggered = true;
	TriggerMesh->SetMaterial(0, RockInPlaceMaterial);
	
}

