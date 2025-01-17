// Copyright © Too Many Eyes , 2022

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BBTask_GoToCheckout.generated.h"

/**
 * 
 */
UCLASS()
class BLIGHTBREW_API UBBTask_GoToCheckout : public UBTTask_BlackboardBase
{
	GENERATED_BODY()

public:
	UBBTask_GoToCheckout();

private:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	virtual FString GetStaticDescription() const override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Navigation", meta = (AllowPrivateAccess = true))
		float AcceptableRadius = 200.0f;
	
};
