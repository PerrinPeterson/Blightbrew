// Copyright © Too Many Eyes , 2022

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "BBQuickSlotWidget.generated.h"

class UBBInventorySlotWidget;
class UBorder;
class ABBPlayerCharacter;
/**
 * 
 */
UCLASS(Abstract)
class BLIGHTBREW_API UBBQuickSlotWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	void SetOwnerCharacter(ABBPlayerCharacter* InCharacter) { OwningCharacter = InCharacter; }

	ABBPlayerCharacter* GetOwnerCharacter() { return OwningCharacter; }

	void DisableQuickslotButtons();
	void EnableQuickslotButtons();


protected:

	ABBPlayerCharacter* OwningCharacter;

	UPROPERTY(meta = (BindWidget))
		UBBInventorySlotWidget* QuickSlotWidget1;

	UPROPERTY(meta = (BindWidget))
		UBBInventorySlotWidget* QuickSlotWidget2;

	UPROPERTY(meta = (BindWidget))
		UBBInventorySlotWidget* QuickSlotWidget3;

	void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

	void NativeConstruct() override;

	
};
