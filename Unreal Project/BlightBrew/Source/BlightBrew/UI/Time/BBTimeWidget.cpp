// Copyright © Too Many Eyes , 2022


#include "BlightBrew/UI/Time/BBTimeWidget.h"

#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"

void UBBTimeWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
	CurrentSeconds += (GetWorld()->GetDeltaSeconds()) * 12;
	//UE_LOG(LogTemp, Warning, TEXT("%f"), CurrentSeconds);

	if (CurrentSeconds >= 60)
	{
		CurrentMinutes++;
		TotalMinutes++;
		CurrentSeconds = 0;
	}
	if (CurrentMinutes == 60)
	{
		CurrentHours++;
		CurrentMinutes = 0;
	}
	if (CurrentHours == 0)
	{
		TimeOfDayTextBlock->SetText(FText::FromString("Morning"));
	}
	if (CurrentHours == 2)
	{
		TimeOfDayTextBlock->SetText(FText::FromString("Morning"));
	}
	if (CurrentHours == 12)
	{
		TimeOfDayTextBlock->SetText(FText::FromString("Afternoon"));
	}
	if (CurrentHours == 17)
	{
		TimeOfDayTextBlock->SetText(FText::FromString("Evening"));
	}
	if (CurrentHours == 22)
	{
		TimeOfDayTextBlock->SetText(FText::FromString("Night"));
	}
	if (CurrentHours == 24)
	{
		CurrentHours = 0;
		TotalMinutes = 0;
	}

	FNumberFormattingOptions Opts;
	Opts.SetMaximumFractionalDigits(0);

	float hourScaled = CurrentHours;

	if (CurrentHours > 12)
	{
		hourScaled = CurrentHours - 12;
	}
	else if (CurrentHours == 0)
	{
		hourScaled = 1;
	}

	CurrentHourTextBlock->SetText(FText::AsNumber(hourScaled, &Opts));
	CurrentMinuteTextBlock->SetText(FText::AsNumber(CurrentMinutes, &Opts));

	TimeBar->SetPercent(TotalMinutes / (60 * 24));
}
