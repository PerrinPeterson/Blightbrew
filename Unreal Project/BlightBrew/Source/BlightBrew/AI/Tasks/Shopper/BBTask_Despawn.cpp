// Copyright © Too Many Eyes , 2022


#include "BlightBrew/AI/Tasks/Shopper/BBTask_Despawn.h"

#include "BlightBrew/Shop/BBShopper.h"
#include "BlightBrew/Shop/BBShopManager.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"

UBBTask_Despawn::UBBTask_Despawn()
{
	NodeName = TEXT("Despawn");
}

EBTNodeResult::Type UBBTask_Despawn::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AAIController* AIController = OwnerComp.GetAIOwner();
	APawn* AIPawn = AIController->GetPawn();


	ABBShopper* shopper = Cast<ABBShopper>(AIPawn);

	shopper->ShopperID.Shop->DespawnShopper(shopper);

	FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);	//	CALLS TASK FINISHED

	return EBTNodeResult::Succeeded;
}

FString UBBTask_Despawn::GetStaticDescription() const
{
	return FString::Printf(TEXT("Despawn the AI"));
}
