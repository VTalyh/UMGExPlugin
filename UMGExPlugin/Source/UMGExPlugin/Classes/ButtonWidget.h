// Copyright 2014 Michael Allar. All Rights Reserved.
#pragma once

#include "UMGExTypes.h"
#include "ButtonWidget.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FButtonWidgetOnPressedSignature, const FName, ButtonTag);

/**
 * 
 */
UCLASS(Blueprintable, Abstract)
class UMGEXPLUGIN_API UButtonWidget : public UUMGExWidget
{
	GENERATED_UCLASS_BODY()

	/** Broadcasts whenever a this button is pressed */
	UPROPERTY(BlueprintAssignable, Category = "Info")
	FButtonWidgetOnPressedSignature OnPressed;

	/** Should be called when something representing this widget has been triggered like a button */
	UFUNCTION(BlueprintCallable, Category = "Events")
	void TriggerOnPressed();

	/** Static method for initializing widget from a widget info struct */
	UFUNCTION(BlueprintCallable, Category = "User Interface")
	static UButtonWidget* CreateButtonWidget(APlayerController* PlayerController, TSubclassOf<UButtonWidget> ButtonClass, const FWidgetInfo& WidgetInfo);

	/** Static method for initializing widget from a widget info struct */
	static UButtonWidget* CreateButtonWidget(UWorld* World, TSubclassOf<UButtonWidget> ButtonClass, const FWidgetInfo& WidgetInfo);
	
};
