// Copyright © Too Many Eyes , 2022 - 2023

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "BBBlackScreenWidget.generated.h"

/**
 * 
 */
UCLASS()
class BLIGHTBREW_API UBBBlackScreenWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	class UBorder* GetBorder() { return BlackBorder; }

protected:
	virtual void NativeConstruct() override;
	
	UPROPERTY(meta = (BindWidget))
		class UBorder* BlackBorder;
	
};
