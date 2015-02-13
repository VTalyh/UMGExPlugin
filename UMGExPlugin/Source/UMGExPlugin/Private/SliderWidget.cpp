// Copyright 2014 Michael Allar. All Rights Reserved.

#include "UMGExPlugin.h"

USliderWidget::USliderWidget(const class FObjectInitializer& PCIP)
	: Super(PCIP)
{
	/*
	** @TODO: We are heavily relying on UMG Editor to create a CanvasPanel for root when a blueprint
	** class of URadioScrollerWidget is made. When Epic creates more non-bp user widget logic, we should revisit this
	*/

	bTreatValueAsInt = false;
	MinValue = 0;
	MaxValue = 1;
	NormalizedValue = 0;
}

void USliderWidget::SetValue(const float NewValue, const bool bNormalized /*= false*/, const bool bForceValueChangeEvent /*= false*/, const bool bSkipValueChangeEvent /*= false*/)
{
	float OldValue = NormalizedValue;

	if (bNormalized)
	{
		NormalizedValue = NewValue;
	}
	else
	{
		NormalizedValue = FMath::GetRangePct(MinValue, MaxValue, NewValue);
	}

	ensure(NormalizedValue >= 0 && NormalizedValue <= 1);

	NormalizedValue = FMath::Clamp<float>(NormalizedValue, 0.0f, 1.0f);

	if ((OldValue != NewValue || bForceValueChangeEvent) && !bSkipValueChangeEvent)
	{
		OnValueChanged.Broadcast(Tag, GetValue());
	}
}

float USliderWidget::GetValue(const bool bNormalized /*= false*/) const
{
	if (bNormalized)
	{
		return NormalizedValue;
	}
	else
	{
		const float RetValue = FMath::Lerp<float, float>(MinValue, MaxValue, NormalizedValue);
		return bTreatValueAsInt ? FMath::FloorToFloat(RetValue) : RetValue;
	}
}

TSharedRef<SWidget> USliderWidget::RebuildWidget()
{
	// Root widget is assumed to be CanvasPanel. See @TODO in Constructor
	TSharedRef<SWidget> RootSlateWidget = Super::RebuildWidget();

	if (!IsDesignTime())
	{
		// Set the initial value which will also invalidate it if a bad value is present
		SetValue(NormalizedValue, true, bTriggerChangeEventOnCreate, !bTriggerChangeEventOnCreate);
	}

	return RootSlateWidget;
}

USliderWidget* USliderWidget::CreateSliderWidget(APlayerController* PlayerController, TSubclassOf<USliderWidget> SliderClass, const FSliderInfo& WidgetInfo)
{
	USliderWidget* SliderWidget = CreateWidget<USliderWidget>(PlayerController, SliderClass);
	SliderWidget->Label = WidgetInfo.Label;
	SliderWidget->Tag = WidgetInfo.Tag;
	SliderWidget->bTreatValueAsInt = WidgetInfo.bTreatValueAsInt;
	SliderWidget->bTriggerChangeEventOnCreate = WidgetInfo.bTriggerChangeEventOnCreate;
	SliderWidget->MinValue = WidgetInfo.MinValue;
	SliderWidget->MaxValue = WidgetInfo.MaxValue;
	SliderWidget->NormalizedValue = WidgetInfo.NormalizedValue;

	return SliderWidget;
}

USliderWidget* USliderWidget::CreateSliderWidget(UWorld* World, TSubclassOf<USliderWidget> SliderClass, const FSliderInfo& WidgetInfo)
{
	USliderWidget* SliderWidget = CreateWidget<USliderWidget>(World, SliderClass);
	SliderWidget->Label = WidgetInfo.Label;
	SliderWidget->Tag = WidgetInfo.Tag;
	SliderWidget->bTreatValueAsInt = WidgetInfo.bTreatValueAsInt;
	SliderWidget->bTriggerChangeEventOnCreate = WidgetInfo.bTriggerChangeEventOnCreate;
	SliderWidget->MinValue = WidgetInfo.MinValue;
	SliderWidget->MaxValue = WidgetInfo.MaxValue;
	SliderWidget->NormalizedValue = WidgetInfo.NormalizedValue;

	return SliderWidget;
}
