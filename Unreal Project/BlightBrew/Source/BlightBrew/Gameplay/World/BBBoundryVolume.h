// Copyright © Too Many Eyes , 2022 - 2023
/*	A Boundry Volume Designed by Perrin Peterson 13/04/2023 
*	This is a Boundry Volume that will be used to keep the player in the level. It will be used with a respawn point to put the player back were they belong.
*	It needs to;
*		- Be a box collider, with an overlap event.
*		- When the player overlaps the boundry volume, they will be teleported to the respawn point.
*		- Hold a reference to the respawn point, that can be set in the editor.
*		- Play a dialogue when the player is teleported.
*		- Fade the players screen to black when they are teleported.
*/

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BBBoundryVolume.generated.h"

UCLASS()
class BLIGHTBREW_API ABBBoundryVolume : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABBBoundryVolume();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Blightbrew|Boundry Volume")
		TSoftObjectPtr<class ABBRespawnPoint> RespawnPoint;

	//Will be hidden in game now
	UPROPERTY(VisibleAnywhere, Category = "Blightbrew|Boundry Volume")
		class UStaticMeshComponent* MeshComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Blightbrew|Boundry Volume")
		class UBoxComponent* BoundryVolume;
	
	UPROPERTY(VisibleAnywhere, Category = "Blightbrew|Boundry Volume")
		class UBBDialogueComponent* DialogueComponent;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	//Overlap Event
	UFUNCTION()
		void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	bool bFadeToBlack;
	bool bFadeBackIn;
	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	

};
