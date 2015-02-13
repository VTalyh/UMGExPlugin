//Copyright(c) 2015 Michael Allar
#pragma once

#include "UMGExTypes.h"
#include "LabelButtonWidget.generated.h"

/**
 * 
 */
UCLASS(Blueprintable, Abstract)
class UMGEXPLUGIN_API ULabelButtonWidget : public UButtonWidget
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Info")
	FText Caption;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Info")
	FName CaptionTag;

	/** Static method for initializing widget from a widget info struct */
	UFUNCTION(BlueprintCallable, Category = "User Interface")
	static ULabelButtonWidget* CreateLabelButtonWidget(APlayerController* PlayerController, TSubclassOf<ULabelButtonWidget> ButtonClass, const FLabelButtonInfo& WidgetInfo);
	
};
