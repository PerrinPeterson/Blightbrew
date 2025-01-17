// Copyright © Too Many Eyes , 2022


#include "BlightBrew/AI/Tasks/BBAITask_FindNextPathPoint.h"

#include "AIController.h"
#include "NavigationSystem.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BlightBrew/AI/Splines/BBSplinePath.h"
#include "BlightBrew/Characters/AI/Wanderer/BBWandererAICharacter.h"
#include "Components/SplineComponent.h"
#include "Kismet/GameplayStatics.h"

UBBAITask_FindNextPathPoint::UBBAITask_FindNextPathPoint()
{
	NodeName = TEXT("Find Next Path Point");

	//	Accept Only Vectors
	BlackboardKey.AddVectorFilter(this,
		GET_MEMBER_NAME_CHECKED(UBBAITask_FindNextPathPoint,
			BlackboardKey));	//ALLOW ONLY VECTOR TO BE FILLED INTO THIS TASK
}

EBTNodeResult::Type UBBAITask_FindNextPathPoint::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	FNavLocation Location{};

	//	GET AI PAWN
	AAIController* AIController = OwnerComp.GetAIOwner();
	APawn* AIPawn = AIController->GetPawn();
	ABBWandererAICharacter* wanderer = Cast<ABBWandererAICharacter>(AIPawn);

	//	GET PAWN ORIGIN
	const FVector Origin = AIPawn->GetActorLocation();

	//	OBTAIN NAV SYSTEM & ALLOCATE RAND LOC
	const UNavigationSystemV1* NavSystem = UNavigationSystemV1::GetCurrent(GetWorld());

	TArray<AActor*> Splines;
	UGameplayStatics::GetAllActorsOfClass(this, ABBSplinePath::StaticClass(), Splines);

	for(auto obj : Splines)
	{
		ABBSplinePath* Spline = Cast<ABBSplinePath>(obj);
		if(Spline !=nullptr
			&& wanderer != nullptr)
		{
			if(Spline->GetPathID().ToString() == wanderer->GetPathToFollow().ToString())
			{
				float OutDistance = 999999999.0f;

				for (int32 i = 0; i < Spline->GetSpline()->GetNumberOfSplinePoints(); i++)
				{
					float TempDistance = (Spline->GetSpline()->GetLocationAtSplinePoint(i, ESplineCoordinateSpace::World) - Origin).Length();

					if (TempDistance < OutDistance)
					{
						OutDistance = TempDistance;
						NextPoint = i;
					}
				}

				if (CurrentPoint != NextPoint)
				{
					CurrentPoint = NextPoint;
				}
				else
				{
					CurrentPoint++;
				}

				float Distance = Spline->GetSpline()->GetDistanceAlongSplineAtSplinePoint(CurrentPoint);

				FVector newLocation = Spline->GetSpline()->GetWorldLocationAtDistanceAlongSpline(Distance);

				//	IF NAV SYSTEM IS VALID
				if (IsValid(NavSystem)		//	& Returns a random point within our nav, within search radius
					&& NavSystem->GetRandomPointInNavigableRadius(newLocation, AcceptableRadius, Location))
				{
					AIController->GetBlackboardComponent()->SetValueAsVector(BlackboardKey.SelectedKeyName, Location.Location);
				}

				break;
			}
		}
	}

	//	SIGNAL BTComp THAT TASK FINISHED :: SUCCESS

	FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);	//	CALLS TASK FINISHED

	return EBTNodeResult::Succeeded;
}

FString UBBAITask_FindNextPathPoint::GetStaticDescription() const
{
	return FString::Printf(TEXT("Vector: %s"), *BlackboardKey.SelectedKeyName.ToString());
}
