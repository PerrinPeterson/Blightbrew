// Copyright © Too Many Eyes , 2022

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BBTask_GetShelfLocations.generated.h"

/**
 * 
 */
UCLASS()
class BLIGHTBREW_API UBBTask_GetShelfLocations : public UBTTask_BlackboardBase
{
	GENERATED_BODY()

public:
	UBBTask_GetShelfLocations();

private:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	virtual FString GetStaticDescription() const override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Navigation", meta = (AllowPrivateAccess = true))
		float AcceptableRadius = 50.0f;
	
};
