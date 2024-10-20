// Copyright © Too Many Eyes , 2022


#include "BlightBrew/AI/Splines/BBSplinePath.h"

#include "Components/SplineComponent.h"

// Sets default values
ABBSplinePath::ABBSplinePath()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


	SplineComponent = CreateDefaultSubobject<USplineComponent>(TEXT("Spline Component"));
}

// Called when the game starts or when spawned
void ABBSplinePath::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABBSplinePath::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

