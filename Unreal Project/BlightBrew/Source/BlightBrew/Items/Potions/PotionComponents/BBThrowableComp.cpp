// Copyright © Too Many Eyes , 2022

#include "BBThrowableComp.h"
#include "../BBPotionBase.h"
#include "../../../Characters/Player/BBPlayerCharacter.h"
#include "../../Engine/Classes/GameFramework/ProjectileMovementComponent.h"
#include "../../Engine/Classes/Kismet/GameplayStatics.h"
#include "../../Engine/Classes/Camera/CameraComponent.h"

bool UBBThrowableComp::OnUse(AActor* instagatingItem, BBControlType controlType, AActor* instagatingActor)
{
	if (controlType != BBControlType::THROW)
		return false;

	//Spawns a ABBPotionBase - WORKS NOW! 
	//ABBPotionBase* potion = (ABBPotionBase*)GetWorld()->SpawnActor(instagatingItem->StaticClass());
	ABBPotionBase* potion = (ABBPotionBase*)instagatingActor->GetWorld()->SpawnActor(instagatingItem->GetClass());
	//ABBPotionBase* potion = (ABBPotionBase*)GetWorld()->SpawnActor();
	if (!potion)
		return false;
	ABBPlayerCharacter* player = Cast<ABBPlayerCharacter>(instagatingActor);

	//potion->MeshComponent->SetMassOverrideInKg(NAME_Actor, 1.0f, false);
	potion->MeshComponent->BodyInstance.bOverrideMass = false;
	potion->MeshComponent->BodyInstance.SetMassOverride(1.0f);
	potion->MeshComponent->SetSimulatePhysics(false);

	potion->ProjectileMovementComponent->SetUpdatedComponent(potion->MeshComponent);
	potion->ProjectileMovementComponent->InitialSpeed = 1000.0f;
	potion->ProjectileMovementComponent->MaxSpeed = 1000.0f;
	potion->ProjectileMovementComponent->bRotationFollowsVelocity = true;
	potion->ProjectileMovementComponent->bShouldBounce = true;
	potion->ProjectileMovementComponent->Bounciness = 0.3f;
	potion->ProjectileMovementComponent->ProjectileGravityScale = 1.0f;
	potion->ProjectileMovementComponent->Friction = 0.6f;


	FVector actorLocation;
	FVector actorBounds;
	instagatingActor->GetActorBounds(true, actorLocation, actorBounds);

	//Player throw
	if (player != nullptr)
	{
		potion->SetActorLocation(actorLocation + (actorBounds.Length() + 5.0) * player->GetThirdPersonCameraComponent()->GetForwardVector());
		potion->MeshComponent->SetVisibility(true);
		potion->ProjectileMovementComponent->Velocity = player->GetThirdPersonCameraComponent()->GetForwardVector() * potion->ProjectileMovementComponent->InitialSpeed;
	}
	else
	{
		//Anything else
		potion->SetActorLocation(actorLocation + (actorBounds.Length() + 1.0) * instagatingActor->GetActorForwardVector());
		potion->MeshComponent->SetVisibility(true);
		potion->ProjectileMovementComponent->Velocity = instagatingActor->GetActorForwardVector() * potion->ProjectileMovementComponent->InitialSpeed;
	}
	TArray<UBBThrowableComp*> throwComps = potion->GetBBComponentsOfType<UBBThrowableComp>();
	for (int i = 0; i < throwComps.Num(); i++)
	{
		throwComps[i]->bThrown = true;
	}
	return true;
}

void UBBThrowableComp::OnHit(AActor* SelfActor, AActor* OtherActor, FVector NormalImpulse, const FHitResult& Hit)
{
	if (bThrown)
	{
		//Effect Logic
		if (!Effects.IsEmpty())
		{
			for (int i = 0; i < Effects.Num(); i++)
			{
				//TODO: For AOE, replace this with a function that tries to get any AOE components, and defaults to the hit actor;
				TArray<AActor*> effectedActors;
				effectedActors.Add(SelfActor);
				Effects[i]->OnUse(effectedActors);
			}
		}
		//Destruction
		SelfActor->Destroy();
	}
}
