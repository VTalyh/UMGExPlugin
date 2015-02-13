// Copyright 2014 Michael Allar. All Rights Reserved.

#include "UMGExPlugin.h"

URadioScrollerWidget::URadioScrollerWidget(const class FObjectInitializer& PCIP)
: Super(PCIP)
{
	/*
	** @TODO: We are heavily relying on UMG Editor to create a CanvasPanel for root when a blueprint
	** class of URadioScrollerWidget is made. When Epic creates more non-bp user widget logic, we should revisit this
	*/

	SelectedChoice = -1;
	bTriggerChangeEventOnCreate = false;
}

void URadioScrollerWidget::SetSelectedChoice(int32 NewChoice, bool bRelative /*= false*/, bool bForceChangeEvent /*= false*/, bool bSkipChangeEvent /*= false*/)
{
	int32 OldChoice = SelectedChoice;

	EnsureValidChoiceIndex(); // Make sure we start with a valid index

	if (Choices.Num() > 0)
	{
		// Useful for incrementing or decrementing
		if (bRelative)
		{
			SelectedChoice += NewChoice;
			if (SelectedChoice < 0)
			{
				while (SelectedChoice < 0)
				{
					SelectedChoice += Choices.Num();
				}
			}
			else
			{
				SelectedChoice %= Choices.Num();
			}
		}
		else
		{
			SelectedChoice = NewChoice;
			EnsureValidChoiceIndex();
		}
	}

	if ((OldChoice != SelectedChoice || bForceChangeEvent) && !bSkipChangeEvent)
	{
		OnChoiceChanged.Broadcast(Tag, GetSelectedChoiceTag());
	}
}

FWidgetInfo URadioScrollerWidget::GetSelectedChoice() const
{
	EnsureValidChoiceIndex();
	if (SelectedChoice >= 0)
	{
		return Choices[SelectedChoice];
	}

	return FWidgetInfo(FText::FromString(TEXT("error")), TEXT("error"));
}

int32 URadioScrollerWidget::GetSelectedChoiceIndex() const
{
	return SelectedChoice;
}

FText URadioScrollerWidget::GetSelectedChoiceLabel() const
{
	EnsureValidChoiceIndex();
	if (SelectedChoice >= 0)
	{
		return Choices[SelectedChoice].Label;
	}

	return FText::FromString(TEXT("error"));
}

FName URadioScrollerWidget::GetSelectedChoiceTag() const
{
	EnsureValidChoiceIndex();
	if (SelectedChoice >= 0)
	{
		return Choices[SelectedChoice].Tag;
	}

	return FName(TEXT("error"));
}

TSharedRef<SWidget> URadioScrollerWidget::RebuildWidget()
{
	// Root widget is assumed to be CanvasPanel. See @TODO in Constructor
	TSharedRef<SWidget> RootSlateWidget = Super::RebuildWidget();

	if (!IsDesignTime())
	{
		// Set the initial choice which will also invalidate it if bad choice data is present
		SetSelectedChoice(SelectedChoice, false, bTriggerChangeEventOnCreate, !bTriggerChangeEventOnCreate);
	}
	

	return RootSlateWidget;
}

void URadioScrollerWidget::EnsureValidChoiceIndex() const
{
	auto ConstThis = const_cast< URadioScrollerWidget* >(this);	// Hack because Header Generator doesn't yet support mutable keyword

	if (Choices.Num() <= 0)
	{
		ConstThis->SelectedChoice = -1;
	}
	else if (SelectedChoice <= 0 || SelectedChoice >= Choices.Num())
	{
		ConstThis->SelectedChoice = 0;
	}
}

URadioScrollerWidget* URadioScrollerWidget::CreateRadioScrollerWidget(APlayerController* PlayerController, TSubclassOf<URadioScrollerWidget> RadioScrollerClass, const FRadioScrollerInfo& WidgetInfo)
{
	URadioScrollerWidget* RadioScrollerWidget = CreateWidget<URadioScrollerWidget>(PlayerController, RadioScrollerClass);
	RadioScrollerWidget->Label = WidgetInfo.Label;
	RadioScrollerWidget->Tag = WidgetInfo.Tag;
	RadioScrollerWidget->Choices = WidgetInfo.Choices;
	RadioScrollerWidget->bTriggerChangeEventOnCreate = WidgetInfo.bTriggerChangeEventOnCreate;

	return RadioScrollerWidget;
}

URadioScrollerWidget* URadioScrollerWidget::CreateRadioScrollerWidget(UWorld* World, TSubclassOf<URadioScrollerWidget> RadioScrollerClass, const FRadioScrollerInfo& WidgetInfo)
{
	URadioScrollerWidget* RadioScrollerWidget = CreateWidget<URadioScrollerWidget>(World, RadioScrollerClass);
	RadioScrollerWidget->Label = WidgetInfo.Label;
	RadioScrollerWidget->Tag = WidgetInfo.Tag;
	RadioScrollerWidget->Choices = WidgetInfo.Choices;
	RadioScrollerWidget->bTriggerChangeEventOnCreate = WidgetInfo.bTriggerChangeEventOnCreate;

	return RadioScrollerWidget;
}

void URadioScrollerWidget::AddChoice(const FWidgetInfo& NewChoice, const bool bSetSelected /*= false*/, const bool bForceChangeEvent /*= false*/, const bool bSkipChangeEvent /*= false*/)
{
	Choices.Add(NewChoice);
	if (bSetSelected)
	{
		SetSelectedChoice(Choices.Num() - 1, false, bForceChangeEvent, bSkipChangeEvent);
	}
}

