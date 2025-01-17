// Copyright © Too Many Eyes , 2022 - 2023

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BBRespawnPoint.generated.h"

UCLASS()
class BLIGHTBREW_API ABBRespawnPoint : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABBRespawnPoint();

	//Mesh, will be hidden in game
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Blightbrew | Respawn Point")
		class UStaticMeshComponent* Mesh;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
