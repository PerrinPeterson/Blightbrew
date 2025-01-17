// Copyright © Too Many Eyes , 2022


#include "BlightBrew/AI/Tasks/BBFaunaAITask_FindRandomLocation.h"

#include "AIController.h"
#include "NavigationSystem.h"
//#include "AI/NavigationSystemBase.h"
#include "BehaviorTree/BlackboardComponent.h"

UBBFaunaAITask_FindRandomLocation::UBBFaunaAITask_FindRandomLocation()
{
	NodeName = TEXT("Find Random Location");

	//	Accept Only Vectors
	BlackboardKey.AddVectorFilter(this,
		GET_MEMBER_NAME_CHECKED(UBBFaunaAITask_FindRandomLocation,
		BlackboardKey));	//ALLOW ONLY VECTOR TO BE FILLED INTO THIS TASK
}

EBTNodeResult::Type UBBFaunaAITask_FindRandomLocation::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	FNavLocation Location{};

	//	GET AI PAWN
	AAIController* AIController = OwnerComp.GetAIOwner();
	const APawn* AIPawn = AIController->GetPawn();

	//	GET PAWN ORIGIN
	const FVector Origin = AIPawn->GetActorLocation();

	//	OBTAIN NAV SYSTEM & ALLOCATE RAND LOC
	const UNavigationSystemV1* NavSystem = UNavigationSystemV1::GetCurrent(GetWorld());

	//	IF NAV SYSTEM IS VALID
	if(IsValid(NavSystem)		//	& Returns a random point within our nav, within search radius
		&& NavSystem->GetRandomPointInNavigableRadius(Origin, SearchRadius, Location))
	{
		AIController->GetBlackboardComponent()->SetValueAsVector(BlackboardKey.SelectedKeyName, Location.Location);
	}

	//	SIGNAL BTComp THAT TASK FINISHED :: SUCCESS

	FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);	//	CALLS TASK FINISHED

	return EBTNodeResult::Succeeded;
}

FString UBBFaunaAITask_FindRandomLocation::GetStaticDescription() const
{
	//	Setups the Blueprint Node

	return FString::Printf(TEXT("Vector: %s"), *BlackboardKey.SelectedKeyName.ToString());
}
