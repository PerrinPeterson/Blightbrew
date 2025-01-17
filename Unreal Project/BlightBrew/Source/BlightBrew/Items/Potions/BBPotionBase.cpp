// Copyright © Too Many Eyes , 2022


#include "BBPotionBase.h"
#include "PotionComponents/BBPotionComponent.h"
#include "PotionComponents/BBThrowableComp.h"
#include "../../Engine/Classes/GameFramework/ProjectileMovementComponent.h"
#include "../../Engine/Classes/Components/SphereComponent.h"

// Sets default values
ABBPotionBase::ABBPotionBase()
{
    // Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = true;
}

void ABBPotionBase::SetFocusText(FText text)
{
    FocusText = text;
}

FText ABBPotionBase::GetFocusText()
{
    return FocusText;
}

// Called when the game starts or when spawned
void ABBPotionBase::BeginPlay()
{
    Super::BeginPlay();

    OnActorHit.AddDynamic(this, &ABBPotionBase::OnHit);
}



// Called every frame
void ABBPotionBase::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

bool ABBPotionBase::OnUse(BBControlType controlType, AActor* instagatingActor)
{

    bool bSuccess = false;

    if (ItemComponents.IsEmpty())
    {
        //UE_LOG(LogTemp, Warning, TEXT("No components found on potion; Check the blueprint of the potion."));
        return false;
    }
    for (int i = 0; i < ItemComponents.Num(); i++)
    {
        if (!ItemComponents[i])
        {
            //UE_LOG(LogTemp, Warning, TEXT("One or more components are nullptr. Likely a logical error."));
            return false;
        }
    }
    for (int i = 0; i < ItemComponents.Num(); i++)
    {
        if (ItemComponents[i]->OnUse(this, controlType, instagatingActor))
        {
            bSuccess = true;
        }
    }

    return bSuccess;
}

void ABBPotionBase::OnFocus(AActor* InstigatingActor)
{
}

void ABBPotionBase::OnInteract(AActor* InstigatingActor)
{
    ABBBaseItem::OnInteract(InstigatingActor);
}

void ABBPotionBase::OnHit(AActor* SelfActor, AActor* OtherActor, FVector NormalImpulse, const FHitResult& Hit)
{
    TArray<UBBThrowableComp*> comps;
    comps = GetBBComponentsOfType<UBBThrowableComp>();
    for (int i = 0; i < comps.Num(); i++)
    {
        comps[i]->OnHit(SelfActor, OtherActor, NormalImpulse, Hit);
    }
}






