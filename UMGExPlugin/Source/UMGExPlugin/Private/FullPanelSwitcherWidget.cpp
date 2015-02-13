// Copyright 2014 Michael Allar. All Rights Reserved.

#include "UMGExPlugin.h"

UFullPanelSwitcherWidget::UFullPanelSwitcherWidget(const class FObjectInitializer& PCIP)
	: Super(PCIP)
{
	/*
	** @TODO: We are heavily relying on UMG Editor to create a CanvasPanel for root when a blueprint
	** class of UWidgetList is made. When Epic creates more non-bp user widget logic, we should revisit this
	*/

	CurrentlyOpenPanel = nullptr;

}

TSharedRef<SWidget> UFullPanelSwitcherWidget::RebuildWidget()
{
	
	TSharedRef<SWidget> RootSlateWidget = Super::RebuildWidget();
	
	// Root widget is assumed to be a Panel Widget.
	UPanelWidget* Panel = Cast<UPanelWidget>(GetRootWidget());
	if (Panel == nullptr)
	{
		return RootSlateWidget;
	}

	if (!IsDesignTime())
	{
		// AFAIK a UserWidget is always guaranteed an owning player at runtime? @TODO: Revisit and confirm
		APlayerController* OwningPC = GetOwningPlayer();
		check(OwningPC);

		// Clear all existing panels. 
		CurrentlyOpenPanel = nullptr;
		Panel->ClearChildren();

		this->ForceLayoutPrepass();
		

		// Open initial panel
		if (OpenPanel(InitialPanel))
		{
		}
		else
		{
			UE_LOG(LogUMGEx, Warning, TEXT("%s::RebuildWidget could not find an initial panel: %s"), *GetFullName(GetWorld()->GetGameInstance()), *InitialPanel.ToString());
		}
	}

	return RootSlateWidget;
}

bool UFullPanelSwitcherWidget::OpenPanel(FName PanelTag)
{
	for (FFullPanelWidgetInfo Info : PanelInfos)
	{
		if (Info.Tag == PanelTag)
		{
			if (CurrentlyOpenPanel)
			{
				CurrentlyOpenPanel->OnClosePanel();
				CurrentlyOpenPanel->SetVisibility(ESlateVisibility::Hidden);
				CurrentlyOpenPanel = nullptr;
			}

			// Root widget is assumed to be a Panel Widget.
			UPanelWidget* Panel = CastChecked<UPanelWidget>(GetRootWidget());
			Panel->ClearChildren();

#if WITH_EDITOR
			UE_LOG(LogUMGEx, VeryVerbose, TEXT("%s::OpenPanel creating panel: %s"), *GetFullName(GetWorld()->GetGameInstance()), *Info.PanelClass->GetDisplayNameText().ToString());
#endif

			CurrentlyOpenPanel = CreateWidget<UFullPanelWidget>(GetOwningPlayer(), Info.PanelClass);
			CurrentlyOpenPanel->ParentSwitcherWidget = this;
			CurrentlyOpenPanel->Tag = Info.Tag;
			CurrentlyOpenPanel->Label = Info.Label;
			CurrentlyOpenPanel->SetVisibility(Info.VisibilityOnOpen);
			Panel->AddChild(CurrentlyOpenPanel);
			CurrentlyOpenPanel->OnOpenPanel();

			return true;
		}
	}

	UE_LOG(LogUMGEx, Warning, TEXT("%s::OpenPanel called but could not find supplied PanelTag: %s"), *GetFullName(), *PanelTag.ToString());
	return false;

}

class UFullPanelWidget* UFullPanelSwitcherWidget::GetCurrentlyOpenPanel() const
{
	return CurrentlyOpenPanel;
}
