// Copyright © Too Many Eyes , 2022 - 2023


#include "BBBlackScreenWidget.h"
#include "Components/Border.h"


void UBBBlackScreenWidget::NativeConstruct()
{
	BlackBorder->SetBrushColor(FLinearColor(FColor::Black));
}
