// Copyright 2014 Michael Allar. All Rights Reserved.
#pragma once

#include "UMGExTypes.h"
#include "SliderWidget.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FSliderWidgetOnChangedSignature, const FName, SliderTag, const float, NewValue);

/**
*
*/
UCLASS()
class UMGEXPLUGIN_API USliderWidget : public UUMGExWidget
{
	GENERATED_UCLASS_BODY()

	/** Static method for initializing widget from a slider info struct */
	UFUNCTION(BlueprintCallable, Category = "User Interface")
	static USliderWidget* CreateSliderWidget(APlayerController* PlayerController, TSubclassOf<USliderWidget> SliderClass, const FSliderInfo& WidgetInfo);

	/** Static method for initializing widget from a slider info struct */
	static USliderWidget* CreateSliderWidget(UWorld* World, TSubclassOf<USliderWidget> SliderClass, const FSliderInfo& WidgetInfo);

	/** Broadcasts whenever a this button is pressed */
	UPROPERTY(BlueprintAssignable, Category = "Info")
	FSliderWidgetOnChangedSignature OnValueChanged;

	UFUNCTION(BlueprintCallable, Category = "Info")
	void SetValue(const float NewValue, const bool bNormalized = false, const bool bForceValueChangeEvent = false, const bool bSkipValueChangeEvent = false);

	UFUNCTION(BlueprintCallable, Category = "Info")
	float GetValue(const bool bNormalized = false) const;


	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Meta = (AlwaysAsPin), Category = "Info")
	bool bTreatValueAsInt;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Meta = (AlwaysAsPin), Category = "Info")
	bool bTriggerChangeEventOnCreate;

	UPROPERTY(EditDefaultsOnly, Meta = (AlwaysAsPin), Category = "Info")
	float MinValue;

	UPROPERTY(EditDefaultsOnly, Meta = (AlwaysAsPin), Category = "Info")
	float MaxValue;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Meta = (AlwaysAsPin), Category = "Info", Meta = (UIMin = 0, UIMax = 1, ClampMin = 0, ClampMax = 1))
	float NormalizedValue;

protected:
	virtual TSharedRef<SWidget> RebuildWidget() override;
};