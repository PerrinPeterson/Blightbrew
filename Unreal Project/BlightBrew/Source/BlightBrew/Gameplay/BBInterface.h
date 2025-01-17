// Copyright © Too Many Eyes , 2022

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "BBInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UBBInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class BLIGHTBREW_API IBBInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:

	virtual void OnFocus(AActor* InstigatingActor) = 0;

	virtual void OnInteract(AActor* InstigatingActor) = 0;

	UFUNCTION(NotBlueprintable)
		virtual void SetFocusText(FText text) = 0;

	UFUNCTION(NotBlueprintable)
		virtual FText GetFocusText() = 0;
};
