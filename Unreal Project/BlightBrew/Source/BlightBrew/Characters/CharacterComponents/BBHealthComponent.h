// Copyright © Too Many Eyes , 2022

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "BBHealthComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BLIGHTBREW_API UBBHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UBBHealthComponent();

	void Init();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Health, meta = (AllowPrivateAccess = "true"))
		float CurrentHealth;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Health, meta = (AllowPrivateAccess = "true"))
		float MaxHealth;

public:

	UFUNCTION(BlueprintCallable)
		FORCEINLINE float GetHealth() { return CurrentHealth; }

	UFUNCTION(BlueprintCallable)
		FORCEINLINE float GetMaxHealth() { return MaxHealth; }

	UFUNCTION(BlueprintCallable)
		FORCEINLINE void SetMaxHealth(float value) { MaxHealth = value; }
};
