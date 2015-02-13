//Copyright(c) 2015 Michael Allar
#pragma once

#include "UMGExTypes.h"
#include "RadioScrollerWidget.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FRadioScrollerWidgetOnChangedSignature, const FName, RadioScrollerTag, const FName, NewChoiceTag);

/**
*
*/
UCLASS()
class UMGEXPLUGIN_API URadioScrollerWidget : public UUMGExWidget
{
	GENERATED_UCLASS_BODY()

	/** Static method for initializing widget from a widget info struct */
	UFUNCTION(BlueprintCallable, Category = "User Interface")
	static URadioScrollerWidget* CreateRadioScrollerWidget(APlayerController* PlayerController, TSubclassOf<URadioScrollerWidget> RadioScrollerClass, const FRadioScrollerInfo& WidgetInfo);

	/** Static method for initializing widget from a widget info struct */
	static URadioScrollerWidget* CreateRadioScrollerWidget(UWorld* World, TSubclassOf<URadioScrollerWidget> RadioScrollerClass, const FRadioScrollerInfo& WidgetInfo);

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Meta = (AlwaysAsPin), Category = "Info")
	int32 SelectedChoice;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Meta = (AlwaysAsPin), Category = "Info")
	TArray<FWidgetInfo> Choices;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Meta = (AlwaysAsPin), Category = "Info")
	bool bTriggerChangeEventOnCreate;

	/** Broadcasts whenever a this button is pressed */
	UPROPERTY(BlueprintAssignable, Category = "Info")
	FRadioScrollerWidgetOnChangedSignature OnChoiceChanged;

	/** Should be called when the selected choice changes */
	UFUNCTION(BlueprintCallable, Category = "Info")
	void AddChoice(const FWidgetInfo& NewChoice, const bool bSetSelected = false, const bool bForceChangeEvent = false, const bool bSkipChangeEvent = false);

	/** Should be called when the selected choice changes */
	UFUNCTION(BlueprintCallable, Category = "Info")
	void SetSelectedChoice(int32 NewChoice, bool bRelative = false, bool bForceChangeEvent = false, bool bSkipChangeEvent = false);

	UFUNCTION(BlueprintCallable, Category = "Info")
	FWidgetInfo GetSelectedChoice() const;

	UFUNCTION(BlueprintCallable, Category = "Info")
	int32 GetSelectedChoiceIndex() const;

	UFUNCTION(BlueprintCallable, Category = "Info")
	FText GetSelectedChoiceLabel() const;

	UFUNCTION(BlueprintCallable, Category = "Info")
	FName GetSelectedChoiceTag() const;

	void EnsureValidChoiceIndex() const;

protected:
	virtual TSharedRef<SWidget> RebuildWidget() override;
};