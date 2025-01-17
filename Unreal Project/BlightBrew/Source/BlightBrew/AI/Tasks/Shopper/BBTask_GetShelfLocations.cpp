// Copyright © Too Many Eyes , 2022


#include "BlightBrew/AI/Tasks/Shopper/BBTask_GetShelfLocations.h"

#include "AIController.h"
#include "NavigationSystem.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BlightBrew/Shop/BBShopper.h"
#include "BlightBrew/Shop/BBShopManager.h"
#include "BlightBrew/Inventory/Storage/BBStorageContainer.h"

UBBTask_GetShelfLocations::UBBTask_GetShelfLocations()
{
	NodeName = TEXT("Get Shelf Locations");

	//	Accept Only Vectors
	BlackboardKey.AddVectorFilter(this,
		GET_MEMBER_NAME_CHECKED(UBBTask_GetShelfLocations,
			BlackboardKey));	//ALLOW ONLY VECTOR TO BE FILLED INTO THIS TASK
}

EBTNodeResult::Type UBBTask_GetShelfLocations::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	FNavLocation Location{};

	//	GET AI PAWN
	AAIController* AIController = OwnerComp.GetAIOwner();
	APawn* AIPawn = AIController->GetPawn();

	//	GET PAWN ORIGIN
	const FVector Origin = AIPawn->GetActorLocation();

	ABBShopper* shopper = Cast<ABBShopper>(AIPawn);

	//	OBTAIN NAV SYSTEM & ALLOCATE RAND LOC
	const UNavigationSystemV1* NavSystem = UNavigationSystemV1::GetCurrent(GetWorld());

	//	IF NAV SYSTEM IS VALID
	if (IsValid(NavSystem))
	{
		//TODO: ADD SHELF LOCATION LOGIC

		if(shopper->ShopperID.Shop == nullptr )
		{
			FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);	//	CALLS TASK FINISHED

			return EBTNodeResult::Succeeded;
		}

		//	Declare a local array to store the pointers to the shop's shelves
		TArray<ABBStorageContainer*> Shelves = shopper->ShopperID.Shop->GetStorageContainerArray();

		//	Declare an empty local array to store pointers to shelves the AI SHOULD visit
		TArray<ABBStorageContainer*> ShelvesToVisit;

		//	Loop through the available shelves in the shop
		for (auto shelf : Shelves)
		{
			//	Declare a local bool to track if THIS shelf has been visited (iteration)
			bool bHasVisited = false;

			//	Loop through the array of visited shelves
			for (auto visitedShelf : shopper->ShopperID.VisitedShelves)
			{
				//	If they are the same shelf
				if (visitedShelf == shelf)
				{
					//	 Mark this shelf as visited, and break out of the loop
					bHasVisited = true;
					break;
				}
			}

			//	If this shelf hasn't been visited
			if(bHasVisited == false)
			{
				//	Add to the shelves to visit
				ShelvesToVisit.Add(shelf);
			}

		}

		//	Declare a local float of distance, to use as the max distance
		float OutDistance = 999999999.0f;

		//	Declare a local ABBStorageContainer to store a pointer to the shelf that is closest to the AI
		ABBStorageContainer* closestShelf = nullptr;

		//	Loop through all of the shelves that haven't been visited
		for (auto shelf : ShelvesToVisit)
		{
			//	Get the distance from the shelf to the AI pawn
			float TempDistance = (shelf->GetActorLocation() - Origin).Length();

			//	If the distance is shorter than the previous distance
			if (TempDistance < OutDistance)
			{
				//	Make the stored distance for closest distance the new closest distance
				OutDistance = TempDistance;
				//	Store the points to the closest shelf
				closestShelf = shelf;
			}
		}

		//	If there is a closest shelf
		if(closestShelf != nullptr)
		{
			//	Add the shelf to the visited shelves
			shopper->AddVisitedShelf(closestShelf);

			//	Find the closest navigable point to the shelf
			if(NavSystem->GetRandomPointInNavigableRadius(closestShelf->GetActorLocation(), AcceptableRadius, Location))
			{
				/*DrawDebugLine(GetWorld(),
					closestShelf->GetActorLocation(),
					shopper->GetActorLocation(),
					FColor::Magenta,
					false,
					1.0f,
					0,
					1.0f);
				DrawDebugSphere(GetWorld(),
					closestShelf->GetActorLocation(),
					AcceptableRadius,
					36,
					FColor::Magenta);*/
				//NavSystem->ProjectPointToNavigation(closestShelf->GetActorLocation(), Location);

				//	Set the blackboard's FVector (TargetLocation) to this point
				AIController->GetBlackboardComponent()->SetValueAsVector(BlackboardKey.SelectedKeyName, Location.Location);
			}


			//AIController->GetBlackboardComponent()->SetValueAsVector(BlackboardKey.SelectedKeyName, closestShelf->GetActorLocation());


			FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);	//	CALLS TASK FINISHED

			return EBTNodeResult::Succeeded;
		}

		
	}

	//	SIGNAL BTComp THAT TASK FINISHED :: FAILED

	FinishLatentTask(OwnerComp, EBTNodeResult::Failed);	//	CALLS TASK FINISHED

	//	This will break out of the current sequence, because there is no more shelves to visit
	return EBTNodeResult::Failed;
}

FString UBBTask_GetShelfLocations::GetStaticDescription() const
{
	return FString::Printf(TEXT("Vector: %s"), *BlackboardKey.SelectedKeyName.ToString());
}
