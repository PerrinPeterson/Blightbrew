// Copyright © Too Many Eyes , 2022

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "BBMapWidget.generated.h"

class UImage;
/**
 * 
 */
UCLASS()
class BLIGHTBREW_API UBBMapWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY(meta = (BindWidget))
		UImage* Map;

	//UPROPERTY(meta = (BindWidget))
	//	UImage* PlayerIcon;
	
};
