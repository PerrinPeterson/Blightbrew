// Copyright © Too Many Eyes , 2022 - 2023


#include "BBBoundryVolume.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "BlightBrew/Characters/Player/BBPlayerCharacter.h"
#include "BlightBrew/UI/Loading/BBBlackScreenWidget.h"
#include "BlightBrew/UI/BBHUD.h"
#include "BlightBrew/Characters/CharacterComponents/BBDialogueComponent.h"
#include "BlightBrew/Gameplay/World/BBRespawnPoint.h"

// Sets default values
ABBBoundryVolume::ABBBoundryVolume()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	//Create the mesh
	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh Component"));
	RootComponent = MeshComponent;

	//MeshComponent->OnComponentBeginOverlap.AddDynamic(this, &ABBBoundryVolume::OnOverlapBegin);
	MeshComponent->SetHiddenInGame(true);
	MeshComponent->SetCollisionProfileName("OverlapAll");
	MeshComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	MeshComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);

	BoundryVolume = CreateDefaultSubobject<UBoxComponent>(TEXT("Box Component"));
	BoundryVolume->OnComponentBeginOverlap.AddDynamic(this, &ABBBoundryVolume::OnOverlapBegin);
	BoundryVolume->SetCollisionProfileName("OverlapAll");
	BoundryVolume->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	BoundryVolume->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);
	BoundryVolume->SetupAttachment(RootComponent);
	
	//Create the Dialogue Component
	DialogueComponent = CreateDefaultSubobject<UBBDialogueComponent>(TEXT("Dialogue Component"));
	//DialogueComponent->SetupAttachment(RootComponent);
	

}

// Called when the game starts or when spawned
void ABBBoundryVolume::BeginPlay()
{
	Super::BeginPlay();
	
	
}

void ABBBoundryVolume::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	//Check if it's a player
	if (OtherActor->IsA(ABBPlayerCharacter::StaticClass()))
	{
		//Cast to player
		ABBPlayerCharacter* player = static_cast<ABBPlayerCharacter*>(OtherActor);
		if (player->IsTeleporting())
			return;
		player->ToggleIsTeleporting();
		player->StopSprint();
		bFadeToBlack = true;
	}
}

// Called every frame
void ABBBoundryVolume::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bFadeToBlack)
	{
		//Grab the player
		ABBPlayerCharacter* Player = Cast<ABBPlayerCharacter>(GetWorld()->GetFirstPlayerController()->GetPawn());
		if (Player)
		{
			//Disable Player Input
			Player->DisableInput(GetWorld()->GetFirstPlayerController());
			//Fade to black
			float opacity = Player->GetBlackScreenWidget()->GetRenderOpacity();
			opacity += DeltaTime;
			Player->GetBlackScreenWidget()->SetRenderOpacity(opacity);
			//If the opacity is 1, then we can fade back in
			if (opacity >= 1)
			{
				//Teleport the player to the respawn place
				Player->SetActorLocation(RespawnPoint->GetActorLocation());
				Player->EnableInput(GetWorld()->GetFirstPlayerController());
				Player->GetHUD()->StartDialogue(DialogueComponent);
				bFadeToBlack = false;
				bFadeBackIn = true;
				Player->ToggleIsTeleporting();
			}
		}
	}
	else
	{
		if (bFadeBackIn)
		{
			//Grab the player
			ABBPlayerCharacter* Player = Cast<ABBPlayerCharacter>(GetWorld()->GetFirstPlayerController()->GetPawn());
			if (Player)
			{
				float opacity = Player->GetBlackScreenWidget()->GetRenderOpacity();
				opacity -= DeltaTime;
				Player->GetBlackScreenWidget()->SetRenderOpacity(opacity);
				if (opacity <= 0)
				{
					bFadeBackIn = false;
				}
			}
		}
	}
}

