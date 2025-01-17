// Copyright © Too Many Eyes , 2022


#include "BlightBrew/AI/Tasks/Shopper/BBTask_LookAtObject.h"

#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"

UBBTask_LookAtObject::UBBTask_LookAtObject()
{
	NodeName = TEXT("Rotate towards location");

	//	Accept Only Vectors
	BlackboardKey.AddVectorFilter(this,
		GET_MEMBER_NAME_CHECKED(UBBTask_LookAtObject,
			BlackboardKey));	//ALLOW ONLY VECTOR TO BE FILLED INTO THIS TASK
}

EBTNodeResult::Type UBBTask_LookAtObject::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	//	GET AI PAWN
	AAIController* AIController = OwnerComp.GetAIOwner();
	APawn* AIPawn = AIController->GetPawn();

	FVector shelfLocation =	AIController->GetBlackboardComponent()->GetValueAsVector(BlackboardKey.SelectedKeyName);
	FVector Direction = shelfLocation - AIPawn->GetActorLocation();
	Direction.Normalize();
	FRotator LookAtRotation = FRotationMatrix::MakeFromX(Direction).Rotator();
	LookAtRotation.Pitch = 0.0f;

	AIPawn->SetActorRotation(LookAtRotation);

	FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);	//	CALLS TASK FINISHED

	return EBTNodeResult::Succeeded;
}

FString UBBTask_LookAtObject::GetStaticDescription() const
{
	return FString::Printf(TEXT("Look at given object."));
}
