// Copyright © Too Many Eyes , 2022


#include "BlightBrew/Characters/AI/BBAICharacterBase.h"

#include "BlightBrew/Characters/CharacterComponents/BBDialogueComponent.h"
#include "BlightBrew/Characters/Player/BBPlayerCharacter.h"

ABBAICharacterBase::ABBAICharacterBase()
{
	//Init();
}

void ABBAICharacterBase::Init()
{
	Super::Init();

	DialogueComponent = CreateDefaultSubobject<UBBDialogueComponent>(TEXT("DialogueComponent"));
}

void ABBAICharacterBase::BeginPlay()
{
	Super::BeginPlay();

	
}

void ABBAICharacterBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ABBAICharacterBase::OnFocus(AActor* InstigatingActor)
{
	Super::OnFocus(InstigatingActor);
}

void ABBAICharacterBase::OnInteract(AActor* InstigatingActor)
{
	Super::OnInteract(InstigatingActor);

	if(ABBPlayerCharacter* player = Cast<ABBPlayerCharacter>(InstigatingActor))
	{
		if(DialogueComponent)
		{
			DialogueComponent->SetName(FocusText);
			DialogueComponent->OnInteract(player);
		}
		

		//UE_LOG(LogTemp, Warning, TEXT("Player interacted with: %s"), *FocusText.ToString());
	}
}
