// Copyright © Too Many Eyes , 2022


#include "BlightBrew/UI/Settings/Video/BBVideoSettingsWidget.h"

#include <string>

#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "GameFramework/GameUserSettings.h"
#include "Components/Slider.h"
#include "Engine/PostProcessVolume.h"
#include "Kismet/GameplayStatics.h"

void UBBVideoSettingsWidget::OnWindowLeft()
{
	WindowModeCounter--;

	WindowModeCounter = FMath::Clamp(WindowModeCounter, 0, 2);
	//UpdateWindowMode();
}

void UBBVideoSettingsWidget::OnWindowRight()
{
	WindowModeCounter++;
	WindowModeCounter = FMath::Clamp(WindowModeCounter, 0, 2);
	//UpdateWindowMode();
}

void UBBVideoSettingsWidget::UpdateWindowMode()
{
	switch(WindowModeCounter)
	{
		case EWindowMode::Fullscreen:
		{
			WindowModeTextBox->SetText(FText::FromString("Fullscreen"));
			break;
		}
		case EWindowMode::WindowedFullscreen :
		{
			WindowModeTextBox->SetText(FText::FromString("WindowedFullscreen"));
			break;
		}
		case EWindowMode::Windowed:
		{
			WindowModeTextBox->SetText(FText::FromString("Windowed"));
			break;
		}
	default:
			{
				
			}
	}
}

void UBBVideoSettingsWidget::OnResolutionLeft()
{
	ResolutionCounter--;
	ResolutionCounter = FMath::Clamp(ResolutionCounter, 0, 4);
	//UpdateResolution();
}

void UBBVideoSettingsWidget::OnResolutionRight()
{
	ResolutionCounter++;
	ResolutionCounter = FMath::Clamp(ResolutionCounter, 0, 4);
	//UpdateResolution();
}

void UBBVideoSettingsWidget::UpdateResolution()
{
	switch (ResolutionCounter)
	{
		case 0:
		{
			ResolutionTextBox->SetText(FText::FromString("1280x720"));
			break;
		}
		case 1:
		{
			ResolutionTextBox->SetText(FText::FromString("1600x900"));
			break;
		}
		case 2:
		{
			ResolutionTextBox->SetText(FText::FromString("1920x1080"));
			break;
		}
		case 3:
		{
			ResolutionTextBox->SetText(FText::FromString("2560x1440"));
			break;
		}
		case 4:
		{
			ResolutionTextBox->SetText(FText::FromString("3840x2160"));
			break;
		}
	default:
			{
				
			}
	}
}

void UBBVideoSettingsWidget::OnShadowLeft()
{
	ShadowCounter--;
	ShadowCounter = FMath::Clamp(ShadowCounter, 0, 4);
	//UpdateShadow();
}

void UBBVideoSettingsWidget::OnShadowRight()
{
	ShadowCounter++;
	ShadowCounter = FMath::Clamp(ShadowCounter, 0, 4);
	//UpdateShadow();
}

void UBBVideoSettingsWidget::UpdateShadow()
{
	switch (ShadowCounter)
	{
		case 0:
		{
			ShadowQTextBox->SetText(FText::FromString("Low"));
			break;
		}
		case 1:
		{
			ShadowQTextBox->SetText(FText::FromString("Medium"));
			break;
		}
		case 2:
		{
			ShadowQTextBox->SetText(FText::FromString("High"));
			break;
		}
		case 3:
		{
			ShadowQTextBox->SetText(FText::FromString("Epic"));
			break;
		}
		case 4:
		{
			ShadowQTextBox->SetText(FText::FromString("Cinematic"));
			break;
		}
	default:
			{
				
			}
	}
}

void UBBVideoSettingsWidget::OnTextureLeft()
{
	TextureCounter--;
	TextureCounter = FMath::Clamp(TextureCounter, 0, 4);
	//UpdateTexture();
}

void UBBVideoSettingsWidget::OnTextureRight()
{
	TextureCounter++;
	TextureCounter = FMath::Clamp(TextureCounter, 0, 4);
	//UpdateTexture();
}

void UBBVideoSettingsWidget::UpdateTexture()
{
	switch (TextureCounter)
	{
	case 0:
	{
		TextureQTextBox->SetText(FText::FromString("Low"));
		break;
	}
	case 1:
	{
		TextureQTextBox->SetText(FText::FromString("Medium"));
		break;
	}
	case 2:
	{
		TextureQTextBox->SetText(FText::FromString("High"));
		break;
	}
	case 3:
	{
		TextureQTextBox->SetText(FText::FromString("Epic"));
		break;
	}
	case 4:
	{
		TextureQTextBox->SetText(FText::FromString("Cinematic"));
		break;
	}
	default:
		{
			
		}
	}
}

void UBBVideoSettingsWidget::OnFoliageLeft()
{
	FoliageCounter--;
	FoliageCounter = FMath::Clamp(FoliageCounter, 0, 4);
	//UpdateFoliage();
}

void UBBVideoSettingsWidget::OnFoliageRight()
{
	FoliageCounter++;
	FoliageCounter = FMath::Clamp(FoliageCounter, 0, 4);
	//UpdateFoliage();
}

void UBBVideoSettingsWidget::UpdateFoliage()
{
	switch (FoliageCounter)
	{
		case 0:
		{
			FoliageQTextBox->SetText(FText::FromString("Low"));
			break;
		}
		case 1:
		{
			FoliageQTextBox->SetText(FText::FromString("Medium"));
			break;
		}
		case 2:
		{
			FoliageQTextBox->SetText(FText::FromString("High"));
			break;
		}
		case 3:
		{
			FoliageQTextBox->SetText(FText::FromString("Epic"));
			break;
		}
		case 4:
		{
			FoliageQTextBox->SetText(FText::FromString("Cinematic"));
			break;
		}
		default:
			{
				
			}
	}
}

void UBBVideoSettingsWidget::OnVSyncPressed()
{
	bIsVSyncEnabled = !bIsVSyncEnabled;

	if(bIsVSyncEnabled)
	{
		VSyncToggleText->SetText(FText::FromString("Enabled"));
	}
	else
	{
		VSyncToggleText->SetText(FText::FromString("Disabled"));
	}
}

void UBBVideoSettingsWidget::OnBrightnessChanged(float Value)
{
	//UserSettings->Br
	BrightnessValue = Value;
	FString com1 = "Gamma ";
	FString com2 = FString::SanitizeFloat(Value);
	FString Command = com1 + com2;
	GetOwningPlayer()->ConsoleCommand(*Command);
	//GetWorld()->Exec(GetWorld(), *Command);
}

void UBBVideoSettingsWidget::Apply()
{
#pragma region WindowMode

	switch(WindowModeCounter)
	{
		case EWindowMode::Fullscreen:
		{
			UserSettings->SetFullscreenMode(EWindowMode::Fullscreen);
			break;
		}
		case EWindowMode::WindowedFullscreen:
		{
			UserSettings->SetFullscreenMode(EWindowMode::WindowedFullscreen);
			break;
		}
		case EWindowMode::Windowed:
		{
			UserSettings->SetFullscreenMode(EWindowMode::Windowed);
			break;
		}
	default:
			{
				
			}
	}

#pragma endregion WindowMode

#pragma region Resolution

	switch (ResolutionCounter)
	{
		case 0:
		{
			UserSettings->SetScreenResolution(FIntPoint(1280, 720));
			break;
		}
		case 1:
		{
			UserSettings->SetScreenResolution(FIntPoint(1600, 900));
			break;
		}
		case 2:
		{
			UserSettings->SetScreenResolution(FIntPoint(1920, 1080));
			break;
		}
		case 3:
		{
			UserSettings->SetScreenResolution(FIntPoint(2560, 1440));
			break;
		}
		case 4:
		{
			UserSettings->SetScreenResolution(FIntPoint(3840, 2160));
			break;
		}
	default:
			{
				
			}
	}

#pragma endregion Resolution

#pragma region Shadow

	UserSettings->SetShadowQuality(ShadowCounter);

#pragma endregion Shadow

#pragma region Texture

	UserSettings->SetTextureQuality(TextureCounter);

#pragma endregion Texture

#pragma region Foliage

	UserSettings->SetFoliageQuality(FoliageCounter);

#pragma endregion Foliage


	UserSettings->SetVSyncEnabled(bIsVSyncEnabled);


#pragma region Brightness

	TArray<AActor*> FoundActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(),
		APostProcessVolume::StaticClass(), FoundActors);

	for(AActor* actor : FoundActors)
	{
		if(APostProcessVolume* PostProcessVolume = Cast<APostProcessVolume>(actor))
		{
			PostProcessVolume->Settings.AutoExposureMinBrightness = BrightnessValue + 0.1f;
			PostProcessVolume->Settings.AutoExposureMaxBrightness = BrightnessValue - 0.1f;
			//UE_LOG(LogTemp, Warning, TEXT("PostProcessVolume Brightness Adjusted %f"), BrightnessValue);
		}

		
	}


#pragma endregion Brightness

	UserSettings->ApplySettings(false);

}

void UBBVideoSettingsWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	UpdateFoliage();
	UpdateResolution();
	UpdateShadow();
	UpdateTexture();
	UpdateWindowMode();

	UserSettings = GetGameInstance()->GetEngine()->GetGameUserSettings();

}

void UBBVideoSettingsWidget::NativeConstruct()
{
	Super::NativeConstruct();

	UserSettings = GetGameInstance()->GetEngine()->GetGameUserSettings();
	//UserSettings->RunHardwareBenchmark();
	//UserSettings->ApplyHardwareBenchmarkResults();

	BrightnessValue = 1.0f;
	BrightnessSlider->SetValue(BrightnessValue);
	//UserSettings = GEngine->GetGameUserSettings();


#pragma region WindowMode

	WindowModeCounter = UserSettings->GetFullscreenMode();

	WindowModeButtonL->OnPressed.AddDynamic(this, &UBBVideoSettingsWidget::OnWindowLeft);
	WindowModeButtonR->OnPressed.AddDynamic(this, &UBBVideoSettingsWidget::OnWindowRight);

#pragma endregion WindowMode

#pragma region Resolution

	ResolutionCounter = 0;
	FIntPoint resolution= UserSettings->GetScreenResolution();

	switch(resolution.X)
	{
		case 1280:
		{
			ResolutionCounter = 0;
			break;
		}
		case 1600:
		{
			ResolutionCounter = 1;
			break;
		}
		case 1920:
		{
			ResolutionCounter = 2;
			break;
		}
		case 2560:
		{
			ResolutionCounter = 3;
			break;
		}
		case 3840:
		{
			ResolutionCounter = 4;
			break;
		}
	}

	ResolutionButtonL->OnPressed.AddDynamic(this, &UBBVideoSettingsWidget::OnResolutionLeft);
	ResolutionButtonR->OnPressed.AddDynamic(this, &UBBVideoSettingsWidget::OnResolutionRight);

#pragma endregion Resolution

#pragma region ShadowQuality

	ShadowCounter = UserSettings->GetShadowQuality();
	ShadowQButtonL->OnPressed.AddDynamic(this, &UBBVideoSettingsWidget::OnShadowLeft);
	ShadowQButtonR->OnPressed.AddDynamic(this, &UBBVideoSettingsWidget::OnShadowRight);

#pragma endregion ShadowQuality

#pragma region TextureQuality

	TextureCounter = UserSettings->GetTextureQuality();
	TextureQButtonL->OnPressed.AddDynamic(this, &UBBVideoSettingsWidget::OnTextureLeft);
	TextureQButtonR->OnPressed.AddDynamic(this, &UBBVideoSettingsWidget::OnTextureRight);

#pragma endregion TextureQuality

#pragma region FoliageQuality

	FoliageCounter = UserSettings->GetFoliageQuality();
	FoliageQButtonL->OnPressed.AddDynamic(this, &UBBVideoSettingsWidget::OnFoliageLeft);
	FoliageQButtonR->OnPressed.AddDynamic(this, &UBBVideoSettingsWidget::OnFoliageRight);

#pragma endregion FoliageQuality

#pragma region VSync

	bIsVSyncEnabled = UserSettings->IsVSyncEnabled();
	VSyncCheckBox->OnPressed.AddDynamic(this, &UBBVideoSettingsWidget::OnVSyncPressed);

#pragma endregion VSync

	BrightnessSlider->OnValueChanged.AddDynamic(this, &UBBVideoSettingsWidget::OnBrightnessChanged);

	ApplyButton->OnPressed.AddDynamic(this, &UBBVideoSettingsWidget::Apply);
}
