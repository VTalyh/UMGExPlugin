// Copyright 2014 Michael Allar. All Rights Reserved.
#include "UMGExPlugin.h"


UTableListRow::UTableListRow(const class FObjectInitializer& PCIP)
	: Super(PCIP)
{
}

void UTableListRow::TriggerOnSelected()
{
	if (!IsDesignTime())
	{
		OnRowSelected.Broadcast(this);
	}
}

UTableListRow* UTableListRow::CreateTableListRowWidget(APlayerController* PlayerController, TSubclassOf<UTableListRow> RowClass, const FWidgetInfo& TagInfo, TArray<FWidgetInfo> ListData, const TArray<float>& InColumnRatios)
{
	if (PlayerController == nullptr)
	{
		UE_LOG(LogUMGEx, Error, TEXT("UTableListRow::CreateTableListRow called with null PlayerController!"));
		return nullptr;
	}
	
	if (RowClass == nullptr)
	{
		UE_LOG(LogUMGEx, Error, TEXT("UTableListRow::CreateTableListRow called with null RowClass!"));
		return nullptr;
	}

	if (InColumnRatios.Num() == ListData.Num())
	{
		UTableListRow* NewRow = CreateWidget<UTableListRow>(PlayerController, RowClass);
		NewRow->Label = TagInfo.Label;
		NewRow->Tag = TagInfo.Tag;
		NewRow->DataList = ListData;
		NewRow->ColumnRatios = InColumnRatios;
		NewRow->BuildRow();
		return NewRow;
	}
	else
	{
		UE_LOG(LogUMGEx, Error, TEXT("UTableListRow::CreateTableListRow called with InDataList length not equal to ColumnRatios length!"));
	}


	return nullptr;
	
}

void UTableListRow::BuildRow()
{
	UHorizontalBox* HorizontalBox = GetRowContainer();
	if (HorizontalBox != nullptr)
	{
		// DataList and ColumnRatios are assumed and guaranteed to be in sync
		for (int i = 0; i < DataList.Num(); ++i)
		{
			UTextBlockWrapper* cellText = CreateWidget<UTextBlockWrapper>(GetOwningPlayer(), TextBlockWrapperClass);
			if (cellText != nullptr)
			{
				cellText->Label = DataList[i].Label;
				cellText->Tag = DataList[i].Tag;

				FSlateChildSize childSize;
				childSize.SizeRule = ESlateSizeRule::Fill;
				childSize.Value = ColumnRatios[i];
				
				cellText->SetVisibility(ESlateVisibility::HitTestInvisible);
				UHorizontalBoxSlot* HorizontalSlot = HorizontalBox->AddChildToHorizontalBox(cellText);
				HorizontalSlot->SetSize(childSize);

				UTextBlock* textBlock = cellText->GetTextBlock();
				if (textBlock != nullptr)
				{
					//textBlock->SetText(DataList[i].Label);
				}
				else
				{
					UE_LOG(LogUMGEx, Error, TEXT("UTableListRow::BuildRow unable to get text block from child widget. GetTextBlock not assigned?"));
				}

				UE_LOG(LogUMGEx, VeryVerbose, TEXT("UTableListRow::BuildRow created text block with text %s with size %f"), *DataList[i].Label.ToString(), ColumnRatios[i]);
			}
			else
			{
				UE_LOG(LogUMGEx, Error, TEXT("UTableListRow::BuildRow unable to create a text block. Bad Text Block Wrapper Class?"));
			}
		}
	}
	else
	{
		UE_LOG(LogUMGEx, Error, TEXT("UTableListRow::BuildRow was called with GetRowContainer unbound. Make sure all user defined TableListRow widgets have GetRowContainer bound to get a Horizontal Box widget."));
	}

	UCanvasPanelSlot* CanvasSlot = Cast<UCanvasPanelSlot>(HorizontalBox->GetParent()->GetParent()->Slot);
	if (CanvasSlot != nullptr)
	{
		//CanvasSlot->RebaseLayout();
	}
}