// Copyright © Too Many Eyes , 2022


#include "BlightBrew/Characters/CharacterComponents/BBDialogueComponent.h"

#include "BlightBrew/Characters/Player/BBPlayerCharacter.h"
#include "BlightBrew/UI/BBHUD.h"
#include "BlightBrew/UI/Dialogue/BBDialogueScreenWidget.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"


void FDialogueOption::OnClicked()
{
	switch(OptionType)
	{
		case EDialogueOptionType::Barter :
		{
			//	Trigger Barter
			
		}
		case EDialogueOptionType::Sell :
		{
			//	Trigger Sell

		}
		case EDialogueOptionType::Next :
		{
			//	Trigger Next Dialogue

		}
		case EDialogueOptionType::End :
		{
			//	End Conversation

		}

		default:
		{
				
		}
	}
}


// Sets default values for this component's properties
UBBDialogueComponent::UBBDialogueComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


void UBBDialogueComponent::OnInteract(ABBPlayerCharacter* instigator)
{
	Player = instigator;

	Player->GetCharacterMovement()->StopActiveMovement();

	Player->GetHUD()->StartDialogue(this);
}

void UBBDialogueComponent::PlayDialogueOneShot()
{
	if (DialogueOneShotFX != nullptr)
	{
		float volume = FMath::FRandRange(0.01f, 0.1f);
		float pitch = FMath::FRandRange(0.75f, 1.0f);

		UGameplayStatics::PlaySound2D(this,
			DialogueOneShotFX,
			volume,
			pitch);
	}
}

// Called when the game starts
void UBBDialogueComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UBBDialogueComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

