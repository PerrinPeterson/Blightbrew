// Copyright © Too Many Eyes , 2022

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "BBStaminaComponent.generated.h"

UENUM()
enum class ELocomotionMode
{
	Vaulting,
	Climbing,
	Hanging,
	Grounded,
	Falling,
	None,
};

//	FORWARD DECLRATAIONS
class ABBCharacterBase;
class UCharacterMovementComponent;


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BLIGHTBREW_API UBBStaminaComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UBBStaminaComponent();

	void Init();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Stamina, meta = (AllowPrivateAccess = "true"))
		float CurrentStamina;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Stamina, meta = (AllowPrivateAccess = "true"))
		float MaxStamina;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Stamina, meta = (AllowPrivateAccess = "true"))
		float MaxStaminaCache;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Stamina, meta = (AllowPrivateAccess = "true"))
		float IncrementAmount;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Stamina, meta = (AllowPrivateAccess = "true"))
		float DecrementAmount;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Stamina, meta = (AllowPrivateAccess = "true"))
		bool bIsModified;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Stamina, meta = (AllowPrivateAccess = "true"))
		float ModifyTime;

	FTimerHandle ModifyTimerHandle;

	ABBCharacterBase* Character;
	UCharacterMovementComponent* CharacterMovement;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Locomotion, meta = (AllowPrivateAccess = "true"))
		ELocomotionMode LocomotionMode;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Locomotion, meta = (AllowPrivateAccess = "true"))
		bool bIsSprinting;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Locomotion, meta = (AllowPrivateAccess = "true"))
		bool bIsCrouching;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Locomotion, meta = (AllowPrivateAccess = "true"))
		bool bIsVaulting;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Locomotion, meta = (AllowPrivateAccess = "true"))
		bool bIsClimbing;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Locomotion, meta = (AllowPrivateAccess = "true"))
		float MaxRunSpeed;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Locomotion, meta = (AllowPrivateAccess = "true"))
		float MaxWalkSpeed;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Locomotion, meta = (AllowPrivateAccess = "true"))
		float MaxCrouchSpeed;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Locomotion, meta = (AllowPrivateAccess = "true"))
		float CurrentSpeed;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Locomotion, meta = (AllowPrivateAccess = "true"))
		float ZSpeed;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Locomotion, meta = (AllowPrivateAccess = "true"))
		float MovementSpeed;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Locomotion, meta = (AllowPrivateAccess = "true"))
		float JumpCost;

public:
	bool Jump();
	void Vault();
	void EndVault();

	void Climb();
	void ClimbApexReached();
	void ClimbFinish();
	void ClimbAbort();
	void EndClimb();

	void StartSprint();
	void EndSprint();

	void StartCrouch();
	void EndCrouch();

protected:

	//	Must be UFUNCTION for Timer To Work
	UFUNCTION()
		void EndModify();

public:

	UFUNCTION(BlueprintCallable)
		FORCEINLINE float GetStamina() { return CurrentStamina; }

	UFUNCTION(BlueprintCallable)
		FORCEINLINE float GetMaxStamina() { return MaxStamina; }

	UFUNCTION(BlueprintCallable)
		FORCEINLINE void SetMaxStamina(float value) { MaxStamina = value; }

	UFUNCTION(BlueprintCallable)
		FORCEINLINE float GetIncrementAmount() { return IncrementAmount; }

	UFUNCTION(BlueprintCallable)
		FORCEINLINE void SetIncrementAmount(float value) { IncrementAmount = value; }

	UFUNCTION(BlueprintCallable)
		FORCEINLINE float GetDecrementAmount() { return DecrementAmount; }

	UFUNCTION(BlueprintCallable)
		FORCEINLINE void SetDecrementAmount(float value) { DecrementAmount = value; }

	UFUNCTION(BlueprintCallable)
		bool ModifyMaxStamina(float value, float time);

	UFUNCTION(BlueprintCallable)
		FORCEINLINE bool IsSprinting() { return bIsSprinting; }

	UFUNCTION(BlueprintCallable)
		FORCEINLINE bool IsModified() { return bIsModified; }

	UFUNCTION(BlueprintCallable)
		FORCEINLINE bool IsVaulting() { return bIsVaulting; }

	UFUNCTION(BlueprintCallable)
		FORCEINLINE bool IsClimbing() { return bIsClimbing; }

	UFUNCTION(BlueprintCallable)
		void SetMovementSpeed(float value);

	UFUNCTION(BlueprintCallable)
		void ModifyCurrentStamina(float value);

	UFUNCTION(BlueprintCallable)
		FORCEINLINE ELocomotionMode GetLocomotionMode() { return LocomotionMode; }

	UFUNCTION(BlueprintCallable)
		FORCEINLINE float GetCurrentSpeed() { return CurrentSpeed; }
		
};
