// Copyright 2014 Michael Allar. All Rights Reserved.
#include "UMGExPlugin.h"


UButtonWidget::UButtonWidget(const class FObjectInitializer& PCIP)
	: Super(PCIP)
{
}

void UButtonWidget::TriggerOnPressed()
{
	if (!IsDesignTime())
	{
		OnPressed.Broadcast(Tag);
	}
}

UButtonWidget* UButtonWidget::CreateButtonWidget(APlayerController* PlayerController, TSubclassOf<UButtonWidget> ButtonClass, const FWidgetInfo& WidgetInfo)
{
	UButtonWidget* NewButtonWidget = CreateWidget<UButtonWidget>(PlayerController, ButtonClass);
	NewButtonWidget->Label = WidgetInfo.Label;
	NewButtonWidget->Tag = WidgetInfo.Tag;
	return NewButtonWidget;
}

UButtonWidget* UButtonWidget::CreateButtonWidget(UWorld* World, TSubclassOf<UButtonWidget> ButtonClass, const FWidgetInfo& WidgetInfo)
{
	UButtonWidget* NewButtonWidget = CreateWidget<UButtonWidget>(World, ButtonClass);
	NewButtonWidget->Label = WidgetInfo.Label;
	NewButtonWidget->Tag = WidgetInfo.Tag;
	return NewButtonWidget;
}


