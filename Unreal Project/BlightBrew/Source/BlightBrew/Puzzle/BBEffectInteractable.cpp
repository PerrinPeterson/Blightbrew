// Copyright © Too Many Eyes , 2022


#include "BBEffectInteractable.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "../../../../../Engine/Plugins/FX/Niagara/Source/Niagara/Public/NiagaraComponent.h"
//BlightBrew
#include "../Characters/Player/BBPlayerCharacter.h"
#include "../Items/Potions/PotionEffects/BBEffect.h"


// Sets default values
ABBEffectInteractable::ABBEffectInteractable()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	EffectInteractableMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh Component"));
	SetRootComponent(EffectInteractableMesh);

	InteractParticleEffect = CreateDefaultSubobject<UNiagaraComponent>(TEXT("OnInteractNiagaraComponent"));
	InteractParticleEffect->SetupAttachment(RootComponent);
	

	InteractableParticleEffect = CreateDefaultSubobject<UNiagaraComponent>(TEXT("InteractableNiagaraComponent"));
	InteractableParticleEffect->SetupAttachment(RootComponent);

	IsInteractable = true;
	if (BeforeUseMesh)
		EffectInteractableMesh->SetStaticMesh(BeforeUseMesh);
	m_focusText = FText::FromString("Drink?");


}

// Called when the game starts or when spawned
void ABBEffectInteractable::BeginPlay()
{
	Super::BeginPlay();
	InteractParticleEffect->Deactivate();
}

// Called every frame
void ABBEffectInteractable::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABBEffectInteractable::OnFocus(AActor* InstigatingActor)
{

}

void ABBEffectInteractable::OnInteract(AActor* InstigatingActor)
{
	if (IsInteractable)
	{
		//Set a timer to reset the interactable
		FTimerHandle ResetInteractableTimer;
		GetWorld()->GetTimerManager().SetTimer(ResetInteractableTimer, this, &ABBEffectInteractable::ResetInteractable, CooldownTime, false);

		//Set a timer to end the particle burst
		FTimerHandle EndParticleBurstTimer;
		GetWorld()->GetTimerManager().SetTimer(EndParticleBurstTimer, this, &ABBEffectInteractable::EndParticleBurst, OnInteractParticleBurstTime, false);

		InteractParticleEffect->Activate();
		InteractableParticleEffect->Deactivate();
		IsInteractable = false;

		//Play the sound effect
		UGameplayStatics::PlaySoundAtLocation(GetWorld(), InteractSoundEffect, GetActorLocation());

		//Apply the effects to the player
		TArray<AActor*> FoundActors;
		FoundActors.Add(InstigatingActor);
		for (UBBEffect* effect : Effects)
		{
			effect->OnUse(FoundActors);
		}

		//Change the mesh to the interacted mesh
		if (AfterUseMesh)
			EffectInteractableMesh->SetStaticMesh(AfterUseMesh);

	}
}

void ABBEffectInteractable::SetFocusText(FText text)
{
	m_focusText = text;
}

FText ABBEffectInteractable::GetFocusText()
{
	if (!IsInteractable)
		return FText::FromString("On Cooldown");
	return m_focusText;
}

void ABBEffectInteractable::ResetInteractable()
{
	IsInteractable = true;
	InteractableParticleEffect->Activate();
	if (BeforeUseMesh)
		EffectInteractableMesh->SetStaticMesh(BeforeUseMesh);
}

//Ends the particle burst
void ABBEffectInteractable::EndParticleBurst()
{
	InteractParticleEffect->Deactivate();
}

