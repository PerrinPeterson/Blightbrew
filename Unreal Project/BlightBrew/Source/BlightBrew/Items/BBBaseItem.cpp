// Copyright © Too Many Eyes , 2022


#include "../Items/BBBaseItem.h"
#include "../Characters/Player/BBPlayerCharacter.h"
#include "../Engine/Classes/GameFramework/ProjectileMovementComponent.h"
#include "../Inventory/BBInventoryComponent.h"

// Sets default values
ABBBaseItem::ABBBaseItem()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh Component"));
	SetRootComponent(MeshComponent);
	MeshComponent->SetEnableGravity(true);
	MeshComponent->SetSimulatePhysics(true);
	//MeshComponent->SetMassOverrideInKg(NAME_Actor, 50.0f, true);
	MeshComponent->BodyInstance.bOverrideMass = true;
	MeshComponent->BodyInstance.SetMassOverride(50.0f);
	
	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Projectile Movement Component"));
	ProjectileMovementComponent->SetActive(true);
	ProjectileMovementComponent->SetAutoActivate(true);



}

// Called when the game starts or when spawned
void ABBBaseItem::BeginPlay()
{
	Super::BeginPlay();
	//Set the focus text of the item to the items name
	FocusText = FText::FromString(Name);
}  

// Called every frame
void ABBBaseItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABBBaseItem::OnFocus(AActor* InstigatingActor)
{
}

void ABBBaseItem::OnInteract(AActor* InstigatingActor)
{
	ABBPlayerCharacter* player = Cast<ABBPlayerCharacter>(InstigatingActor);

	if (player)
	{
		int64 amount = 1;
		if(player->GetInventoryComponent()->AddToInventory(this, amount))
		{
			Destroy();
		}
	}
}

bool ABBBaseItem::OnUse(BBControlType controlType, AActor* instagatingActor)
{
	return false;
}

void ABBBaseItem::SetFocusText(FText text)
{
	FocusText = text;
}

FText ABBBaseItem::GetFocusText()
{
	return FocusText;
}

