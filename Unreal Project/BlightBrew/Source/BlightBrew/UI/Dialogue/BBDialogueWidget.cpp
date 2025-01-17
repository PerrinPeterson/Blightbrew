// Copyright © Too Many Eyes , 2022


#include "BlightBrew/UI/Dialogue/BBDialogueWidget.h"

#include "BBDialogueOptionWidget.h"
#include "BlightBrew/Characters/CharacterComponents/BBDialogueComponent.h"
#include "BlightBrew/Characters/Player/BBPlayerCharacter.h"
#include "BlightBrew/UI/BBHUD.h"

#include "Components/TextBlock.h"
#include "Components/Border.h"
#include "Components/ScrollBox.h"
#include "TimerManager.h"
#include "BlightBrew/Shop/BBShopper.h"
#include "Blueprint/WidgetTree.h"
#include "Kismet/GameplayStatics.h"

void UBBDialogueWidget::SetDialogueComponent(UBBDialogueComponent* dialogue)
{
	DialogueComponent = dialogue;
	
	SetTargetDialogue(DialogueComponent->GetDialogues()[0].Dialogue);
}

void UBBDialogueWidget::SetTargetDialogue(FString dialogue)
{
	TargetDialogue = dialogue;
	CurrentDialogue = "";
	bIsChoosingOption = false;
	bIsCurrentDialogueFinished = false;

	StartDialogue();
}

void UBBDialogueWidget::OnOptionClicked(UBBDialogueOptionWidget* widget)
{

	switch (widget->GetOption().OptionType)
	{
		case EDialogueOptionType::Barter:
		{
			//	Trigger Barter
			if (ABBShopper* shopper = Cast<ABBShopper>(DialogueComponent->GetOwner()))
			{
				//shopper->Barter();
			}
			break;

		}
		case EDialogueOptionType::Sell:
		{
			//	Trigger Sell
			if (ABBShopper* shopper = Cast<ABBShopper>(DialogueComponent->GetOwner()))
			{
				if (shopper->Sell())
				{
					EndDialogue();
				}
			}
			break;

		}
		case EDialogueOptionType::Next:
		{
			//	Trigger Next Dialogue
			NextDialogue();
			break;

		}
		case EDialogueOptionType::End:
		{
			//	End Conversation
			EndDialogue();
			break;
		}

		default:
		{
			break;
		}
	}

}

void UBBDialogueWidget::DialogueInput()
{
	SkipCurrentDialogue();
}

void UBBDialogueWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	//if (GetParent()->Visibility == ESlateVisibility::Visible)
	{
		if (bIsTimerFinished
			&& !bIsChoosingOption
			&& !bIsCurrentDialogueFinished)
		{
			NextDialogueCharacter();
		}

		//DialogueTextBlock->Text = FText::FromString(CurrentDialogue);
		//UE_LOG(LogTemp, Warning, TEXT("%s"), *CurrentDialogue);
		//UE_LOG(LogTemp, Warning, TEXT("%s"), *TargetDialogue);
		DialogueTextBlock->SetText(FText::FromString(CurrentDialogue));

		if (bIsCurrentDialogueFinished
			&& !bIsChoosingOption)
		{
			bIsChoosingOption = true;

			ShowDialogueOptions();
		}
	}
	//else
	{

	}



}

void UBBDialogueWidget::NativeConstruct()
{
	Super::NativeConstruct();

	//DialogueBufferTime = 0.25f;



	HideDialogueOptions();


	//Border->SetIsEnabled(false);
	//Border->SetVisibility(ESlateVisibility::Hidden);

}

void UBBDialogueWidget::SkipCurrentDialogue()
{
	GetWorld()->GetTimerManager().ClearAllTimersForObject(this);
	bIsTimerFinished = true;
	CurrentDialogue = TargetDialogue;
	bIsCurrentDialogueFinished = true;

	NextDialogue();
}

void UBBDialogueWidget::NextDialogueCharacter()
{
	bIsTimerFinished = false;

	if (!CurrentDialogue.Equals(TargetDialogue, ESearchCase::CaseSensitive))
	{
		CurrentDialogue += TargetDialogue[DialogueIndex];
		//DialogueTextBlock->SetText(FText::FromString(CurrentDialogue));
		DialogueIndex++;

		DialogueComponent->PlayDialogueOneShot();

		GetWorld()->GetTimerManager().SetTimer(DialogueTimerHandle, this, &UBBDialogueWidget::OnTimerFinished, DialogueBufferTime, false);
	}
	else
	{
		bIsCurrentDialogueFinished = true;
	}

}

void UBBDialogueWidget::StartDialogue()
{
	bIsTimerFinished = true;

	HideDialogueOptions();

	//GetWorld()->GetTimerManager().SetTimer(DialogueTimerHandle, this, &UBBDialogueWidget::OnTimerFinished, DialogueBufferTime, false, 5.0f);

	ActiveDialogueIndex = 0;

	SpeakerNameTextBlock->SetText(DialogueComponent->GetName());
}

void UBBDialogueWidget::NextDialogue()
{
	if (DialogueComponent->GetDialogues().Num() - 1 >= ActiveDialogueIndex)
	{
		DialogueIndex = 0;
		ActiveDialogueIndex++;
		TargetDialogue = DialogueComponent->GetDialogues()[ActiveDialogueIndex].Dialogue;

		HideDialogueOptions();
		bIsTimerFinished = true;
		CurrentDialogue = "";
		bIsCurrentDialogueFinished = false;
	}
}

void UBBDialogueWidget::EndDialogue()
{

	GetWorld()->GetTimerManager().ClearAllTimersForObject(this);
	bIsTimerFinished = true;
	CurrentDialogue = "";
	bIsCurrentDialogueFinished = true;
	DialogueIndex = 0;

	HideDialogueOptions();

	TArray<AActor*> FoundActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ABBPlayerCharacter::StaticClass(), FoundActors);

	if (ABBPlayerCharacter* player = Cast< ABBPlayerCharacter>(FoundActors[0]))
	{
		player->GetHUD()->EndDialogue();
	}


}

void UBBDialogueWidget::OnTimerFinished()
{
	bIsTimerFinished = true;
	NextDialogueCharacter();
}

void UBBDialogueWidget::ShowDialogueOptions()
{
	DialogueOptions->SetIsEnabled(true);
	DialogueOptions->SetVisibility(ESlateVisibility::Visible);

	for (int i = 0; i < DialogueComponent->GetDialogues()[ActiveDialogueIndex].DialogueOptions.Num(); i++)
	{
		UBBDialogueOptionWidget* NewWidget = WidgetTree->ConstructWidget<UBBDialogueOptionWidget>(OptionClass);

		NewWidget->SetText(FText::FromString(DialogueComponent->GetDialogues()[ActiveDialogueIndex].DialogueOptions[i].Dialogue));

		NewWidget->SetDialogueWidget(this);

		NewWidget->SetOption(DialogueComponent->GetDialogues()[ActiveDialogueIndex].DialogueOptions[i]);

		DialogueOptions->AddChild(NewWidget);
	}

	UBBDialogueOptionWidget* NewWidget = WidgetTree->ConstructWidget<UBBDialogueOptionWidget>(OptionClass);

	NewWidget->SetText(FText::FromString("Exit"));
	NewWidget->SetDialogueWidget(this);

	FDialogueOption option;
	option.OptionType = EDialogueOptionType::End;
	NewWidget->SetOption(option);

	DialogueOptions->AddChild(NewWidget);
}

void UBBDialogueWidget::HideDialogueOptions()
{
	DialogueOptions->SetIsEnabled(false);
	DialogueOptions->SetVisibility(ESlateVisibility::Hidden);

	DialogueOptions->ClearChildren();

	bIsChoosingOption = false;
}
