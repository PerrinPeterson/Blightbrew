// Copyright © Too Many Eyes , 2022


#include "BlightBrew/AI/Tasks/Shopper/BBTask_GoToShelf.h"


#include "AIController.h"
#include "NavigationSystem.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BlightBrew/Shop/BBShopper.h"
#include "Kismet/GameplayStatics.h"

UBBTask_GoToShelf::UBBTask_GoToShelf()
{
	NodeName = TEXT("Go To Shelf");

	//	Accept Only Vectors
	BlackboardKey.AddVectorFilter(this,
		GET_MEMBER_NAME_CHECKED(UBBTask_GoToShelf,
			BlackboardKey));	//ALLOW ONLY VECTOR TO BE FILLED INTO THIS TASK
}

EBTNodeResult::Type UBBTask_GoToShelf::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	//return Super::ExecuteTask(OwnerComp, NodeMemory);

	FNavLocation Location{};

	//	GET AI PAWN
	AAIController* AIController = OwnerComp.GetAIOwner();
	APawn* AIPawn = AIController->GetPawn();
	ABBShopper* shopper = Cast<ABBShopper>(AIPawn);

	//	GET PAWN ORIGIN
	const FVector Origin = AIPawn->GetActorLocation();

	//	OBTAIN NAV SYSTEM & ALLOCATE RAND LOC
	const UNavigationSystemV1* NavSystem = UNavigationSystemV1::GetCurrent(GetWorld());

	if(IsValid(NavSystem))
	{

		AIController->GetBlackboardComponent()->SetValueAsVector(BlackboardKey.SelectedKeyName, Location.Location);
	}

	FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);	//	CALLS TASK FINISHED

	return EBTNodeResult::Succeeded;
}

FString UBBTask_GoToShelf::GetStaticDescription() const
{
	return FString::Printf(TEXT("Vector: %s"), *BlackboardKey.SelectedKeyName.ToString());
}
