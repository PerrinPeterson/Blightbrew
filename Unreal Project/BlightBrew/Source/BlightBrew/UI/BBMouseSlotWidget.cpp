// Copyright © Too Many Eyes , 2022


#include "BlightBrew/UI/BBMouseSlotWidget.h"

#include "Kismet/GameplayStatics.h"

void UBBMouseSlotWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);


	float mouseX;
	float mouseY;
	UGameplayStatics::GetPlayerController(GetWorld(), 0)->GetMousePosition(mouseX, mouseY);
	SetPositionInViewport(FVector2D(mouseX, mouseY));

}

void UBBMouseSlotWidget::NativeConstruct()
{
	Super::NativeConstruct();

	//	Sets it as visible, but Mouse Ignores it 
	SetVisibility(ESlateVisibility::HitTestInvisible);	//	Will not overlap mouse
}
