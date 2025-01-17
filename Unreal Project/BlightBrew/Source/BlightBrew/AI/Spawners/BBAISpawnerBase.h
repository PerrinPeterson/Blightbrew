// Copyright © Too Many Eyes , 2022

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BBAISpawnerBase.generated.h"

class ABBAICharacterBase;
UCLASS()
class BLIGHTBREW_API ABBAISpawnerBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABBAISpawnerBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "AI")
		TArray<TSubclassOf<ABBAICharacterBase>> AIClasses;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "AI")
		TArray<ABBAICharacterBase*> ManagedAI;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "AI")
		int MaxSpawnAmount;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "AI")
		float SpawnRadius;

};
