// Copyright © Too Many Eyes , 2022


#include "BlightBrew/UI/Dialogue/BBDialogueOptionWidget.h"

#include "BBDialogueWidget.h"
#include "BlightBrew/Characters/CharacterComponents/BBDialogueComponent.h"

#include "Components/TextBlock.h"
#include "Components/Button.h"

void UBBDialogueOptionWidget::SetDialogueWidget(UBBDialogueWidget* widget)
{
	DialogueWidget = widget;
}

void UBBDialogueOptionWidget::SetIndex(int32 index)
{
	Index = index;
}

void UBBDialogueOptionWidget::SetText(FText text)
{
	DialogueTextBlock->Text = text;
}

void UBBDialogueOptionWidget::SetOption(FDialogueOption option)
{
	Option = option;
}

FDialogueOption UBBDialogueOptionWidget::GetOption()
{
	return Option;
}

void UBBDialogueOptionWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	//Super::NativeTick(MyGeometry, InDeltaTime);
}

void UBBDialogueOptionWidget::NativeConstruct()
{
	Super::NativeConstruct();

	Button->OnPressed.AddDynamic(this, &UBBDialogueOptionWidget::OnClick);
}

void UBBDialogueOptionWidget::OnClick()
{
	if(DialogueWidget)
	{
		//Option.OnClicked();
		DialogueWidget->OnOptionClicked(this);
	}
}
