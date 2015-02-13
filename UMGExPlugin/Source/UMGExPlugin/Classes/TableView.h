// Copyright 2014 Michael Allar. All Rights Reserved.
#pragma once

#include "UMGExTypes.h"
#include "TableView.generated.h"

USTRUCT(BlueprintType)
struct FTableSortInfo
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(BlueprintReadWrite, Category = "Sorting")
	FName SortColumn;

	UPROPERTY(BlueprintReadWrite, Category = "Sorting")
	bool bSortAscending;
};

UCLASS()
class UMGEXPLUGIN_API UTableView : public UUMGExWidget
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintImplementableEvent, Category = "Layout")
	UHorizontalBox* HeaderRowDelegate();
	
	UFUNCTION(BlueprintImplementableEvent, Category = "Layout")
	UScrollBox* ScrollBoxDelegate();

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Layout")
	TSubclassOf<UButtonWidget> HeaderRowButtonClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Layout")
	TArray<TSubclassOf<UTableListRow>> RowClasses;

	/** Internal event called when a header row button is pressed. This should trigger OnHeaderRowButtonPressed */
	UFUNCTION(BlueprintNativeEvent)
	void OnHeaderRowButtonPressed_Internal(const FName ButtonTag);
	virtual void OnHeaderRowButtonPressed_Internal_Implementation(const FName ButtonTag);

	UPROPERTY(BlueprintAssignable, Category = "Events")
	FButtonWidgetOnPressedSignature OnHeaderRowButtonPressed;

	UPROPERTY(EditDefaultsOnly, Category = "Info")
	TArray<FWidgetInfo> HeaderRowItems;

	UPROPERTY(BlueprintAssignable, Category = "Events")
	FOnTableListRowSelectedSignature OnRowSelected;

	UFUNCTION(BlueprintNativeEvent)
	void OnRowSelected_Internal(class UTableListRow* TableListRow);
	virtual void OnRowSelected_Internal_Implementation(class UTableListRow* TableListRow);

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Layout")
	TArray<float> ColumnRatios;

	UFUNCTION(BlueprintCallable, Category = "Widgets")
	void AddTableItem(const FWidgetInfo& TagInfo, const TArray<FWidgetInfo>& ItemData);

	UFUNCTION(BlueprintCallable, Category = "Widgets")
	void SetTableItemInfo(int32 TableItemRow, const FWidgetInfo& TagInfo, const TArray<FWidgetInfo>& ItemData);

	UFUNCTION(BlueprintCallable, Category = "Widgets")
	void ClearTableList();

protected:
	virtual TSharedRef<SWidget> RebuildWidget() override;
};
