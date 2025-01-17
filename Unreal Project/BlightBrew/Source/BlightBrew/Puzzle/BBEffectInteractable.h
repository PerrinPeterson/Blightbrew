// Copyright © Too Many Eyes , 2022
/*An Effect Interactable, Designed by Perrin Peterson, 02/05/2023
* This actor is a puzzle element and serves as an interactable that can be interacted with by the player.
* This actor is used to apply a status effect to the player when they interact with it.
* This actor needs to;
*	- Apply a status effect to the player when they interact with it (our potion effects work perfectly)
*	- Have 2 meshes, one for when the player can interact with it, and one for when the player can't interact with it
*	- Have a particle effect that plays when the player interacts with it
*	- Have a sound effect that plays when the player interacts with it
*	- Have a particle effect that plays while it's interactable
*/

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
//Blightbrew
#include "../Gameplay/BBInterface.h"
#include "BBEffectInteractable.generated.h"

UCLASS()
class BLIGHTBREW_API ABBEffectInteractable : public AActor, public IBBInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABBEffectInteractable();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//Interactable
	virtual void OnFocus(AActor* InstigatingActor) override;
	virtual void OnInteract(AActor* InstigatingActor) override;
	UFUNCTION(NotBlueprintable)
		virtual void SetFocusText(FText text) override;
	UFUNCTION(NotBlueprintable)
		virtual FText GetFocusText() override;

	//The Mesh component, not editable, so that we can change the mesh at runtime
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "BlightBrew|Puzzle")
		class UStaticMeshComponent* EffectInteractableMesh;
	//The before use mesh
	UPROPERTY(EditAnywhere, Category = "BlightBrew|Puzzle")
		class UStaticMesh* BeforeUseMesh;
	//The after use mesh
	UPROPERTY(EditAnywhere, Category = "BlightBrew|Puzzle")
		class UStaticMesh* AfterUseMesh;

	//The particle effect that plays when the player interacts with the interactable
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BlightBrew|Puzzle")
		class UNiagaraComponent* InteractParticleEffect;
	//The sound effect that plays when the player interacts with the interactable
	UPROPERTY(EditAnywhere, Category = "BlightBrew|Puzzle")
		class USoundBase* InteractSoundEffect;
	//The particle effect that plays while the interactable is interactable
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BlightBrew|Puzzle")
		class UNiagaraComponent* InteractableParticleEffect;
	
	//The status effects that are applied to the player when they interact with the interactable
	UPROPERTY(EditAnywhere, Instanced, BlueprintReadWrite, Category = "Blightbrew|Puzzle")
		TArray<class UBBEffect*> Effects;
	
	UPROPERTY(VisibleAnywhere, Category = "Blightbrew|Puzzle")
		bool IsInteractable;

	UPROPERTY(EditAnywhere, Category = "Blightbrew|Puzzle")
		float OnInteractParticleBurstTime;
	//Time before the interactable resets
	UPROPERTY(EditAnywhere, Category = "Blightbrew|Puzzle")
		float CooldownTime;

public:
	UFUNCTION()
		void ResetInteractable();
	UFUNCTION()
		void EndParticleBurst();

	
private:
	FText m_focusText;
};
