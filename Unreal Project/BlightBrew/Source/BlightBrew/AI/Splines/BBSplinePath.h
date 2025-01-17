// Copyright © Too Many Eyes , 2022

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BBSplinePath.generated.h"

class USplineComponent;
UCLASS()
class BLIGHTBREW_API ABBSplinePath : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABBSplinePath();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	USplineComponent* GetSpline() { return SplineComponent; }

	FText GetPathID() { return PathID; }

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Spline")
		USplineComponent* SplineComponent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Spline")
		FText PathID;
};
