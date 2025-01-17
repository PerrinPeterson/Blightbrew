// Copyright © Too Many Eyes , 2022 - 2023

#pragma once

#include "CoreMinimal.h"
#include "BlightBrew/UI/Dialogue/BBDialogueOptionWidget.h"
#include "Engine/TriggerBox.h"
#include "BBDialogueTrigger.generated.h"

/**
 * 
 */
UCLASS()
class BLIGHTBREW_API ABBDialogueTrigger : public ATriggerBox
{
	GENERATED_BODY()

public:
	ABBDialogueTrigger();


protected:
	virtual void BeginPlay() override;

	UFUNCTION()
		void TriggerOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
			UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
		UBBDialogueComponent* DialogueComponent;




private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Trigger, meta = (AllowPrivateAccess = "true"))
		bool bIsTriggered;

};
