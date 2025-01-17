// Copyright © Too Many Eyes , 2022

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BBFaunaAITask_FindRandomLocation.generated.h"

/**
 * BTTask for finding a random location in a NavMesh
 */
UCLASS(Blueprintable)
class BLIGHTBREW_API UBBFaunaAITask_FindRandomLocation : public UBTTask_BlackboardBase
{
	GENERATED_BODY()

public:
	UBBFaunaAITask_FindRandomLocation();

private:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	virtual FString GetStaticDescription() const override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Search", meta = (AllowPrivateAccess = true))
		float SearchRadius = 500.0f ;
	
};
