// Copyright © Too Many Eyes , 2022


#include "BBThrowableComponent.h"
#include "../../Engine/Classes/GameFramework/ProjectileMovementComponent.h"
#include "../../Engine/Classes/Kismet/GameplayStatics.h"
//#include "../../../Characters/Player/BBPlayerCharacter.h"
#include "../../Engine/Classes/Camera/CameraComponent.h"

// Sets default values for this component's properties
UBBThrowableComponent::UBBThrowableComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UBBThrowableComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...

}


// Called every frame
void UBBThrowableComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

bool UBBThrowableComponent::OnUse(BBControlType controlType, AActor* instagatingActor)
{
	//if (controlType != BBControlType::THROW)
	//	return false;

	////Spawns a ABBPotionBase - WORKS NOW!
	//ABBPotionBase* potion = (ABBPotionBase*)GetWorld()->SpawnActor(GetOwner()->GetClass());
	//if (!potion)
	//	return false;
	//ABBPlayerCharacter* player = Cast<ABBPlayerCharacter>(instagatingActor);

	//potion->projectileMovementComponent->SetUpdatedComponent(potion->MeshComponent);
	//potion->projectileMovementComponent->InitialSpeed = 1000.0f;
	//potion->projectileMovementComponent->MaxSpeed = 1000.0f;
	//potion->projectileMovementComponent->bRotationFollowsVelocity = true;
	//potion->projectileMovementComponent->bShouldBounce = true;
	//potion->projectileMovementComponent->Bounciness = 0.3f;
	//potion->projectileMovementComponent->ProjectileGravityScale = 1.0f;
	//potion->projectileMovementComponent->Friction = 0.6f;



	//FVector actorLocation;
	//FVector actorBounds;
	//instagatingActor->GetActorBounds(true, actorLocation, actorBounds);

	////Player throw
	//if (player != nullptr)
	//{
	//	potion->SetActorLocation(actorLocation + (actorBounds.Length() + 5.0) * player->GetThirdPersonCameraComponent()->GetForwardVector());
	//	potion->MeshComponent->SetVisibility(true);
	//	potion->projectileMovementComponent->Velocity = player->GetThirdPersonCameraComponent()->GetForwardVector() * potion->projectileMovementComponent->InitialSpeed;
	//}
	//else
	//{
	//	//Anything else
	//	potion->SetActorLocation(actorLocation + (actorBounds.Length() + 1.0) * instagatingActor->GetActorForwardVector());
	//	potion->MeshComponent->SetVisibility(true);
	//	potion->projectileMovementComponent->Velocity = instagatingActor->GetActorForwardVector() * potion->projectileMovementComponent->InitialSpeed;
	//}

	return true;
}

