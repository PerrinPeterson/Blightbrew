// Copyright © Too Many Eyes , 2022

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "BBFocusTextWidget.generated.h"

class UBorder;
class UTextBlock;
class ABBPlayerCharacter;
/**
 * 
 */
UCLASS()
class BLIGHTBREW_API UBBFocusTextWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
		void SetOwnerCharacter(ABBPlayerCharacter* InCharacter) { OwningCharacter = InCharacter; }
	ABBPlayerCharacter* GetOwnerCharacter() { return OwningCharacter; }

protected:

	UPROPERTY(meta = (BindWidget))
		UBorder* Border;

	UPROPERTY(meta = (BindWidget))
		UTextBlock* FocusTextBlock;


	void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

	void NativeConstruct() override;

private:
	ABBPlayerCharacter* OwningCharacter;
	
};
