// Copyright © Too Many Eyes , 2022


#include "BlightBrew/AI/Tasks/Shopper/BBTask_Barter.h"

#include "BlightBrew/Shop/BBShopper.h"
#include "BlightBrew/Shop/BBShopManager.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"
#include "BlightBrew/Inventory/BBInventoryComponent.h"
#include "BlightBrew/Inventory/BBInventorySlotNew.h"
#include "BlightBrew/Items/BBBaseItem.h"

UBBTask_Barter::UBBTask_Barter()
{
	NodeName = TEXT("Barter");
}

EBTNodeResult::Type UBBTask_Barter::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AAIController* AIController = OwnerComp.GetAIOwner();
	APawn* AIPawn = AIController->GetPawn();


	ABBShopper* shopper = Cast<ABBShopper>(AIPawn);

	for (int i =0; i < shopper->InventoryComponent->GetInventorySlots().Num(); i++)
	{
		if (shopper->InventoryComponent->GetInventorySlots()[i]->GetItemClass())
		{
			break;
		}

		if (i == shopper->InventoryComponent->GetInventorySlots().Num() - 1)
		{
			FinishLatentTask(OwnerComp, EBTNodeResult::Failed);	//	CALLS TASK FINISHED
			return EBTNodeResult::Failed;
		}
	}


	if (shopper->m_isWaiting)
	{
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);	//	CALLS TASK FINISHED

		return EBTNodeResult::Succeeded;
	}

	FinishLatentTask(OwnerComp, EBTNodeResult::Failed);	//	CALLS TASK FINISHED

	return EBTNodeResult::Failed;

}

FString UBBTask_Barter::GetStaticDescription() const
{
	return FString::Printf(TEXT("Barter with the player."));
}
