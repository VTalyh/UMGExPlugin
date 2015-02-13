// Copyright 2014 Michael Allar. All Rights Reserved.
#pragma once

#include "UMGExTypes.h"
#include "ButtonWidget.h"
#include "WidgetList.generated.h"

UCLASS()
class UMGEXPLUGIN_API UWidgetList : public UUMGExWidget
{
	GENERATED_UCLASS_BODY()

public:

	UPROPERTY(BlueprintReadOnly, EditInstanceOnly, Category = "Child Info")
	TArray<FWidgetInfoFactory> InfoList;

	/** Template button widget to use for child buttons */
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Info")
	TSubclassOf<UButtonWidget> ButtonClass;

	/** Template button widget to use for child buttons */
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Info")
	TSubclassOf<ULabelButtonWidget> LabelButtonClass;

	/** Template slider widget to use for sliders */
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Info")
	TSubclassOf<USliderWidget> SliderClass;

	/** Template radio scroller widget to use for radio scrollers */
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Info")
	TSubclassOf<URadioScrollerWidget> RadioScrollerClass;

	/** Desired Width and Height of all child widgets */
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Layout")
	FVector2D ChildWidgetSize;

	/** Spacing between child widgets */
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Layout")
	float ChildWidgetSpacing;

	/** When true, widgets are stacked vertically. When false, horizontal. */
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Layout")
	bool bIsVertical;

	/** Broadcasts whenever a child button is clicked */
	UPROPERTY(BlueprintAssignable, Category = "Events")
	FButtonWidgetOnPressedSignature OnButtonPressed;

	/** Broadcasts whenever a child slider value is changed */
	UPROPERTY(BlueprintAssignable, Category = "Events")
	FSliderWidgetOnChangedSignature OnSliderValueChanged;

	/** Broadcasts whenever a child radio scroller value is changed */
	UPROPERTY(BlueprintAssignable, Category = "Events")
	FRadioScrollerWidgetOnChangedSignature OnRadioScrollerValueChanged;

	/** Internal event called when a child button is pressed. This should trigger OnButtonClicked */
	UFUNCTION(BlueprintNativeEvent)
	void OnButtonPressed_Internal(const FName ButtonTag);

	/** Internal event called when a slider widget value is changed. This should trigger OnSliderValueChanged */
	UFUNCTION(BlueprintNativeEvent)
	void OnSliderValueChanged_Internal(const FName SliderTag, const float NewValue);

	/** Internal event called when a radio scroller widget value is changed. This should trigger OnRadioScrollerValueChanged */
	UFUNCTION(BlueprintNativeEvent)
	void OnRadioScrollerValueChanged_Internal(const FName RadioScrollerTag, const FName NewChoiceTag);

	UFUNCTION(BlueprintCallable, Category = "Widgets")
	URadioScrollerWidget* GetRadioScrollerWidgetWithTag(const FName SearchTag) const;

	UFUNCTION(BlueprintCallable, Category = "Widgets")
	UButtonWidget* GetButtonWidgetWithTag(const FName SearchTag) const;

	UFUNCTION(BlueprintCallable, Category = "Widgets")
	USliderWidget* GetSliderWidgetWithTag(const FName SearchTag) const;

	template<class T>
	T* GetWidgetWithTag(const FName& SearchTag) const;

	UFUNCTION(BlueprintCallable, Category = "Widgets")
	UUMGExWidget* AddWidgetFromFactory(const FWidgetInfoFactory& InfoFactory);

protected:
	virtual TSharedRef<SWidget> RebuildWidget() override;
};
