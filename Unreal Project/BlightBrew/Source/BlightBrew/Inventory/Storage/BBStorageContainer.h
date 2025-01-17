// Copyright © Too Many Eyes , 2022

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "../../Gameplay/BBInterface.h"
#include "BBStorageContainer.generated.h"

class ABBBaseItem;
UCLASS(Abstract, NotBlueprintable)
class BLIGHTBREW_API ABBStorageContainer : public AActor, public IBBInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABBStorageContainer();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UStaticMeshComponent* BodyMesh;
	

public:
	virtual void OnFocus(AActor* InstigatingActor) override;

	virtual void OnInteract(AActor* InstigatingActor) override;

	FORCEINLINE virtual void SetFocusText(FText text) override { FocusText = text; }

	FORCEINLINE virtual FText GetFocusText() override { return FocusText; }

	virtual TArray<ABBBaseItem*> GetItems();
	virtual TArray<TSubclassOf<ABBBaseItem>> GetItemClasses();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Focus)
		FText FocusText;

	

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
