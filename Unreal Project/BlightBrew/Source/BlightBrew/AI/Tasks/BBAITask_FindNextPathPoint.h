// Copyright © Too Many Eyes , 2022

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BBAITask_FindNextPathPoint.generated.h"

/**
 * 
 */
UCLASS()
class BLIGHTBREW_API UBBAITask_FindNextPathPoint : public UBTTask_BlackboardBase
{
	GENERATED_BODY()

public:
	UBBAITask_FindNextPathPoint();

private:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	virtual FString GetStaticDescription() const override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Navigation", meta = (AllowPrivateAccess = true))
		float AcceptableRadius = 50.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Navigation", meta = (AllowPrivateAccess = true))
		int32 CurrentPoint = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Navigation", meta = (AllowPrivateAccess = true))
		int32 NextPoint = 0;
	
};
