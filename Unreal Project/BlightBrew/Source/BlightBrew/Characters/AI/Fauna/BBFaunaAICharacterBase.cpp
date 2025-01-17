// Copyright © Too Many Eyes , 2022


#include "BlightBrew/Characters/AI/Fauna/BBFaunaAICharacterBase.h"

#include "BlightBrew/Characters/AI/Fauna/BBFaunaAIController.h"

#include "GameFramework/CharacterMovementComponent.h"

ABBFaunaAICharacterBase::ABBFaunaAICharacterBase()
{
	//Init();

	//MovementSpeed = 100.0f;
}

void ABBFaunaAICharacterBase::Init()
{
	Super::Init();

	MovementSpeed = 100.0f;
	AngerPercent = 0.0f;
}

void ABBFaunaAICharacterBase::BeginPlay()
{
	Super::BeginPlay();

	GetCharacterMovement()->MaxWalkSpeed = MovementSpeed;

	switch (PatrolType)
	{
		case EPatrolType::Path:
		{

		}

		case EPatrolType::Random:
		{
			//GenerateRandomTarget();

		}

		case EPatrolType::Region:
		{

		}

		default:
		{

		}
	}
}

void ABBFaunaAICharacterBase::Patrol(float DeltaTime)
{
	switch(PatrolType)
	{
		case EPatrolType::Path :
		{
			
		}

		case EPatrolType::Random:
		{
			//if(GetActorLocation() == CurrentTarget)
			//{
			//	GenerateRandomTarget();
			//}
			//
			//SetActorLocation(FMath::VInterpTo(GetActorLocation(), CurrentTarget, DeltaTime, MovementSpeed));
		}

		case EPatrolType::Region:
		{

		}

		default:
		{
				
		}
	}
}

void ABBFaunaAICharacterBase::GenerateRandomTarget()
{
	CurrentTarget = FMath::VRand();
}

void ABBFaunaAICharacterBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (PatrolType != EPatrolType::None)
	{
		//Patrol(DeltaTime);
	}
}

void ABBFaunaAICharacterBase::OnFocus(AActor* InstigatingActor)
{
	Super::OnFocus(InstigatingActor);

	switch (Temperament)
	{
		case ETemperamentType::Aggressive :
		{
			AngerPercent += 10.0f;
		}
		case ETemperamentType::Dynamic:
		{

		}
		case ETemperamentType::Passive:
		{

		}
	}
}

void ABBFaunaAICharacterBase::OnInteract(AActor* InstigatingActor)
{
	Super::OnInteract(InstigatingActor);

	switch(ConfrontationType)
	{
		case EConfrontationType::Flee :
		{
			
		}
		case EConfrontationType::Pursue:
		{
			AngerPercent = 100.0f;
		}
		case EConfrontationType::None :
		{

		}
	}
}

TSubclassOf<ABBFaunaAIController> ABBFaunaAICharacterBase::GetControllerClass()
{
	return ControllerClass;
}
