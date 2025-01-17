// Copyright © Too Many Eyes , 2022

#pragma once

#include "CoreMinimal.h"
#include "BlightBrew/Characters/BBCharacterBase.h"
#include "BBPlayerCharacter.generated.h"

class USphereComponent;
class USoundCue;
//	FORWARD DECLARATIONS
class UCameraComponent;
class USpringArmComponent;
class UBBInventoryComponent;

UENUM()
enum class EInputMode
{
	GameOnly,
	UIOnly,
	GameAndUI,
	NoInput
};

UENUM()
enum class ECameraState
{
	Unlocked,
	Locked
};

/**
 *
 */
UCLASS()
class BLIGHTBREW_API ABBPlayerCharacter : public ABBCharacterBase
{
	GENERATED_BODY()

public:
	ABBPlayerCharacter();

	virtual void Init() override;

private:
	/** Third person SA */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		USpringArmComponent* SpringArmComponent;

	/** Third person camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		UCameraComponent* ThirdPersonCameraComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Inventory, meta = (AllowPrivateAccess = "true"))
		UBBInventoryComponent* InventoryComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Camera, meta = (AllowPrivateAccess = "true"))
		UArrowComponent* Unlocked_CameraPosition;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Camera, meta = (AllowPrivateAccess = "true"))
		UArrowComponent* Locked_CameraPosition;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Camera, meta = (AllowPrivateAccess = "true"))
		FVector CameraPosition;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Hands, meta = (AllowPrivateAccess = "true"))
		USphereComponent* HandLSphere;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Hands, meta = (AllowPrivateAccess = "true"))
		USphereComponent* HandRSphere;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Focus, meta = (AllowPrivateAccess = "true"))
		bool bIsFocusing;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Inventory, meta = (AllowPrivateAccess = "true"))
		int QuickSlotIndex;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Inventory, meta = (AllowPrivateAccess = "true"))
		int Currency;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = UI, meta = (AllowPrivateAccess = "true"))
		bool bIsInMenu;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = UI, meta = (AllowPrivateAccess = "true"))
		bool bIsInDialogue;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = UI, meta = (AllowPrivateAccess = "true"))
		bool bIsPaused;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Locomotion, meta = (AllowPrivateAccess = "true"))
		bool bIsClimbing;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Locomotion, meta = (AllowPrivateAccess = "true"))
		bool bIsTeleporting;

protected:
	UPROPERTY(VisibleAnywhere)
		class UWidgetComponent* StaminaWidgetComp;

	UPROPERTY(EditDefaultsOnly)
		class ABBHUD* HUD;


	UPROPERTY(EditDefaultsOnly)
		TArray<USoundBase*> Music;

	UAudioComponent* MusicComponent;

	UFUNCTION()
		void OnMusicFinished();

	UPROPERTY(EditDefaultsOnly)
		USoundBase* FootstepFX;

	FTimerHandle FootstepTimer;

	float FootstepDelayTime;

	bool bCanFootstepFXPlay;

	void AllowFootstep();
	void PlayFootstep();

	bool CanInput();

	void DialogueInput();

	UPROPERTY(EditDefaultsOnly)
		ECameraState CameraState;

	void ChangeCameraState(ECameraState state);

	UFUNCTION()
		void HandLOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
			UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
		void HandLOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
			UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	UFUNCTION()
		void HandROverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
			UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
		void HandROverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
			UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);



protected:
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UCameraComponent* GetThirdPersonCameraComponent() const { return ThirdPersonCameraComponent; }

	UBBInventoryComponent* GetInventoryComponent() { return InventoryComponent; }

	//Needed so I can open a crafting menu from the crafter.
	ABBHUD* GetPlayerHud() { return HUD; }
	void RefreshHudVisibility();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
		float BaseTurnRate;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
		float BaseLookUpRate;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
		float XSensitivity;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
		float YSensitivity;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
		bool InvertY;

	//For the fade to black functionality of the world borders.
	class UBBBlackScreenWidget* GetBlackScreenWidget();

	void StopSprint();
	bool IsTeleporting() { return bIsTeleporting; }
	void ToggleIsTeleporting() { bIsTeleporting = !bIsTeleporting; }

protected:

	virtual void StartJump() override;
	virtual void StartCrouch() override;
	virtual void EndCrouch() override;
	virtual void StartSprint() override;
	virtual void EndSprint() override;

	virtual void StartVault() override;
	virtual void EndVault() override;

	void StartFocus();
	void EndFocus();

	bool CanMove();

	void Interact();
	void CheckFocus();

	void Primary();
	void Secondary();
	void Secondary_Release();

	void Zoom();
	void UnZoom();

	void QuickSlot1();
	void QuickSlot2();
	void QuickSlot3();
	void QuickSlot4();

	void NextQuickSlot();
	void PreviousQuickSlot();

	void DropItem();

	void ChangeQuickSlot(int slotNum);

	void MoveForward(float val);
	void MoveRight(float val);

	void TurnAtRate(float rate);
	void LookUpAtRate(float rate);

	void Turn(float val);
	void LookUp(float val);

	void OnPause();
	void Pause();

	void UpdateCamera();

public:
	void UnPause();

	void ToggleInputMode(EInputMode inputMode);

	void ModifyMouseSensitivity(float mouseX, float mouseY);

	void ModifyXSensitivity(float mouseX) { XSensitivity = mouseX; }
	void ModifyYSensitivity(float mouseY) { YSensitivity = mouseY; }

protected:

	void OnJournal();
	void OnInventory();
	void OnMap();
	void OnCloseMenu();

public:
	virtual void OnFocus(AActor* InstigatingActor) override;
	virtual void OnInteract(AActor* InstigatingActor) override;

	UFUNCTION(BlueprintCallable)
		FORCEINLINE bool IsFocusing() { return bIsFocusing; }

	UFUNCTION(BlueprintCallable)
		FORCEINLINE bool IsInMenu() { return bIsInMenu; }

	UFUNCTION(BlueprintCallable)
		FORCEINLINE void SetIsInMenu(bool isInMenu) { bIsInMenu = isInMenu; }

	UFUNCTION(BlueprintCallable)
		void StartDialogue();

	UFUNCTION(BlueprintCallable)
		void EndDialogue();

	UFUNCTION(BlueprintCallable)
		FORCEINLINE bool IsInDialogue() { return bIsInDialogue; }

	UFUNCTION(BlueprintCallable)
		FORCEINLINE int GetQuickSlotIndex() { return QuickSlotIndex; }

	UFUNCTION(BlueprintCallable)
		FORCEINLINE int GetCurrency() { return Currency; }

	UFUNCTION(BlueprintCallable)
		FORCEINLINE void SetCurrency(int value) { Currency = value; }

	ABBHUD* GetHUD() { return HUD; }


};
