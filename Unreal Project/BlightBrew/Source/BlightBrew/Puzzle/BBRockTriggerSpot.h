// Copyright © Too Many Eyes , 2022
/*Rock Trigger Spot, Designed by Perrin Peterson, 02/07/2023
* This actor is a puzzle element and serves as a trigger spot for the rock puzzle.
* This actor needs to;
*	- Have a trigger volume that can be used to trigger the other elements of the puzzle
*	- Once the rock is in range, it needs to pull the rock into place, and keep it there
* For debugging purposes, we'll set a new material on the base mesh when the rock is in place
*/

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BBRockTriggerSpot.generated.h"

class ABBRollingStone;
UCLASS()
class BLIGHTBREW_API ABBRockTriggerSpot : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABBRockTriggerSpot();

	//The Mesh component for the actor
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BlightBrew|Puzzle")
		class UStaticMeshComponent* TriggerMesh;
	
	//The Trigger Volume for the actor
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BlightBrew|Puzzle")
		class UCapsuleComponent* TriggerVolume;

	//The spot the rock will be pulled to, we'll use the center of a sphere component
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BlightBrew|Puzzle")
		class USphereComponent* RockPullSpot;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BlightBrew|Puzzle")
		float PullSpeed = 5.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BlightBrew|Puzzle")
		float DistanceForgiveness = 0.0f;

#pragma region Debug
	//The material to set on the mesh when the rock is in place
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BlightBrew|Puzzle")
		class UMaterialInterface* RockInPlaceMaterial;
#pragma endregion
	

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void OnTrigger();
	bool IsTriggered() { return m_bTriggered; }
	

	
private:
	bool m_bTriggered = false;
	bool m_bRockInPlace = false;
	ABBRollingStone* m_Rock;

};
