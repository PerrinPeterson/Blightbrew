// Copyright © Too Many Eyes , 2022


#include "BlightBrew/Characters/CharacterComponents/BBStaminaComponent.h"

//	COMPONENT INCLUDES
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/CapsuleComponent.h"

//	BLIGHTBREW INCLUDES
#include "BlightBrew/Characters/BBCharacterBase.h"

// Sets default values for this component's properties
UBBStaminaComponent::UBBStaminaComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;


	Init();
	// ...
}

void UBBStaminaComponent::Init()
{
	MaxStamina = 100.0f;
	CurrentStamina = MaxStamina;

#pragma region Modify

	MaxStaminaCache = MaxStamina;
	bIsModified = false;
	ModifyTime = 0.0f;

#pragma endregion EndModify

	bIsSprinting = false;
	bIsCrouching = false;
	bIsVaulting = false;
	bIsClimbing = false;
	MaxRunSpeed = 700.0f;
	MaxWalkSpeed = 450.0f;
	MaxCrouchSpeed = 250.0f;
	IncrementAmount = 0.1f;
	DecrementAmount = 0.1f;
	JumpCost = 5.0f;

	LocomotionMode = ELocomotionMode::None;

	Character = Cast<ABBCharacterBase>(GetOwner());
}


// Called when the game starts
void UBBStaminaComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UBBStaminaComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);


	if(Character->GetCharacterMovement()->IsFalling()
		&& LocomotionMode != ELocomotionMode::Climbing)
	{
		LocomotionMode = ELocomotionMode::Falling;
	}
	if (Character->GetCharacterMovement()->IsMovingOnGround())
	{
		LocomotionMode = ELocomotionMode::Grounded;
	}

	FVector velocity = Character->GetCharacterMovement()->Velocity;
	ZSpeed = velocity.Z;
	velocity.Z = 0;
	CurrentSpeed = velocity.Length();

	if (!bIsSprinting
		&& CurrentStamina < MaxStamina)
	{
		CurrentStamina += IncrementAmount;
	}
	if (bIsSprinting
		&& CurrentStamina > 0.0f)
	{
		CurrentStamina -= DecrementAmount;
	}
	else
	{
		EndSprint();
	}

	if(CurrentStamina < 0.0f)
	{
		CurrentStamina = 0.0f;
	}
	// ...
}

bool UBBStaminaComponent::Jump()
{
	if(Character->CanJump()
		&& CurrentStamina >= JumpCost)
	{
		Character->GetCharacterMovement()->JumpZVelocity = 650.0f;
		Character->Jump();
		CurrentStamina -= JumpCost;
		return true;
	}

	if (Character->CanJump()
		&& CurrentStamina < JumpCost)
	{
		Character->GetCharacterMovement()->JumpZVelocity = 325.0f;
		Character->Jump();
		return true;
	}

	return false;
}

void UBBStaminaComponent::Vault()
{
	if (CurrentStamina >= JumpCost)
	{
		bIsVaulting = true;
		//Character->Jump();
		CurrentStamina -= JumpCost;
		LocomotionMode = ELocomotionMode::Vaulting;
	}
}

void UBBStaminaComponent::EndVault()
{
	bIsVaulting = false;
	LocomotionMode = ELocomotionMode::Grounded;
}

void UBBStaminaComponent::Climb()
{
	if (CurrentStamina >= JumpCost)
	{
		bIsClimbing = true;
		//Character->Jump();
		Character->GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Custom);
		CurrentStamina -= JumpCost;
		LocomotionMode = ELocomotionMode::Climbing;
	}
}

void UBBStaminaComponent::ClimbApexReached()
{
	LocomotionMode = ELocomotionMode::Hanging;
}

void UBBStaminaComponent::ClimbFinish()
{
	LocomotionMode = ELocomotionMode::Grounded;
}

void UBBStaminaComponent::ClimbAbort()
{
	LocomotionMode = ELocomotionMode::Falling;
	EndClimb();
}

void UBBStaminaComponent::EndClimb()
{
	bIsClimbing = false;
	Character->GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Falling);
	LocomotionMode = ELocomotionMode::Falling;
}

void UBBStaminaComponent::StartSprint()
{
	if (!bIsSprinting)
	{
		if(Character->GetCharacterMovement()->IsSwimming())
		{
			bIsSprinting = true;
			Character->GetCharacterMovement()->MaxSwimSpeed = 600.0f;
		}
		else
		{
			bIsSprinting = true;
			Character->GetCharacterMovement()->MaxWalkSpeed = MaxRunSpeed;
		}

	}
}

void UBBStaminaComponent::EndSprint()
{

	Character->GetCharacterMovement()->MaxSwimSpeed = 300.0f;
	bIsSprinting = false;
	Character->GetCharacterMovement()->MaxWalkSpeed = MaxWalkSpeed;


}

void UBBStaminaComponent::StartCrouch()
{
	if (!bIsCrouching
		&& !bIsClimbing)
		//&& Character->CanCrouch())
	{
		EndSprint();
		bIsCrouching = true;
		Character->GetCharacterMovement()->MaxWalkSpeed = MaxCrouchSpeed;
		Character->GetCharacterMovement()->Crouch(true);
		float moveAmount = Character->GetCapsuleComponent()->GetScaledCapsuleHalfHeight() / 2;
		Character->SetActorLocation(FVector(Character->GetActorLocation().X, Character->GetActorLocation().Y, Character->GetActorLocation().Z - moveAmount));
	}
	else
	{
		EndCrouch();
	}
}

void UBBStaminaComponent::EndCrouch()
{
	bIsCrouching = false;
	Character->GetCharacterMovement()->MaxWalkSpeed = MaxWalkSpeed;
	Character->GetCharacterMovement()->UnCrouch(true);
}

void UBBStaminaComponent::EndModify()
{
	//	Reset the Modify State Timer's Time
	ModifyTime = 0.0f;
	//	Reset the MaxStamina Value to the Cached(Previous) Value.
	MaxStamina = MaxStaminaCache;
	//	Reset Current Stamina
	if (CurrentStamina > MaxStamina)
	{
		CurrentStamina = MaxStamina;
	}
	//	Toggle the Modify State to false
	bIsModified = false;
}

bool UBBStaminaComponent::ModifyMaxStamina(float value, float time)
{
	if (!bIsModified)
	{
		//	Set the Modify State Timer's Time to the Input Time
		ModifyTime = time;
		//	Cache the current MaxStamina Value
		MaxStaminaCache = MaxStamina;
		//	Increase MaxStamina by the Input Value
		MaxStamina += value;
		CurrentStamina += value;

		//	Create a Timer for the current Modify State
		GetWorld()->GetTimerManager().SetTimer(ModifyTimerHandle,
			this,
			&UBBStaminaComponent::EndModify,
			ModifyTime);

		//	Toggle Modify State to true
		bIsModified = true;

		//	Tell the instigator that the Stamina was Successfully Modified.
		return true;
	}

	//	Tell the instigator that the Stamina was Not Modified.	(Is Currently Modified)
	return false;
}

void UBBStaminaComponent::SetMovementSpeed(float value)
{
	MovementSpeed = value;
	Character->GetCharacterMovement()->MaxWalkSpeed = MovementSpeed;
	MaxWalkSpeed = value;
}

void UBBStaminaComponent::ModifyCurrentStamina(float value)
{
	CurrentStamina += value;
	if (CurrentStamina > MaxStamina)
	{
		CurrentStamina = MaxStamina;

	}
}

