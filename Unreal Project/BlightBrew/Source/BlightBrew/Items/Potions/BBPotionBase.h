// Copyright © Too Many Eyes , 2022

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "../BBBaseItem.h"
#include "BBPotionBase.generated.h"

class UBBPotionComponent;
class UProjectileMovementComponent;
class USphereComponent;

UCLASS()
class BLIGHTBREW_API ABBPotionBase : public ABBBaseItem
{
    GENERATED_BODY()

public:
    // Sets default values for this actor's properties
    ABBPotionBase();


   /* UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "BlightBrew|Throwable")
        UProjectileMovementComponent* projectileMovementComponent;*/

    virtual void SetFocusText(FText text) override;
    virtual FText GetFocusText() override;

    
protected:
    // Called when the game starts or when spawned
    virtual void BeginPlay() override;

public:
    // Called every frame
    virtual void Tick(float DeltaTime) override;

public:
    virtual bool OnUse(BBControlType controlType, AActor* instagatingActor) override;

    virtual void OnFocus(AActor* InstigatingActor) override;
    virtual void OnInteract(AActor* InstigatingActor) override;

    UFUNCTION()
        void OnHit(AActor* SelfActor, AActor* OtherActor, FVector NormalImpulse, const FHitResult& Hit);


public:
    UPROPERTY(EditAnywhere, Instanced, BlueprintReadWrite, Category = "BlightBrew|Components")
        TArray<UBBPotionComponent*> ItemComponents;
    
    template <typename T>
    TArray<T*> GetBBComponentsOfType()
    {
        TArray<T*> comps;
        for (int i = 0; i < ItemComponents.Num(); i++)
        {
            T* comp = Cast<T>(ItemComponents[i]);
            if (comp)
            {
                comps.Add(comp);
            }
        }
        return comps;
    }

};
