//Copyright(c) 2015 Michael Allar
#pragma once

#include "FullPanelWidget.generated.h"

UCLASS()
class UMGEXPLUGIN_API UFullPanelWidget : public UUMGExWidget
{
	GENERATED_UCLASS_BODY()

	UFUNCTION(BlueprintImplementableEvent)
	void OnOpenPanel();

	UFUNCTION(BlueprintImplementableEvent)
	void OnClosePanel();

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Widgets")
	UFullPanelSwitcherWidget* ParentSwitcherWidget;

protected:
	
};