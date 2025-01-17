// Copyright © Too Many Eyes , 2022


#include "BlightBrew/UI/Dialogue/BBDialogueScreenWidget.h"

#include "BBDialogueWidget.h"
#include "BlightBrew/Characters/CharacterComponents/BBDialogueComponent.h"
#include "BlightBrew/Characters/Player/BBPlayerCharacter.h"
#include "BlightBrew/UI/BBHUD.h"
#include "Kismet/GameplayStatics.h"

void UBBDialogueScreenWidget::StartDialogue(UBBDialogueComponent* Instigator)
{
	CurrentDialogueComponent = Instigator;
	Dialogue->SetDialogueComponent(Instigator);
	
}

void UBBDialogueScreenWidget::EndDialogue()
{

}

void UBBDialogueScreenWidget::DialogueInput()
{
	Dialogue->DialogueInput();
}

void UBBDialogueScreenWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

}

void UBBDialogueScreenWidget::NativeConstruct()
{
	Super::NativeConstruct();

}
