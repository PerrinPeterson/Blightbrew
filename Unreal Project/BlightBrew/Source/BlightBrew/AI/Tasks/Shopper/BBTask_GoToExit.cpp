// Copyright © Too Many Eyes , 2022


#include "BlightBrew/AI/Tasks/Shopper/BBTask_GoToExit.h"

#include "AIController.h"
#include "NavigationSystem.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BlightBrew/Shop/BBShopper.h"
#include "BlightBrew/Shop/BBShopManager.h"
#include "Components/BoxComponent.h"

UBBTask_GoToExit::UBBTask_GoToExit()
{
	NodeName = TEXT("Go To Exit");

	//	Accept Only Vectors
	BlackboardKey.AddVectorFilter(this,
		GET_MEMBER_NAME_CHECKED(UBBTask_GoToExit,
			BlackboardKey));	//ALLOW ONLY VECTOR TO BE FILLED INTO THIS TASK
}

EBTNodeResult::Type UBBTask_GoToExit::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	FNavLocation Location{};

	//	GET AI PAWN
	AAIController* AIController = OwnerComp.GetAIOwner();
	APawn* AIPawn = AIController->GetPawn();

	//	GET PAWN ORIGIN
	const FVector Origin = AIPawn->GetActorLocation();

	ABBShopper* shopper = Cast<ABBShopper>(AIPawn);

	FVector despawnArea = shopper->ShopperID.Shop->GetDespawnArea()->GetComponentLocation();

	//	OBTAIN NAV SYSTEM & ALLOCATE RAND LOC
	const UNavigationSystemV1* NavSystem = UNavigationSystemV1::GetCurrent(GetWorld());

	//	IF NAV SYSTEM IS VALID
	if (IsValid(NavSystem)
		&& NavSystem->GetRandomPointInNavigableRadius(despawnArea, AcceptableRadius, Location))
	{

		AIController->GetBlackboardComponent()->SetValueAsVector(BlackboardKey.SelectedKeyName, Location.Location);
	}

	FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);	//	CALLS TASK FINISHED

	return EBTNodeResult::Succeeded;
}

FString UBBTask_GoToExit::GetStaticDescription() const
{
	return FString::Printf(TEXT("Vector: %s"), *BlackboardKey.SelectedKeyName.ToString());
}
