// Copyright © Too Many Eyes , 2022

#pragma once

#include "CoreMinimal.h"
#include "BlightBrew/Characters/AI/BBAICharacterBase.h"
#include "BBWandererAICharacter.generated.h"

/**
 * 
 */
UCLASS()
class BLIGHTBREW_API ABBWandererAICharacter : public ABBAICharacterBase
{
	GENERATED_BODY()


public:
	// Sets default values for this character's properties
	ABBWandererAICharacter();
	virtual void Init() override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	virtual void OnFocus(AActor* InstigatingActor) override;
	virtual void OnInteract(AActor* InstigatingActor) override;


	FORCEINLINE virtual void SetFocusText(FText text) override { FocusText = text; }

	FORCEINLINE virtual FText GetFocusText() override { return FocusText; }

	FText GetPathToFollow() { return PathToFollow; }

protected:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = AI)
		FText PathToFollow;
	
};
