// Copyright © Too Many Eyes , 2022

#pragma once

#include "CoreMinimal.h"
#include "BlightBrew/Characters/AI/BBAICharacterBase.h"
#include "BBFaunaAICharacterBase.generated.h"

class ABBFaunaAIController;

UENUM()
enum class EPatrolType
{
	Region,
	Random,
	Path,
	None
};

UENUM()
enum class ETemperamentType
{
	Aggressive,
	Passive,
	Dynamic
};

UENUM()
enum class EConfrontationType
{
	Pursue,
	Flee,
	None
};

/**
 * 
 */
UCLASS()
class BLIGHTBREW_API ABBFaunaAICharacterBase : public ABBAICharacterBase
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ABBFaunaAICharacterBase();
	virtual void Init() override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void Patrol(float DeltaTime);

	void GenerateRandomTarget();

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Fauna AI")
		EPatrolType PatrolType;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Fauna AI")
		ETemperamentType Temperament;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Fauna AI")
		EConfrontationType ConfrontationType;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Fauna AI")
		float MovementSpeed;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Fauna AI")
		float AngerPercent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Fauna AI")
		TSubclassOf<ABBFaunaAIController> ControllerClass;

public:
	virtual void OnFocus(AActor* InstigatingActor) override;
	virtual void OnInteract(AActor* InstigatingActor) override;

	TSubclassOf<ABBFaunaAIController> GetControllerClass();


	FORCEINLINE virtual void SetFocusText(FText text) override { FocusText = text; }

	FORCEINLINE virtual FText GetFocusText() override { return FocusText; }

private:

	FVector CurrentTarget;
	
};
