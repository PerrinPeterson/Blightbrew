// Copyright © Too Many Eyes , 2022

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BBTask_Barter.generated.h"

/**
 * 
 */
UCLASS()
class BLIGHTBREW_API UBBTask_Barter : public UBTTask_BlackboardBase
{
	GENERATED_BODY()

public:
	UBBTask_Barter();

private:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	virtual FString GetStaticDescription() const override;
	
};
