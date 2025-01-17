// Copyright © Too Many Eyes , 2022

#pragma once

#include "CoreMinimal.h"
#include "BlightBrew/Gameplay/BBInterface.h"
#include "GameFramework/Character.h"
#include "BBCharacterBase.generated.h"


UENUM()
enum class ScaleType
{
	Vaulting,
	Climbing,
	Grounded,
	None,
};

//	FORWARD DECLARATIONS
class UBBStaminaComponent;


UCLASS()
class BLIGHTBREW_API ABBCharacterBase : public ACharacter, public IBBInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ABBCharacterBase();
	virtual void Init();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Focus)
		FText FocusText;

	//TODO: HEALTH COMPONENT

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Movement)
		UBBStaminaComponent* StaminaComponent;

	UPROPERTY(EditDefaultsOnly)
		USoundBase* JumpFX;

public:
	virtual void OnFocus(AActor* InstigatingActor) override;
	virtual void OnInteract(AActor* InstigatingActor) override;

	UFUNCTION(BlueprintCallable)
		void SetFocusText_BP(FText text);

	FORCEINLINE virtual void SetFocusText(FText text) override { FocusText = text; }

	FORCEINLINE virtual FText GetFocusText() override { return FocusText; }

	//TODO: HEALTH COMPONENT GETTER

	UFUNCTION(BlueprintCallable)
		FORCEINLINE UBBStaminaComponent* GetStaminaComponent() { return StaminaComponent; }

protected:
	virtual void StartJump();
	virtual void StartCrouch();
	virtual void EndCrouch();
	virtual void StartSprint();
	virtual void EndSprint();
	virtual void StartVault();
	virtual void UpdateVault(float DeltaTime);
	virtual void EndVault();

	void StartClimb();
	void UpdateClimb(float DeltaTime);
	void AbortClimb();
	void FinishClimb();
	void EndClimb();

	ScaleType CheckScaleType();

private:
	float PreviousGravity;
	FVector VaultStartLocation;
	FVector VaultApexLocation;
	FVector VaultEndLocation;
	float VaultSpeed;
	bool bHasReachedApex;
	bool bHasReachedEnd;
	bool bHasLeftStart;
	FBox VaultBounds;
};
