//Copyright(c) 2015 Michael Allar

#include "UMGExPlugin.h"

UWidgetList::UWidgetList(const class FObjectInitializer& PCIP)
	: Super(PCIP)
{
	/*
	** @TODO: We are heavily relying on UMG Editor to create a CanvasPanel for root when a blueprint
	** class of UWidgetList is made. When Epic creates more non-bp user widget logic, we should revisit this
	*/

	ChildWidgetSize = FVector2D(256.0f, 48.0f);
}

TSharedRef<SWidget> UWidgetList::RebuildWidget()
{
	// Root widget is assumed to be CanvasPanel. See @TODO in Constructor
	TSharedRef<SWidget> RootSlateWidget = Super::RebuildWidget();
	UCanvasPanel* CanvasPanel = CastChecked<UCanvasPanel>(GetRootWidget());

	if (!IsDesignTime())
	{
		// Clear all existing buttons. 
		CanvasPanel->ClearChildren();

		// AFAIK a UserWidget is always guaranteed an owning player at runtime? @TODO: Revisit and confirm
		APlayerController* OwningPC = GetOwningPlayer();

		if (!OwningPC)
		{
			UE_LOG(LogUMGEx, Error, TEXT("%s::RebuildWidget called without Owning Player."), *GetFullName());
			return RootSlateWidget;
		}

		// Create our child widgets
		for (int32 i = 0; i < InfoList.Num(); ++i)
		{
			UUMGExWidget* ChildWidget = AddWidgetFromFactory(InfoList[i]);
			if (ChildWidget == NULL)
			{
				UE_LOG(LogUMGEx, Error, TEXT("%s::RebuildWidget failed to create child widget as its InfoList contains a bad entry (index: %d)."), *GetFullName(GetWorld()->GetGameInstance()), i);
				continue;
			}			
		}

		UCanvasPanelSlot* ParentSlot = Cast<UCanvasPanelSlot>(CanvasPanel->Slot);
		if (ParentSlot != NULL)
		{
			if (bIsVertical)
			{
				ParentSlot->SetSize(FVector2D(ChildWidgetSize.X, InfoList.Num() * ChildWidgetSize.Y + ChildWidgetSpacing));
			}
		}
	}

	return RootSlateWidget;
}

void UWidgetList::OnButtonPressed_Internal_Implementation(const FName ButtonTag)
{
	OnButtonPressed.Broadcast(ButtonTag);
}

void UWidgetList::OnSliderValueChanged_Internal_Implementation(const FName SliderTag, const float NewValue)
{
	OnSliderValueChanged.Broadcast(SliderTag, NewValue);
}

void UWidgetList::OnRadioScrollerValueChanged_Internal_Implementation(const FName RadioScrollerTag, const FName NewChoiceTag)
{
	OnRadioScrollerValueChanged.Broadcast(RadioScrollerTag, NewChoiceTag);
}

URadioScrollerWidget* UWidgetList::GetRadioScrollerWidgetWithTag(const FName SearchTag) const
{
	return GetWidgetWithTag<URadioScrollerWidget>(SearchTag);
}

USliderWidget* UWidgetList::GetSliderWidgetWithTag(const FName SearchTag) const
{
	return GetWidgetWithTag<USliderWidget>(SearchTag);
}

UButtonWidget* UWidgetList::GetButtonWidgetWithTag(const FName SearchTag) const
{
	return GetWidgetWithTag<UButtonWidget>(SearchTag);
}


template<class T>
T* UWidgetList::GetWidgetWithTag(const FName& SearchTag) const
{
	TArray<UWidget*> Widgets;
	WidgetTree->GetAllWidgets(Widgets);

	for (UWidget* Widget : Widgets)
	{
		T* FoundWidget = Cast<T>(Widget);
		if (FoundWidget != NULL && FoundWidget->Tag == SearchTag)
		{
			return FoundWidget;
		}
	}

	return NULL;
}

UUMGExWidget* UWidgetList::AddWidgetFromFactory(const FWidgetInfoFactory& InfoFactory)
{
	UUMGExWidget* ChildWidget = nullptr;

	APlayerController* OwningPC = GetOwningPlayer();
	if (!OwningPC)
	{
		UE_LOG(LogUMGEx, Error, TEXT("%s::AddWidgetFromFactory called without Owning Player."), *GetFullName());
		return nullptr;
	}

	if (InfoFactory.bButton && ButtonClass)
	{
#if WITH_EDITOR
		UE_LOG(LogUMGEx, VeryVerbose, TEXT("%s::AddWidgetFromFactory creating button widget %s with tag: %s"), *GetFullName(GetWorld()->GetGameInstance()), *ButtonClass->GetDisplayNameText().ToString(), *InfoFactory.ButtonInfo.Tag.ToString());
#endif

		UButtonWidget* ButtonWidget = UButtonWidget::CreateButtonWidget(OwningPC, ButtonClass, InfoFactory.ButtonInfo);
		ChildWidget = ButtonWidget;

		// @TODO: Look into how a newly created widget could already have OnPressed bound
		if (!ButtonWidget->OnPressed.IsAlreadyBound(this, &UWidgetList::OnButtonPressed_Internal))
		{
			ButtonWidget->OnPressed.AddDynamic(this, &UWidgetList::OnButtonPressed_Internal);
		}
	}
	else if (InfoFactory.bLabelButton && LabelButtonClass)
	{

#if WITH_EDITOR
		UE_LOG(LogUMGEx, VeryVerbose, TEXT("%s::AddWidgetFromFactory creating label button widget %s with tag: %s"), *GetFullName(GetWorld()->GetGameInstance()), *LabelButtonClass->GetDisplayNameText().ToString(), *InfoFactory.LabelButtonInfo.Tag.ToString());
#endif 

		ULabelButtonWidget* LabelButtonWidget = ULabelButtonWidget::CreateLabelButtonWidget(OwningPC, LabelButtonClass, InfoFactory.LabelButtonInfo);
		ChildWidget = LabelButtonWidget;

		if (!LabelButtonWidget->OnPressed.IsAlreadyBound(this, &UWidgetList::OnButtonPressed_Internal))
		{
			LabelButtonWidget->OnPressed.AddDynamic(this, &UWidgetList::OnButtonPressed_Internal);
		}
	}
	else if (InfoFactory.bSlider && SliderClass)
	{

#if WITH_EDITOR
		UE_LOG(LogUMGEx, VeryVerbose, TEXT("%s::AddWidgetFromFactory creating slider widget %s with tag: %s"), *GetFullName(GetWorld()->GetGameInstance()), *SliderClass->GetDisplayNameText().ToString(), *InfoFactory.SliderInfo.Tag.ToString());
#endif

		USliderWidget* SliderWidget = USliderWidget::CreateSliderWidget(OwningPC, SliderClass, InfoFactory.SliderInfo);
		ChildWidget = SliderWidget;

		// @TODO: Look into how a newly created widget could already have OnPressed bound
		if (!SliderWidget->OnValueChanged.IsAlreadyBound(this, &UWidgetList::OnSliderValueChanged_Internal))
		{
			SliderWidget->OnValueChanged.AddDynamic(this, &UWidgetList::OnSliderValueChanged_Internal);
		}
	}
	else if (InfoFactory.bRadioScroller && RadioScrollerClass)
	{

#if WITH_EDITOR
		UE_LOG(LogUMGEx, VeryVerbose, TEXT("%s::AddWidgetFromFactory creating radio scroller widget %s with tag: %s"), *GetFullName(GetWorld()->GetGameInstance()), *RadioScrollerClass->GetDisplayNameText().ToString(), *InfoFactory.RadioScrollerInfo.Tag.ToString());
#endif

		URadioScrollerWidget* RadioScrollerWidget = URadioScrollerWidget::CreateRadioScrollerWidget(OwningPC, RadioScrollerClass, InfoFactory.RadioScrollerInfo);
		ChildWidget = RadioScrollerWidget;

		// @TODO: Look into how a newly created widget could already have OnPressed bound
		if (!RadioScrollerWidget->OnChoiceChanged.IsAlreadyBound(this, &UWidgetList::OnRadioScrollerValueChanged_Internal))
		{
			RadioScrollerWidget->OnChoiceChanged.AddDynamic(this, &UWidgetList::OnRadioScrollerValueChanged_Internal);
		}
	}

	if (ChildWidget == nullptr)
	{

#if WITH_EDITOR
		UE_LOG(LogUMGEx, Error, TEXT("%s::AddWidgetFromFactory failed to create child widget as the passed InfoList is invalid."), *GetFullName(GetWorld()->GetGameInstance()));
#endif

		return nullptr;
	}

	UCanvasPanel* Panel = CastChecked<UCanvasPanel>(GetRootWidget());
	if (Panel != nullptr)
	{
		UCanvasPanelSlot* ChildSlot = Panel->AddChildToCanvas(ChildWidget);
		int index = Panel->GetChildIndex(ChildWidget);
		UE_LOG(LogUMGEx, VeryVerbose, TEXT("AddWidgetFromFactory last created widget has index of %d"), index);

		ChildSlot->SetSize(ChildWidgetSize);

		FAnchorData AnchorData;
		AnchorData.Alignment = ChildSlot->GetAlignment();
		AnchorData.Anchors = ChildSlot->GetAnchors();
		AnchorData.Offsets = ChildSlot->GetOffsets();

		if (bIsVertical)
		{
			ChildSlot->SetPosition(FVector2D(0, index * (ChildWidgetSize.Y + ChildWidgetSpacing)));
		}
		else
		{
			ChildSlot->SetPosition(FVector2D(index * (ChildWidgetSize.X + ChildWidgetSpacing), 0));
		}

#if WITH_EDITOR
		ChildSlot->RebaseLayout();
		ChildSlot->SaveBaseLayout();
#endif
		ChildSlot->SynchronizeProperties();

		
	}	

	return ChildWidget;	
}
