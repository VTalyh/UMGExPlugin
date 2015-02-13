//Copyright(c) 2015 Michael Allar
#pragma once

#include "UMGExTypes.h"
#include "FullPanelSwitcherWidget.generated.h"

/**
*
*/
UCLASS(Blueprintable, Abstract)
class UMGEXPLUGIN_API UFullPanelSwitcherWidget : public UUMGExWidget
{
	GENERATED_UCLASS_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "User Interface")
	TArray<FFullPanelWidgetInfo> PanelInfos;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "User Interface")
	FName InitialPanel;

	UFUNCTION(BlueprintCallable, Category = "User Interface")
	bool OpenPanel(FName PanelTag);

	UFUNCTION(BlueprintCallable, Category = "User Interface")
	class UFullPanelWidget* GetCurrentlyOpenPanel() const;

protected:
	virtual TSharedRef<SWidget> RebuildWidget() override;

	class UFullPanelWidget* CurrentlyOpenPanel;

};
