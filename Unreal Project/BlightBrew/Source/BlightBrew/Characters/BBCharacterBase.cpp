// Copyright © Too Many Eyes , 2022


#include "BlightBrew/Characters/BBCharacterBase.h"

//	COMPONENT INCLUDES
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

//	BLIGHTBREW INCLUDES
#include "CharacterComponents/BBStaminaComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Actor.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ABBCharacterBase::ABBCharacterBase()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


	VaultSpeed = 500.0f;
	bHasReachedApex = false;
	bHasReachedEnd = false;
	bHasLeftStart = false;
}

void ABBCharacterBase::Init()
{
#pragma region StaminaComponent

	StaminaComponent = CreateDefaultSubobject<UBBStaminaComponent>(TEXT("Stamina Component"));

#pragma endregion EndStamina
}

// Called when the game starts or when spawned
void ABBCharacterBase::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void ABBCharacterBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if(StaminaComponent != nullptr)
	{
		if (StaminaComponent->IsVaulting())
		{
			UpdateVault(DeltaTime);
		}
		if (StaminaComponent->IsClimbing())
		{
			UpdateClimb(DeltaTime);
		}
	}

}

// Called to bind functionality to input
void ABBCharacterBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ABBCharacterBase::OnFocus(AActor* InstigatingActor)
{

}

void ABBCharacterBase::OnInteract(AActor* InstigatingActor)
{

}

void ABBCharacterBase::SetFocusText_BP(FText text)
{
	SetFocusText(text);
}

void ABBCharacterBase::StartJump()
{
	if(StaminaComponent->IsClimbing()
		&& !bHasReachedApex)
	{
		AbortClimb();
	}
	else if (StaminaComponent->IsClimbing()
		&& bHasReachedApex)
	{
		FinishClimb();
	}
	else
	{
		const ScaleType scaleType = CheckScaleType();
		if (scaleType == ScaleType::Vaulting)
		{
			StartVault();
			//UE_LOG(LogTemp, Warning, TEXT("Vaulting"));
		}
		else if (scaleType == ScaleType::Climbing)
		{
			StartClimb();
			//UE_LOG(LogTemp, Warning, TEXT("Climbing"));
		}
		else
		{
			if(StaminaComponent->Jump())
			{
				//UE_LOG(LogTemp, Warning, TEXT("Jumping"));

				if (JumpFX != nullptr)
				{
					FVector fxLocation = GetActorLocation();
					fxLocation.Z -= GetCapsuleComponent()->GetScaledCapsuleHalfHeight() * 2;

					UGameplayStatics::PlaySoundAtLocation(this,
						JumpFX,
						fxLocation);
				}
			}

		}
	}

}

void ABBCharacterBase::StartCrouch()
{
	StaminaComponent->StartCrouch();
}

void ABBCharacterBase::EndCrouch()
{
	StaminaComponent->EndCrouch();
}

void ABBCharacterBase::StartSprint()
{
	StaminaComponent->StartSprint();
}

void ABBCharacterBase::EndSprint()
{
	StaminaComponent->EndSprint();
}

void ABBCharacterBase::StartVault()
{
	//UE_LOG(LogTemp, Warning, TEXT("Vault Started."));
	StaminaComponent->Vault();
	bHasReachedApex = false;
	//GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void ABBCharacterBase::UpdateVault(float DeltaTime)
{
	if (!bHasReachedApex)
	{
		SetActorLocation(FMath::VInterpConstantTo(GetActorLocation(), VaultApexLocation, DeltaTime, VaultSpeed));
		if (GetActorLocation().Z + 1 >= VaultApexLocation.Z - 1)
		{
			//UE_LOG(LogTemp, Warning, TEXT("Vault Apex Reached."));
			bHasReachedApex = true;
		}
	}
	else
	{
		SetActorLocation(FMath::VInterpConstantTo(GetActorLocation(), VaultEndLocation, DeltaTime, VaultSpeed));
		if (GetActorLocation() == VaultEndLocation)
		{
			//UE_LOG(LogTemp, Warning, TEXT("Vault End Location Reached."));
			EndVault();
		}
	}
}

void ABBCharacterBase::EndVault()
{
	StaminaComponent->EndVault();
	//GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	//UE_LOG(LogTemp, Warning, TEXT("Vault Ended."));
}

void ABBCharacterBase::StartClimb()
{
	//UE_LOG(LogTemp, Warning, TEXT("Climb Started."));
	StaminaComponent->Climb();
	bHasReachedApex = false;
	bHasReachedEnd = true;
	bHasLeftStart = false;
}

void ABBCharacterBase::UpdateClimb(float DeltaTime)
{
	if (!bHasReachedApex)
	{
		if(GetActorLocation().Z != VaultStartLocation.Z)
		{
			bHasLeftStart = true;
		}
		if(GetActorLocation().Z == VaultStartLocation.Z
			&& bHasLeftStart)
		{
			AbortClimb();
		}
		if(GetActorLocation().Z < VaultBounds.Min.Z)
		{
			SetActorLocation(VaultStartLocation);
		}
		//SetActorLocation(FMath::VInterpConstantTo(GetActorLocation(), VaultApexLocation, DeltaTime, VaultSpeed));
		if (GetActorLocation().Z + 1 >= VaultApexLocation.Z - 1)
		{
			//UE_LOG(LogTemp, Warning, TEXT("Climb Apex Reached."));
			bHasReachedApex = true;
			StaminaComponent->ClimbApexReached();
		}
	}
	else if(bHasReachedApex && !bHasReachedEnd)
	{
		SetActorLocation(FMath::VInterpConstantTo(GetActorLocation(), VaultEndLocation, DeltaTime, VaultSpeed));
		if (GetActorLocation() == VaultEndLocation)
		{
			//UE_LOG(LogTemp, Warning, TEXT("Climb End Location Reached."));
			bHasReachedEnd = true;
			EndClimb();
		}
	}
}

void ABBCharacterBase::AbortClimb()
{
	StaminaComponent->ClimbAbort();
	//UE_LOG(LogTemp, Warning, TEXT("Climb Aborted."));
}

void ABBCharacterBase::FinishClimb()
{
	bHasReachedEnd = false;
}

void ABBCharacterBase::EndClimb()
{
	StaminaComponent->EndClimb();
	//UE_LOG(LogTemp, Warning, TEXT("Climb Ended."));

}

ScaleType ABBCharacterBase::CheckScaleType()
{
	FHitResult hitResult;
	FVector traceStart = GetActorLocation();
	FVector traceEnd = traceStart + (GetActorForwardVector() * 100.0f);
	FCollisionQueryParams params;
	params.AddIgnoredActor(this);

	GetWorld()->LineTraceSingleByChannel(hitResult, traceStart, traceEnd, ECC_WorldDynamic, params);

	/*DrawDebugLine(GetWorld(),
		traceStart,
		traceEnd,
		FColor::Green,
		false,
		0.5f,
		0,
		5.0f);*/

	//	If the raycast hit
	if (hitResult.GetActor())
	{
#pragma region Vaulting
		if (hitResult.GetActor()->ActorHasTag("Vaultable"))
		{

			FVector loc = hitResult.GetActor()->GetActorLocation();
			FVector playerLoc = GetActorLocation();
			//FBox bounds = hitResult.GetActor()->GetStreamingBounds();
			FVector hitOrigin = FVector::Zero();
			FVector boundsExtent = FVector::Zero();
			hitResult.GetActor()->GetActorBounds(true, hitOrigin, boundsExtent);
			//FVector height = bounds.Max;

			FVector finalLoc = playerLoc;
			//FVector finalLoc = FVector(loc.X, loc.Y, height.Z + 90.0f);
			finalLoc.Z = (boundsExtent.Z*2) + 90.0f;

			//UE_LOG(LogTemp, Warning, TEXT("Your Height: %f"), GetCapsuleComponent()->GetScaledCapsuleHalfHeight() * 2);

			if (boundsExtent.Z > GetCapsuleComponent()->GetScaledCapsuleHalfHeight() * 2)
			{
				//UE_LOG(LogTemp, Warning, TEXT("Actor too tall to vault."));
				return ScaleType::None;
			}

			VaultApexLocation = finalLoc + GetActorForwardVector() * 100.0f;
			VaultSpeed = 500.0f;
			VaultEndLocation = VaultApexLocation + GetActorForwardVector() * 100.0f;

			//UE_LOG(LogTemp, Warning, TEXT("Vault Height: %f"), VaultApexLocation.Z);

			/*DrawDebugSphere(GetWorld(),
				VaultApexLocation,
				10.0f,
				36,
				FColor::Green,
				false,
				5.0f,
				2.0f);

			DrawDebugSphere(GetWorld(),
				VaultEndLocation,
				10.0f,
				36,
				FColor::Green,
				false,
				5.0f,
				2.0f);*/

			return ScaleType::Vaulting;
		}	//	END VAULTING
#pragma endregion Vaulting

#pragma region Climbing
		if (hitResult.GetActor()->ActorHasTag("Climbable"))
		{

			FVector loc = GetActorLocation();
			VaultStartLocation = GetActorLocation();
			//VaultBounds = hitResult.GetActor()->GetStreamingBounds();
			FVector hitOrigin = FVector::Zero();
			FVector boundsExtent = FVector::Zero();
			hitResult.GetActor()->GetActorBounds(true, hitOrigin, boundsExtent);
			//FVector height = VaultBounds.Max;

			//UE_LOG(LogTemp, Warning, TEXT("Your Height: %f"), GetCapsuleComponent()->GetScaledCapsuleHalfHeight() * 2);

			if ((boundsExtent.Z * 2) > GetCapsuleComponent()->GetScaledCapsuleHalfHeight() * 4)
			{
				//UE_LOG(LogTemp, Warning, TEXT("Actor too tall to climb."));
				//return ScaleType::None;
			}

			//VaultApexLocation = FVector(loc.X, loc.Y, height.Z);
			VaultApexLocation = loc;
			VaultApexLocation.Z = (boundsExtent.Z * 2);
			float scale = (boundsExtent.Z * 2) - GetActorLocation().Z;
			//UE_LOG(LogTemp, Warning, TEXT("Climb Scale: %f"), scale);
			VaultSpeed = 100.0f;// *scale;
			VaultEndLocation = VaultApexLocation + GetActorForwardVector() * 100.0f;
			VaultEndLocation.Z += 100.0f;

			//UE_LOG(LogTemp, Warning, TEXT("Climb Height: %f"), (boundsExtent.Z * 2));
			//UE_LOG(LogTemp, Warning, TEXT("Climb Speed: %f"), VaultSpeed);

			/*DrawDebugSphere(GetWorld(),
				VaultApexLocation,
				10.0f,
				36,
				FColor::Green,
				false,
				5.0f,
				2.0f);

			DrawDebugSphere(GetWorld(),
				VaultEndLocation,
				10.0f,
				36,
				FColor::Green,
				false,
				5.0f,
				2.0f);*/

			return ScaleType::Climbing;
		}	//	END CLIMBING
#pragma endregion Climbing
	}

	return ScaleType::None;
}

