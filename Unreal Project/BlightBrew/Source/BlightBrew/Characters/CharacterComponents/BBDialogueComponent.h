// Copyright © Too Many Eyes , 2022

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "BBDialogueComponent.generated.h"

class ABBPlayerCharacter;
UENUM(BlueprintType)
enum class EDialogueOptionType : uint8
{
	Barter				UMETA(DisplayName = "Barter"),
	Sell				UMETA(DisplayName = "Sell"),
	Next				UMETA(DisplayName = "Next"),
	End					UMETA(DisplayName = "End"),
	Count
};

USTRUCT(BlueprintType)
struct FDialogueOption
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		FString Dialogue;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		EDialogueOptionType OptionType;


	void OnClicked();
};

USTRUCT(BlueprintType)
struct FDialogue
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		FString Dialogue;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		TArray<FDialogueOption> DialogueOptions;
};


UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class BLIGHTBREW_API UBBDialogueComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UBBDialogueComponent();

	//void OnDialogueBegin();

	//UBBDialogue* GetNextDialogue();

	TArray<FDialogue> GetDialogues() { return Dialogues; }

	void OnInteract(ABBPlayerCharacter* instigator);

	void PlayDialogueOneShot();

	UFUNCTION(BlueprintCallable)
	FORCEINLINE FText GetName() { return SpeakerName; }

	UFUNCTION(BlueprintCallable)
		FORCEINLINE void SetName(FText name) { SpeakerName = name; }

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FText SpeakerName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TArray<FDialogue> Dialogues;

	ABBPlayerCharacter* Player = nullptr;

	UPROPERTY(EditDefaultsOnly)
		USoundBase* DialogueOneShotFX;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;


};
