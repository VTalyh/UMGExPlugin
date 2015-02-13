// Copyright 2014 Michael Allar. All Rights Reserved.
#pragma once

#include "UMGExTypes.h"
#include "TableListRow.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnTableListRowSelectedSignature, class UTableListRow*, TableListRow);

/**
*
*/
UCLASS(Blueprintable, Abstract)
class UMGEXPLUGIN_API UTableListRow : public UUMGExWidget
{
	GENERATED_UCLASS_BODY()

	FOnTableListRowSelectedSignature OnRowSelected;

	UFUNCTION(BlueprintCallable, Category = "Events")
	void TriggerOnSelected();

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Layout")
	TSubclassOf<class UTextBlockWrapper> TextBlockWrapperClass;

	UFUNCTION(BlueprintImplementableEvent, Category = "Layout")
	UHorizontalBox* GetRowContainer();

	/** Static method for initializing widget from a widget info struct */
	UFUNCTION(BlueprintCallable, Category = "Widgets")
	static UTableListRow* CreateTableListRowWidget(APlayerController* PlayerController, TSubclassOf<UTableListRow> RowClass, const FWidgetInfo& TagInfo, TArray<FWidgetInfo> ListData, const TArray<float>& InColumnRatios );

protected:
	void BuildRow();

protected:
	TArray<FWidgetInfo> DataList;
	TArray<float> ColumnRatios;

};
