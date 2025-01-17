// Copyright © Too Many Eyes , 2022
/*The Revealable Actor, Designed by Perrin Peterson, 02/07/2023
* This actor is a puzzle element and serves as a base class for all actors that need to be revealed by the player.
* This actor needs to;
*	- Have a material that can be changed to reveal the actor
*	- Disable the collision on the actor when it's hidden, so that the player can't interact with it
*/

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BBRevealableActor.generated.h"

UCLASS()
class BLIGHTBREW_API ABBRevealableActor : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ABBRevealableActor();

	//The Mesh component for the actor
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BlightBrew|Puzzle")
		class UStaticMeshComponent* RevealableMesh;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	virtual void RevealActor();
	virtual void HideActor();

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;


#pragma region Debug
	UPROPERTY(EditAnywhere, Category = "BlightBrew|Puzzle")
		bool bIsHidden = true;
#pragma endregion
};
