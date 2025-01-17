// Copyright © Too Many Eyes , 2022

//	BASE CLASS INCLUDE
#include "BlightBrew/Characters/Player/BBPlayerCharacter.h"

//	COMPONENT INCLUDES
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/WidgetComponent.h"
#include "Components/ArrowComponent.h"
#include "Components/SphereComponent.h"

//	FRAMEWORK INCLUDES
#include "GameFramework/InputSettings.h"
#include "Kismet/GameplayStatics.h"

//	DEBUG INCLUDES
#include "DrawDebugHelpers.h"
#include "BlightBrew/Characters/CharacterComponents/BBStaminaComponent.h"
#include "BlightBrew/UI/Stamina/BBStaminaBar.h"


//	BLIGHTBREW INCLUDES
#include "BlightBrew/Inventory/BBInventoryComponent.h"
#include "BlightBrew/Items/BBBaseItem.h"

//	WIDGET INCLUDES
#include "BlightBrew/Shop/BBShopper.h"
#include "BlightBrew/UI/Journal/BBJournalWidget.h"
#include "BlightBrew/UI/Pause/BBPauseMenuWidget.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "BlightBrew/UI/BBHUD.h"
#include "Components/AudioComponent.h"

ABBPlayerCharacter::ABBPlayerCharacter()
{
	//	IF SERVER SIDE
	//if(HasAuthority())	//UNCOMMENT IF MULTIPLAYER
	{
		Init();
	}

}

void ABBPlayerCharacter::Init()
{
	Super::Init();
	BaseTurnRate = 45.f;
	BaseLookUpRate = 45.f;
	XSensitivity = 1.0f;
	YSensitivity = 1.0f;
	InvertY = true;

#pragma region SpringArm
	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComponent"));
	SpringArmComponent->SetupAttachment(GetCapsuleComponent());
	SpringArmComponent->bUsePawnControlRotation = true;
#pragma endregion SpringArm

#pragma region Camera
	ThirdPersonCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("ThirdPersonCamera"));
	ThirdPersonCameraComponent->SetupAttachment(SpringArmComponent);
	ThirdPersonCameraComponent->bUsePawnControlRotation = false;

	Unlocked_CameraPosition = CreateDefaultSubobject<UArrowComponent>(TEXT("UnlockedCameraPosition"));
	Unlocked_CameraPosition->SetupAttachment(RootComponent);

	CameraPosition = Unlocked_CameraPosition->GetRelativeTransform().GetLocation();

	Locked_CameraPosition = CreateDefaultSubobject<UArrowComponent>(TEXT("LockedCameraPosition"));
	Locked_CameraPosition->SetupAttachment(RootComponent);
#pragma endregion Camera

#pragma region Hands

	HandLSphere = CreateDefaultSubobject<USphereComponent>(TEXT("Left Hand Sphere"));
	HandLSphere->SetSphereRadius(15.0f);
	HandLSphere->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	HandLSphere->SetupAttachment(GetMesh(), "HandLSocket");

	HandRSphere = CreateDefaultSubobject<USphereComponent>(TEXT("Right Hand Sphere"));
	HandRSphere->SetSphereRadius(15.0f);
	HandLSphere->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	HandRSphere->SetupAttachment(GetMesh(), "HandRSocket");

#pragma endregion Hands

#pragma region Inventory
	InventoryComponent = CreateDefaultSubobject<UBBInventoryComponent>(TEXT("InventoryComponent"));
	QuickSlotIndex = 0;
	Currency = 0;
#pragma endregion Inventory

#pragma region StaminaWidget
	StaminaWidgetComp = CreateDefaultSubobject<UWidgetComponent>(TEXT("StaminaBar"));
	StaminaWidgetComp->SetupAttachment(RootComponent);
#pragma endregion StaminaWidget

	bIsInMenu = false;

	bCanFootstepFXPlay = true;
	FootstepDelayTime = 0.25f;

	MusicComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("MusicComponent"));
	MusicComponent->OnAudioFinished.AddDynamic(this, &ABBPlayerCharacter::OnMusicFinished);


	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;
	GetCharacterMovement()->bOrientRotationToMovement = true;
	CameraState = ECameraState::Unlocked;
}

void ABBPlayerCharacter::OnMusicFinished()
{
	if (Music.Num() > 0)
	{
		int index = FMath::RandRange(0, Music.Num() - 1);

		MusicComponent->Sound = Music[index];
		MusicComponent->Play();
	}
}

void ABBPlayerCharacter::AllowFootstep()
{
	bCanFootstepFXPlay = true;
}

void ABBPlayerCharacter::PlayFootstep()
{
	if (FootstepFX != nullptr
		&& bCanFootstepFXPlay
		&& !GetCharacterMovement()->IsFalling())
	{
		bCanFootstepFXPlay = false;

		FVector fxLocation = GetActorLocation();
		fxLocation.Z -= GetCapsuleComponent()->GetScaledCapsuleHalfHeight() * 2;

		float volume = FMath::FRandRange(0.01f, 0.1f);
		float pitch = FMath::FRandRange(0.75f, 1.0f);

		UGameplayStatics::PlaySoundAtLocation(this, 
			FootstepFX, 
			fxLocation,
			volume,
			pitch);

		GetWorld()->GetTimerManager().SetTimer(FootstepTimer,
			this,
			&ABBPlayerCharacter::AllowFootstep, FootstepDelayTime,
			false);
	}
}

bool ABBPlayerCharacter::CanInput()
{
	if(bIsInMenu
		|| bIsInDialogue)
	{
		return false;
	}

	return true;
}

void ABBPlayerCharacter::DialogueInput()
{
	HUD->DialogueInput();
}

void ABBPlayerCharacter::ChangeCameraState(ECameraState state)
{
	CameraState = state;

	if(CameraState == ECameraState::Locked)
	{
		bUseControllerRotationPitch = false;
		bUseControllerRotationYaw = true;
		bUseControllerRotationRoll = true;
		GetCharacterMovement()->bOrientRotationToMovement = false;


		CameraPosition = Locked_CameraPosition->GetRelativeTransform().GetLocation();
		//CameraPosition = Locked_CameraPosition->GetComponentLocation();
	}
	else if (CameraState == ECameraState::Unlocked)
	{
		bUseControllerRotationPitch = false;
		bUseControllerRotationYaw = false;
		bUseControllerRotationRoll = false;
		GetCharacterMovement()->bOrientRotationToMovement = true;

		CameraPosition = Unlocked_CameraPosition->GetRelativeTransform().GetLocation();
		//CameraPosition = Unlocked_CameraPosition->GetComponentLocation();
	}
}

void ABBPlayerCharacter::HandLOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{

	if(OtherActor != this)
	{
		//UE_LOG(LogTemp, Warning, TEXT("Left Hand Overlapped"));

		HandLSphere->SetHiddenInGame(false);

		if (OtherActor->ActorHasTag("Climbable"))
		{
			//UE_LOG(LogTemp, Warning, TEXT("Hit is Climbable"));

			/*DrawDebugSphere(GetWorld(),
				HandLSphere->GetComponentLocation(),
				HandLSphere->GetScaledSphereRadius(),
				6,
				FColor::Cyan,
				false,
				5.0f,
				2.0f);*/
		}
	}

}

void ABBPlayerCharacter::HandLOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	HandLSphere->SetHiddenInGame(true);
}

void ABBPlayerCharacter::HandROverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	HandRSphere->SetHiddenInGame(true);
}

void ABBPlayerCharacter::HandROverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                                           UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{

	if(OtherActor != this)
	{
		//UE_LOG(LogTemp, Warning, TEXT("Right Hand Overlapped"));

		HandRSphere->SetHiddenInGame(false);

		if (OtherActor->ActorHasTag("Climbable"))
		{
			//UE_LOG(LogTemp, Warning, TEXT("Hit is Climbable"));

			/*DrawDebugSphere(GetWorld(),
				HandRSphere->GetComponentLocation(),
				HandRSphere->GetScaledSphereRadius(),
				6,
				FColor::Cyan,
				false,
				5.0f,
				2.0f);*/
		}
	}

}

void ABBPlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	GetWorld()->GetFirstPlayerController()->Possess(this);

	UBBStaminaBar* StaminaBar = Cast<UBBStaminaBar>(StaminaWidgetComp->GetUserWidgetObject());
	StaminaBar->SetOwnerCharacter(this);

	if (Music.Num() > 0)
	{
		int index = FMath::RandRange(0, Music.Num() - 1);

		//UGameplayStatics::PlaySound2D(this,
		//	Music[index]);

		MusicComponent->Sound = Music[index];
		MusicComponent->Play();

		//MusicComponent->OnAudioFinished.AddDynamic(this, &ABBPlayerCharacter::OnMusicFinished);
	}

	if (APlayerController* control = Cast<APlayerController>(Controller))
	{
		//control->SetPause(true);
		control->SetInputMode(FInputModeUIOnly());
		control->SetShowMouseCursor(true);
		//HUD->TogglePause(true);
		bIsInMenu = true;
	}

	HUD = Cast<ABBHUD>(GetWorld()->GetFirstPlayerController()->GetHUD());
	HUD->LateBeginPlay();

	HandLSphere->OnComponentBeginOverlap.AddDynamic(this, &ABBPlayerCharacter::HandLOverlapBegin);
	HandLSphere->OnComponentEndOverlap.AddDynamic(this, &ABBPlayerCharacter::HandLOverlapEnd);
	HandRSphere->OnComponentBeginOverlap.AddDynamic(this, &ABBPlayerCharacter::HandROverlapBegin);
	HandRSphere->OnComponentEndOverlap.AddDynamic(this, &ABBPlayerCharacter::HandROverlapEnd);

	//UnPause();

	
}

void ABBPlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);


	CheckFocus();

	UpdateCamera();
}

void ABBPlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	// Assert the Input Component is Valid first
	check(PlayerInputComponent);

	//	Pass the input component to parent(s)
	Super::SetupPlayerInputComponent(PlayerInputComponent);

#pragma region LocomotionActions
	//	Bind Locomotion Actions
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ABBPlayerCharacter::StartJump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);
	PlayerInputComponent->BindAction("Sprint", IE_Pressed, this, &ABBPlayerCharacter::StartSprint);
	PlayerInputComponent->BindAction("Sprint", IE_Released, this, &ABBPlayerCharacter::EndSprint);
	PlayerInputComponent->BindAction("Crouch", IE_Pressed, this, &ABBPlayerCharacter::StartCrouch);
#pragma endregion LocomotionActions

#pragma region LocomotionAxes
	// Bind Locomotion Axes
	PlayerInputComponent->BindAxis("MoveForward", this, &ABBPlayerCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ABBPlayerCharacter::MoveRight);
	PlayerInputComponent->BindAxis("Turn", this, &ABBPlayerCharacter::Turn);
	PlayerInputComponent->BindAxis("TurnRate", this, &ABBPlayerCharacter::TurnAtRate);
	PlayerInputComponent->BindAxis("LookUp", this, &ABBPlayerCharacter::LookUp);
	PlayerInputComponent->BindAxis("LookUpRate", this, &ABBPlayerCharacter::LookUpAtRate);
#pragma endregion LocomotionAxes

#pragma region InteractionActions
	// Bind Interaction Actions
	PlayerInputComponent->BindAction("Interact", IE_Pressed, this, &ABBPlayerCharacter::Interact);
	PlayerInputComponent->BindAction("Primary", IE_Pressed, this, &ABBPlayerCharacter::Primary);
	PlayerInputComponent->BindAction("Secondary", IE_Pressed, this, &ABBPlayerCharacter::Secondary);
	PlayerInputComponent->BindAction("Secondary", IE_Released, this, &ABBPlayerCharacter::Secondary_Release);

#pragma endregion InteractionActions

#pragma region UIActions
	// Bind Interaction Actions
	PlayerInputComponent->BindAction("Journal", IE_Pressed, this, &ABBPlayerCharacter::OnJournal);
	PlayerInputComponent->BindAction("Map", IE_Pressed, this, &ABBPlayerCharacter::OnMap);
	PlayerInputComponent->BindAction("Inventory", IE_Pressed, this, &ABBPlayerCharacter::OnInventory);
	PlayerInputComponent->BindAction("Pause", IE_Pressed, this, &ABBPlayerCharacter::OnPause);
	//To close any open menu
	PlayerInputComponent->BindAction("CloseMenu", IE_Pressed, this, &ABBPlayerCharacter::OnCloseMenu);

#pragma endregion UIActions

#pragma region InventoryActions
	//	Bind QuickSlot Actions
	PlayerInputComponent->BindAction("QuickSlot1", IE_Pressed, this, &ABBPlayerCharacter::QuickSlot1);
	PlayerInputComponent->BindAction("QuickSlot2", IE_Pressed, this, &ABBPlayerCharacter::QuickSlot2);
	PlayerInputComponent->BindAction("QuickSlot3", IE_Pressed, this, &ABBPlayerCharacter::QuickSlot3);
	PlayerInputComponent->BindAction("QuickSlot4", IE_Pressed, this, &ABBPlayerCharacter::QuickSlot4);
	PlayerInputComponent->BindAction("NextQuickSlot", IE_Pressed, this, &ABBPlayerCharacter::NextQuickSlot);
	PlayerInputComponent->BindAction("PreviousQuickSlot", IE_Pressed, this, &ABBPlayerCharacter::PreviousQuickSlot);
	PlayerInputComponent->BindAction("DropItem", IE_Pressed, this, &ABBPlayerCharacter::DropItem);

#pragma endregion InventoryActions
}

void ABBPlayerCharacter::RefreshHudVisibility()
{
	bIsInMenu = HUD->GetIsMenuOpen();
}

UBBBlackScreenWidget* ABBPlayerCharacter::GetBlackScreenWidget()
{
	return HUD->GetBlackScreenWidget();
}

void ABBPlayerCharacter::StopSprint()
{
	if (StaminaComponent->IsSprinting()) 
		EndSprint();
}

void ABBPlayerCharacter::StartJump()
{
	if (CanInput())
	{
		Super::StartJump();


	}
	

}

void ABBPlayerCharacter::StartCrouch()
{
	if (CanInput())
	{
		Super::StartCrouch();
	}

}

void ABBPlayerCharacter::EndCrouch()
{
	if (CanInput())
	{
		Super::EndCrouch();
	}
}

void ABBPlayerCharacter::StartSprint()
{
	if (CanInput())
	{
		Super::StartSprint();
		FootstepDelayTime /= 2;
	}
}

void ABBPlayerCharacter::EndSprint()
{
	if (CanInput())
	{
		Super::EndSprint();
		FootstepDelayTime *= 2;
	}
}

void ABBPlayerCharacter::StartVault()
{
	Super::StartVault();

}

void ABBPlayerCharacter::EndVault()
{
	Super::EndVault();

	ChangeCameraState(ECameraState::Unlocked);
}

void ABBPlayerCharacter::StartFocus()
{
	bIsFocusing = true;
}

void ABBPlayerCharacter::EndFocus()
{
	bIsFocusing = false;
}

bool ABBPlayerCharacter::CanMove()
{
	if(CanInput())
	{
		return true;
	}

	return false;
}

void ABBPlayerCharacter::Interact()
{
	if(CanInput())
	{
		FHitResult hitResult;
		FVector traceStart = GetActorLocation();
		FVector traceEnd = traceStart + (GetControlRotation().Vector() * 500.0f);
		FCollisionQueryParams params;
		params.AddIgnoredActor(this);

		GetWorld()->LineTraceSingleByChannel(hitResult, traceStart, traceEnd, ECC_WorldDynamic, params);

		/*DrawDebugLine(GetWorld(),
			traceStart,
			traceEnd,
			FColor::Red,
			false,
			1,
			0,
			5);*/

		if (hitResult.GetActor())
		{
			if (IBBInterface* interactable = Cast<IBBInterface>(hitResult.GetActor()))
			{
				//UE_LOG(LogTemp, Warning, TEXT("Interaction Hit."));
				if(ABBShopper* shopper = Cast<ABBShopper>(interactable))
				{
					if(shopper->m_isWaiting)
					{
						interactable->OnInteract(this);
					}
				}
				else
				{
					interactable->OnInteract(this);
				}

				
			}	//ENDIF

		}	//ENDIF
	}

	if(bIsInDialogue)
	{
		//DialogueInput();
	}
	
}

void ABBPlayerCharacter::CheckFocus()
{
	if(CanInput())
	{
		FHitResult hitResult;
		FVector traceStart = GetActorLocation();
		FVector traceEnd = traceStart + (GetControlRotation().Vector() * 500.0f);
		FCollisionQueryParams params;
		params.AddIgnoredActor(this);

		GetWorld()->LineTraceSingleByChannel(hitResult, traceStart, traceEnd, ECC_WorldDynamic, params);

		/*DrawDebugLine(GetWorld(),
			traceStart,
			traceEnd,
			FColor::Blue,
			false,
			0.1f,
			0,
			1.0f);*/

		//	If the raycast hit
		if (hitResult.GetActor())
		{
			// If the hit actor is interactable
			if (IBBInterface* interactable = Cast<IBBInterface>(hitResult.GetActor()))
			{
				interactable->OnFocus(this);
				// TODO: ADD RESULT FILTERING
				{
					FocusText = interactable->GetFocusText();
					StartFocus();
				}	//	END ELSE
			}	//	END IF
			else
			{
				EndFocus();
			}
		}	//	END IF
		else
		{
			EndFocus();
		}
	}
	else
	{
		EndFocus();
	}
	
}

void ABBPlayerCharacter::Primary()
{
	if(CanInput())
	{
		//UE_LOG(LogTemp, Warning, TEXT("Primary fired"));
		//TODO: Add Inventory Item Usage
		//InventoryComponent->UseItemInSlot(0, this);
		//TESTING PURPOSES ONLY - Needs to be better than this lol
		InventoryComponent->UseItemInQuickSlot(QuickSlotIndex, this);
	}

	if(bIsInDialogue)
	{
		//DialogueInput();
	}

}

void ABBPlayerCharacter::Secondary()
{

	if(!StaminaComponent->IsClimbing())
	{
		ChangeCameraState(ECameraState::Locked);
	}
	

}

void ABBPlayerCharacter::Secondary_Release()
{
	ChangeCameraState(ECameraState::Unlocked);
}

void ABBPlayerCharacter::Zoom()
{
	if(!bIsInMenu)
	{
		SpringArmComponent->TargetArmLength = 100.0f;
	}

}

void ABBPlayerCharacter::UnZoom()
{
	if(!bIsInMenu)
	{
		SpringArmComponent->TargetArmLength = 300.0f;
	}

}

void ABBPlayerCharacter::QuickSlot1()
{
	ChangeQuickSlot(0);
}

void ABBPlayerCharacter::QuickSlot2()
{
	ChangeQuickSlot(1);
}

void ABBPlayerCharacter::QuickSlot3()
{
	ChangeQuickSlot(2);
}

void ABBPlayerCharacter::QuickSlot4()
{
	//ChangeQuickSlot(3);
}

void ABBPlayerCharacter::NextQuickSlot()
{
	ChangeQuickSlot(QuickSlotIndex + 1);
}

void ABBPlayerCharacter::PreviousQuickSlot()
{
	ChangeQuickSlot(QuickSlotIndex - 1);
}

void ABBPlayerCharacter::DropItem()
{
	InventoryComponent->DropItem(InventoryComponent->GetQuickSlots()[QuickSlotIndex]);
}

void ABBPlayerCharacter::ChangeQuickSlot(int slotNum)
{
	//	If the range is above the maximum
	if (slotNum > 2)
	{
		//	Go back to the beginning
		QuickSlotIndex = 0;
	}
	//	If the range is below the minimum
	else if (slotNum < 0)
	{
		// Go back to the end
		QuickSlotIndex = 2;
	}
	else
	{
		//	 Set the current index (visual) to the slot num
		QuickSlotIndex = slotNum;
	}
}

void ABBPlayerCharacter::MoveForward(float val)
{
	if (val != 0.0f
		&& CanInput())
	{
		if (StaminaComponent->GetLocomotionMode() == ELocomotionMode::Climbing)
		{
			//AddMovementInput(GetActorUpVector(), val);

			FVector newLoc = GetActorLocation();
			newLoc.Z += val;
			SetActorLocation(newLoc);
		}
		else
		{
			switch (CameraState)
			{
				case ECameraState::Locked:
				{
					AddMovementInput(GetActorForwardVector(), val);
				}
				case ECameraState::Unlocked:
				{
					//	Find out which way is forward
					const FRotator rotation = Controller->GetControlRotation();
					const FRotator yawRotation(0, rotation.Yaw, 0);

					//	Get forward vector
					const FVector direction = FRotationMatrix(yawRotation).GetUnitAxis(EAxis::X);

					//	Add movement in that direction
					AddMovementInput(direction, val);
				}
			}


			PlayFootstep();
		}

	}
}

void ABBPlayerCharacter::MoveRight(float val)
{
	if (val != 0.0f
		&& CanInput()
		&& StaminaComponent->GetLocomotionMode() != ELocomotionMode::Climbing)
	{
		switch (CameraState)
		{
			case ECameraState::Locked:
			{
				AddMovementInput(GetActorRightVector(), val);
			}
			case ECameraState::Unlocked:
			{
				//	Find out which way is right
				const FRotator rotation = Controller->GetControlRotation();
				const FRotator yawRotation(0, rotation.Yaw, 0);

				//	Get right vector 
				const FVector direction = FRotationMatrix(yawRotation).GetUnitAxis(EAxis::Y);

				//	Add movement in that direction
				AddMovementInput(direction, val);
			}
		}
		PlayFootstep();
	}
}

void ABBPlayerCharacter::TurnAtRate(float rate)
{
	if(!bIsInMenu)
	{
		AddControllerYawInput(rate * BaseTurnRate * GetWorld()->GetDeltaSeconds());
	}
	
}

void ABBPlayerCharacter::LookUpAtRate(float rate)
{
	if(!bIsInMenu)
	{
		AddControllerPitchInput(rate * BaseLookUpRate * GetWorld()->GetDeltaSeconds());
	}
	
}

void ABBPlayerCharacter::Turn(float val)
{
	if(val != 0)
	{
		AddControllerYawInput(val * XSensitivity);
	}
}

void ABBPlayerCharacter::LookUp(float val)
{
	if (val != 0)
	{
		if(InvertY)
		{
			val *= -1;
		}
		else
		{
			val *= 1;
		}

		AddControllerPitchInput(val * YSensitivity);
	}
}

void ABBPlayerCharacter::OnPause()
{
	/*if(bIsInMenu)
	{
		HUD->ToggleJournal();
		bIsInMenu = HUD->GetIsMenuOpen();
	}
	else*/
	{
		APlayerController* control = Cast<APlayerController>(Controller);
		if (control->IsPaused())
		{
			UnPause();
		}

		if (!control->IsPaused())
		{
			Pause();
		}
	}


}

void ABBPlayerCharacter::Pause()
{
	if(APlayerController* control = Cast<APlayerController>(Controller))
	{
		if (bIsInMenu)
			return;
		control->SetPause(true);
		control->SetInputMode(FInputModeUIOnly());
		control->SetShowMouseCursor(true);
		HUD->TogglePause(true);
		bIsInMenu = true;
	}

}

void ABBPlayerCharacter::UpdateCamera()
{
	if(SpringArmComponent->GetRelativeTransform().GetLocation() != CameraPosition)
	{
		SpringArmComponent->GetRelativeTransform().SetLocation(FMath::Lerp(SpringArmComponent->GetRelativeTransform().GetLocation(), CameraPosition, 0.5f));
	}
}

void ABBPlayerCharacter::UnPause()
{
	if(APlayerController* control = Cast<APlayerController>(Controller))
	{
		control->SetPause(false);
		control->SetInputMode(FInputModeGameOnly());
		control->SetShowMouseCursor(false);
		HUD->TogglePause(false);
		bIsInMenu = false;
	}

}

void ABBPlayerCharacter::ToggleInputMode(EInputMode inputMode)
{
	APlayerController* control = Cast<APlayerController>(Controller);
	switch (inputMode)
	{
	case EInputMode::GameAndUI:
	{
		control->SetInputMode(FInputModeGameAndUI());
		control->SetShowMouseCursor(true);
		break;
	}
	case EInputMode::GameOnly:
	{
		control->SetInputMode(FInputModeGameOnly());
		control->SetShowMouseCursor(false);
		break;
	}
	case EInputMode::UIOnly:
	{
		control->SetInputMode(FInputModeUIOnly());
		control->SetShowMouseCursor(true);
		break;
	}
	case EInputMode::NoInput:
	{
		control->SetInputMode(FInputModeUIOnly());
		control->SetShowMouseCursor(false);
		break;
	}
	}
}

void ABBPlayerCharacter::ModifyMouseSensitivity(float mouseX, float mouseY)
{
	XSensitivity = mouseX;
	YSensitivity = mouseY;
}

void ABBPlayerCharacter::OnJournal()
{
	HUD->ToggleJournal();
	bIsInMenu = HUD->GetIsMenuOpen(); 
}

void ABBPlayerCharacter::OnInventory()
{
	//HUD->SwitchJournalPage(EJournalWidgetType::Inventory);
	HUD->ToggleInventory();
	bIsInMenu = HUD->GetIsMenuOpen();
}

void ABBPlayerCharacter::OnMap()
{
	//HUD->SwitchJournalPage(EJournalWidgetType::Map);
	HUD->ToggleMap();
	bIsInMenu = HUD->GetIsMenuOpen();
}

void ABBPlayerCharacter::OnCloseMenu()
{
	if (bIsInMenu)
	{
		HUD->CloseOpenMenu();
		bIsInMenu = HUD->GetIsMenuOpen();
	}
}

void ABBPlayerCharacter::OnFocus(AActor* InstigatingActor)
{
	//Super::OnFocus(InstigatingActor);
}

void ABBPlayerCharacter::OnInteract(AActor* InstigatingActor)
{
	//Super::OnInteract(InstigatingActor);
}

void ABBPlayerCharacter::StartDialogue()
{
	bIsInDialogue = true;
	ToggleInputMode(EInputMode::UIOnly);


}

void ABBPlayerCharacter::EndDialogue()
{
	bIsInDialogue = false;
	ToggleInputMode(EInputMode::GameOnly);
}
