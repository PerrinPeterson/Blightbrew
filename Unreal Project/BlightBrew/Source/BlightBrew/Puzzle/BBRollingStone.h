// Copyright © Too Many Eyes , 2022
/*The Rolling Stone, Designed by Perrin Peterson, 02/03/2023
* This actor is a puzzle element and serves as a base class so that actors can be hidden, and revealed when the player has a status effect that allows them to see them
* This actor needs to;
*	- Be able to be hidden, and not have any physics or collision
*	- Be able to be revealed, and have the physics and collision that it had before it was hidden
*/
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BBRevealableActor.h"
#include "BBRollingStone.generated.h"

UCLASS()
class BLIGHTBREW_API ABBRollingStone : public ABBRevealableActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABBRollingStone();
	
	//The collision box that will be used to detect when the player is pushing the rolling stone
	UPROPERTY(VisibleAnywhere, Category = "BlightBrew|Puzzle")
		class USphereComponent* RollingStoneCollision;
	
	//The RollingStoneSlot that the rolling stone is currently locked into
	/*UPROPERTY(VisibleAnywhere, Category = "BlightBrew|Puzzle")
		class ABBRollingStoneSlot* CurrentSlot;*/
	
	

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void Roll(FVector Direction, float distance);
	void Lock();

	//Overrides
	void RevealActor() override;
	void HideActor() override;

public:
	UPROPERTY(EditAnywhere, Category = "BlightBrew|Puzzle")
		bool bIsLocked = false;
	UPROPERTY(VisibleAnywhere, Category = "BlightBrew|Puzzle")
		bool bIsRolling = false;
	UPROPERTY(VisibleAnywhere, Category = "BlightBrew|Puzzle")
		FVector rollingDirection;
	UPROPERTY(EditAnywhere, Category = "BlightBrew|Puzzle")
		float rollingSpeed = 1.0f;
	UPROPERTY(EditAnywhere, Category = "BlightBrew|Puzzle")
		float facingDirectionForgiveness = 0.1f;
	/* Cannot be 0, lower is a higher corrective force. 0.1 is near absolute. */
	UPROPERTY(EditAnywhere, Category = "BlightBrew|Puzzle")
		float correctiveForce = 1.0f;
	
private:
	//A refernece to the player, so we can keep track of the player's pushing direction
	class ABBPlayerCharacter* m_player;
};
