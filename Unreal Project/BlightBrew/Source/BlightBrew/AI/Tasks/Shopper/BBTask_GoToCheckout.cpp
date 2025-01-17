// Copyright © Too Many Eyes , 2022


#include "BlightBrew/AI/Tasks/Shopper/BBTask_GoToCheckout.h"

#include "AIController.h"
#include "NavigationSystem.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BlightBrew/Shop/BBShopper.h"
#include "BlightBrew/Shop/BBShopManager.h"
#include "Components/BoxComponent.h"


UBBTask_GoToCheckout::UBBTask_GoToCheckout()
{
	NodeName = TEXT("Go To Checkout");

	//	Accept Only Vectors
	BlackboardKey.AddVectorFilter(this,
		GET_MEMBER_NAME_CHECKED(UBBTask_GoToCheckout,
			BlackboardKey));	//ALLOW ONLY VECTOR TO BE FILLED INTO THIS TASK
}

EBTNodeResult::Type UBBTask_GoToCheckout::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	FNavLocation Location{};

	//	GET AI PAWN
	AAIController* AIController = OwnerComp.GetAIOwner();
	APawn* AIPawn = AIController->GetPawn();

	//	GET PAWN ORIGIN
	const FVector Origin = AIPawn->GetActorLocation();

	ABBShopper* shopper = Cast<ABBShopper>(AIPawn);

	FVector waitingArea = shopper->ShopperID.Shop->GetWaitingArea()->GetComponentLocation();

	//	OBTAIN NAV SYSTEM & ALLOCATE RAND LOC
	const UNavigationSystemV1* NavSystem = UNavigationSystemV1::GetCurrent(GetWorld());

	if((shopper->GetActorLocation() - waitingArea).Length() <= AcceptableRadius)
	{

		shopper->m_isWaiting = true;

		FinishLatentTask(OwnerComp, EBTNodeResult::Failed);	//	CALLS TASK FINISHED

		return EBTNodeResult::Failed;
	}

	//	IF NAV SYSTEM IS VALID
	if (IsValid(NavSystem)
		&& NavSystem->GetRandomPointInNavigableRadius(waitingArea, AcceptableRadius, Location))
	{
		/*DrawDebugSphere(GetWorld(),
			Location.Location,
			AcceptableRadius,
			36,
			FColor::Magenta,
			false,
			5.0f);*/

		AIController->GetBlackboardComponent()->SetValueAsVector(BlackboardKey.SelectedKeyName, Location.Location);

		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);	//	CALLS TASK FINISHED

		return EBTNodeResult::Succeeded;
	}

	FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);	//	CALLS TASK FINISHED

	return EBTNodeResult::Succeeded;


}

FString UBBTask_GoToCheckout::GetStaticDescription() const
{
	return FString::Printf(TEXT("Vector: %s"), *BlackboardKey.SelectedKeyName.ToString());
}
