// Copyright © Too Many Eyes , 2022


#include "BlightBrew/UI/Settings/Control/BBControlSettingsWidget.h"

#include "BlightBrew/Characters/Player/BBPlayerCharacter.h"
#include "Components/Slider.h"
#include "Components/CheckBox.h"

void UBBControlSettingsWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	if (ABBPlayerCharacter* PC = Cast<ABBPlayerCharacter>(GetGameInstance()->GetFirstGamePlayer()->GetPlayerController(GetWorld())->GetPawn()))
	{
		MouseXSlider->Value = PC->XSensitivity;
		MouseYSlider->Value = PC->YSensitivity;

		InvertYCheckBox->SetIsChecked(PC->InvertY);
	}
}

void UBBControlSettingsWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (ABBPlayerCharacter* PC = Cast<ABBPlayerCharacter>(GetGameInstance()->GetFirstGamePlayer()->GetPlayerController(GetWorld())->GetPawn()))
	{
		MouseXSlider->Value = PC->XSensitivity;
		MouseYSlider->Value = PC->YSensitivity;

		InvertYCheckBox->SetIsChecked(PC->InvertY);
	}

	MouseXSlider->OnValueChanged.AddDynamic(this, &UBBControlSettingsWidget::OnMouseXChanged);
	MouseYSlider->OnValueChanged.AddDynamic(this, &UBBControlSettingsWidget::OnMouseYChanged);

	InvertYCheckBox->OnCheckStateChanged.AddDynamic(this, &UBBControlSettingsWidget::OnInvertYChanged);
}

void UBBControlSettingsWidget::OnMouseXChanged(float Value)
{
	if(ABBPlayerCharacter* PC = Cast<ABBPlayerCharacter>(GetGameInstance()->GetFirstGamePlayer()->GetPlayerController(GetWorld())->GetPawn()))
	{
		PC->ModifyXSensitivity(Value);
	}
}

void UBBControlSettingsWidget::OnMouseYChanged(float Value)
{
	if (ABBPlayerCharacter* PC = Cast<ABBPlayerCharacter>(GetGameInstance()->GetFirstGamePlayer()->GetPlayerController(GetWorld())->GetPawn()))
	{
		PC->ModifyYSensitivity(Value);
	}
}

void UBBControlSettingsWidget::OnInvertYChanged(bool state)
{
	if (ABBPlayerCharacter* PC = Cast<ABBPlayerCharacter>(GetGameInstance()->GetFirstGamePlayer()->GetPlayerController(GetWorld())->GetPawn()))
	{
		PC->InvertY = state;
	}
}
