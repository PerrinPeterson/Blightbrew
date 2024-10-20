// Copyright © Too Many Eyes , 2022

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "BBFaunaAIController.generated.h"

class UBehaviorTreeComponent;
/**
 * 
 */
UCLASS()
class BLIGHTBREW_API ABBFaunaAIController : public AAIController
{
	GENERATED_BODY()
public:
	ABBFaunaAIController();

protected:
	virtual void BeginPlay() override;
	virtual void OnPossess(APawn* InPawn) override;

private:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "AI", meta = (AllowPrivateAccess = true))
		TObjectPtr<UBehaviorTree> BehaviorTree;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AI", meta = (AllowPrivateAccess = true))
		TObjectPtr<UBehaviorTreeComponent> BehaviorTreeComponent;


	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AI", meta = (AllowPrivateAccess = true))
		TObjectPtr<UBlackboardComponent> BlackboardComponent;
};
