// Copyright 2014 Michael Allar. All Rights Reserved.
#pragma once

#include "UMGExTypes.generated.h"

/** Used for exposing FIntPoint */
USTRUCT(BlueprintType)
struct UMGEXPLUGIN_API FExposedIntPoint
{
	GENERATED_USTRUCT_BODY();

	FExposedIntPoint() {}
	FExposedIntPoint(const FIntPoint& InIntPoint);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Size")
	int32 X;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Size")
	int32 Y;
};

/** Used for associating display data with arbitrary data */
USTRUCT(BlueprintType)
struct UMGEXPLUGIN_API FLabelTagData
{
	GENERATED_USTRUCT_BODY();

	FLabelTagData() {}
	FLabelTagData(FText InLabel, FString InTag) {}

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "User Interface")
		FText Label;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "User Interface")
		FString Tag;
};

UENUM()
namespace EWidgetInfoType
{
	enum Type
	{
		Button,
		Slider,
		RadioScroller,
	};
}

USTRUCT(BlueprintType)
struct UMGEXPLUGIN_API FWidgetInfo
{
	GENERATED_USTRUCT_BODY()

	FWidgetInfo();
	FWidgetInfo(FText InLabel, FName InTag);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Info")
	FText Label;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Info")
	FName Tag;
};

USTRUCT(BlueprintType)
struct UMGEXPLUGIN_API FLabelButtonInfo : public FWidgetInfo
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Info")
	FText Caption;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Info")
	FName CaptionTag;
};

USTRUCT(BlueprintType)
struct UMGEXPLUGIN_API FMessageBoxInfo : public FLabelButtonInfo
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Info")
	FText ConfirmText;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Info")
	FText CancelText;
};

USTRUCT(BlueprintType)
struct UMGEXPLUGIN_API FFullPanelWidgetInfo : public FWidgetInfo
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Info")
	TSubclassOf<class UFullPanelWidget> PanelClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Info")
	ESlateVisibility VisibilityOnOpen;

	FFullPanelWidgetInfo() : VisibilityOnOpen(ESlateVisibility::SelfHitTestInvisible) { }
};

USTRUCT(BlueprintType)
struct UMGEXPLUGIN_API FSliderInfo : public FWidgetInfo
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Info")
	bool bTreatValueAsInt;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Info")
	bool bTriggerChangeEventOnCreate;

	UPROPERTY(EditDefaultsOnly, Category = "Info")
	float MinValue;

	UPROPERTY(EditDefaultsOnly, Category = "Info")
	float MaxValue;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Info", Meta = (UIMin = 0, UIMax = 1, ClampMin = 0, ClampMax = 1))
	float NormalizedValue;
};

USTRUCT(BlueprintType)
struct UMGEXPLUGIN_API FRadioScrollerInfo : public FWidgetInfo
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Info")
	TArray<FWidgetInfo> Choices;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Info")
	bool bTriggerChangeEventOnCreate;
};

//@TODO: This is so bad, but best way I can figure having this functionality so far
USTRUCT(BlueprintType)
struct UMGEXPLUGIN_API FWidgetInfoFactory
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Info")
	bool bButton;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Info")
	bool bLabelButton;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Info")
	bool bSlider;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Info")
	bool bRadioScroller;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (EditCondition = "bButton"), Category = "Info")
	FWidgetInfo ButtonInfo;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (EditCondition = "bLabelButton"), Category = "Info")
	FLabelButtonInfo LabelButtonInfo;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (EditCondition = "bSlider"), Category = "Info")
	FSliderInfo SliderInfo;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (EditCondition = "bRadioScroller"), Category = "Info")
	FRadioScrollerInfo RadioScrollerInfo;

	FWidgetInfoFactory() : bButton(false), bLabelButton(false), bSlider(false), bRadioScroller(false) { }
};