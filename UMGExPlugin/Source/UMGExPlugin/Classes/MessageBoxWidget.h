//Copyright(c) 2015 Michael Allar
#pragma once

#include "UMGExTypes.h"
#include "UMGExWidget.h"
#include "MessageBoxWidget.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FMessageBoxWidgetOnButtonPressedSignature, const FName, MessageBoxTag, const FName, ButtonTag);

/**
 * 
 */
UCLASS(Blueprintable, Abstract)
class UMGEXPLUGIN_API UMessageBoxWidget : public UUMGExWidget
{
	GENERATED_BODY()

public:

	/** Message to be shown in the body of this message box */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Info")
	FText Caption;

	/** Label for the confirm button i.e. "OK" */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Info")
	FText ConfirmText;

	/** Label for the confirm button i.e. "OK" */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Info")
	FText CancelText;

	/** Broadcasts whenever this message box is confirmed and closed */
	UPROPERTY(BlueprintAssignable)
	FMessageBoxWidgetOnButtonPressedSignature OnButtonPressed;

	/** Should be called when the confirm button if this message box is pressed */
	UFUNCTION(BlueprintCallable, Category = "Events")
	void TriggerOnButtonPressed(const FName ButtonTag);

	/** Should be called when the confirm button if this message box is pressed */
	UFUNCTION(BlueprintCallable, Category = "Events")
	virtual void CloseBox();

	/** This should be set if you want the game to change states after the dialog button is closed i.e. an error message */
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category = "State")
	FName StateAfterConfirm;

	/** Static method for initializing widget from a widget info struct */
	UFUNCTION(BlueprintCallable, Category = "Widgets")
	static UMessageBoxWidget* ShowMessageBoxWidget(APlayerController* PlayerController, TSubclassOf<UMessageBoxWidget> MessageBoxClass, const FMessageBoxInfo& WidgetInfo);
};
