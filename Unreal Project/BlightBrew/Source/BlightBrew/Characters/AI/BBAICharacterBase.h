// Copyright © Too Many Eyes , 2022

#pragma once

#include "CoreMinimal.h"
#include "BlightBrew/Characters/BBCharacterBase.h"
#include "BBAICharacterBase.generated.h"

class UBBDialogueComponent;
/**
 * 
 */
UCLASS()
class BLIGHTBREW_API ABBAICharacterBase : public ABBCharacterBase
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ABBAICharacterBase();
	virtual void Init();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
		UBBDialogueComponent* DialogueComponent;

public:
	virtual void OnFocus(AActor* InstigatingActor) override;
	virtual void OnInteract(AActor* InstigatingActor) override;


	FORCEINLINE virtual void SetFocusText(FText text) override { FocusText = text; }

	FORCEINLINE virtual FText GetFocusText() override { return FocusText; }
	
};
