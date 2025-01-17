// Copyright © Too Many Eyes , 2022


#include "BlightBrew/UI/MainMenu/BBCreditsMenuWidget.h"

#include "BBMainMenuParentWidget.h"
#include "Components/Button.h"
#include "Components/WidgetSwitcher.h"

void UBBCreditsMenuWidget::OnBack()
{
	if (UBBMainMenuParentWidget* Parent = Cast<UBBMainMenuParentWidget>(GetParent()->GetOuter()->GetOuter()))
	{
		//UE_LOG(LogTemp, Warning, TEXT("Success"));
		Parent->SetCurrentWidget(EMainMenuWidgetType::Menu);
	}
}

void UBBCreditsMenuWidget::NativeConstruct()
{
	Super::NativeConstruct();

	BackButton->OnPressed.AddDynamic(this, &UBBCreditsMenuWidget::OnBack);

}
