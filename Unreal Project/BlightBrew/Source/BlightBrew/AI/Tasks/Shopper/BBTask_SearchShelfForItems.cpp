// Copyright © Too Many Eyes , 2022


#include "BlightBrew/AI/Tasks/Shopper/BBTask_SearchShelfForItems.h"

#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"

#include "BlightBrew/Shop/BBShopper.h"
#include "BlightBrew/Shop/BBShopManager.h"
#include "BlightBrew/Inventory/Storage/BBStorageContainer.h"

UBBTask_SearchShelfForItems::UBBTask_SearchShelfForItems()
{
	NodeName = TEXT("Search Shelf For Items");
}

EBTNodeResult::Type UBBTask_SearchShelfForItems::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	//	GET AI PAWN
	AAIController* AIController = OwnerComp.GetAIOwner();
	APawn* AIPawn = AIController->GetPawn();

	ABBShopper* shopper = Cast<ABBShopper>(AIPawn);

	if(shopper->Interact())
	{
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);	//	CALLS TASK FINISHED

		return EBTNodeResult::Succeeded;
	}

	FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);	//	CALLS TASK FINISHED

	return EBTNodeResult::Succeeded;
}

FString UBBTask_SearchShelfForItems::GetStaticDescription() const
{
	return FString::Printf(TEXT("Search the current shelf for shopping list items."));
}
