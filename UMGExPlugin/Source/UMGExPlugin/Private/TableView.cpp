//Copyright(c) 2015 Michael Allar
#include "UMGExPlugin.h"

TSharedRef<SWidget> UTableView::RebuildWidget()
{
	// Root widget is assumed to be CanvasPanel. See @TODO in Constructor
	TSharedRef<SWidget> RootSlateWidget = Super::RebuildWidget();

	if (!IsDesignTime())
	{
		if (ColumnRatios.Num() != HeaderRowItems.Num())
		{
			UE_LOG(LogUMGEx, Error, TEXT("UTableView HeaderRowItems needs to be the same size as Column Ratios"));
			return RootSlateWidget;
		}

		UHorizontalBox* HeaderHorizontalBox = HeaderRowDelegate();
		if (HeaderHorizontalBox == nullptr)
		{
			UE_LOG(LogUMGEx, Error, TEXT("UTableView ScrollBoxDelegate needs to return a horizontal box"));
			return RootSlateWidget;
		}

		UScrollBox* ScrollBox = ScrollBoxDelegate();
		if (ScrollBox == nullptr)
		{
			UE_LOG(LogUMGEx, Error, TEXT("UTableView ScrollBoxDelegate needs to return a scroll box"));
			return RootSlateWidget;
		}

		for (int i = 0; i < HeaderRowItems.Num(); ++i)
		{
			UButtonWidget* HeaderRowButton = CreateWidget<UButtonWidget>(GetOwningPlayer(), HeaderRowButtonClass);
			if (HeaderRowButton != nullptr)
			{
				HeaderRowButton->Label = HeaderRowItems[i].Label;
				HeaderRowButton->Tag = HeaderRowItems[i].Tag;

				// @TODO: Look into how a newly created widget could already have OnPressed bound
				if (!HeaderRowButton->OnPressed.IsAlreadyBound(this, &UTableView::OnHeaderRowButtonPressed_Internal))
				{
					HeaderRowButton->OnPressed.AddDynamic(this, &UTableView::OnHeaderRowButtonPressed_Internal);
				}

				FSlateChildSize childSize;
				childSize.SizeRule = ESlateSizeRule::Fill;
				childSize.Value = ColumnRatios[i];

				UHorizontalBoxSlot* HorizontalBoxSlot = HeaderHorizontalBox->AddChildToHorizontalBox(HeaderRowButton);
				if (HorizontalBoxSlot != nullptr)
				{
					HorizontalBoxSlot->SetSize(childSize);
				}
				else
				{
					UE_LOG(LogUMGEx, Error, TEXT("UTableView Unable to add a horizontal box and get a horizontal box slot. This should never happen."));
					return RootSlateWidget;
				}
			}
			else
			{
				UE_LOG(LogUMGEx, Error, TEXT("UTableView Unable to create header row buttons. Bad HeaderRowButtonClass?"));
				return RootSlateWidget;
			}			
		}
	}

	return RootSlateWidget;
}

void UTableView::OnHeaderRowButtonPressed_Internal_Implementation(const FName ButtonTag)
{
	if (OnHeaderRowButtonPressed.IsBound())
	{
		OnHeaderRowButtonPressed.Broadcast(ButtonTag);
	}
}

void UTableView::AddTableItem(const FWidgetInfo& TagInfo, const TArray<FWidgetInfo>& ItemData)
{
	UScrollBox* ScrollBox = ScrollBoxDelegate();
	if (ScrollBox == nullptr)
	{
		UE_LOG(LogUMGEx, Error, TEXT("UTableView ScrollBoxDelegate needs to return a scroll box"));
		return;
	}

	int childrenCount = ScrollBox->GetChildrenCount();
	UE_LOG(LogUMGEx, VeryVerbose, TEXT("TableView adding Table Item to Scroll box that has %d children"), childrenCount);

	TSubclassOf<UTableListRow> RowClass = RowClasses[childrenCount % RowClasses.Num()];

	UTableListRow* Row = UTableListRow::CreateTableListRowWidget(GetOwningPlayer(), RowClass, TagInfo, ItemData, ColumnRatios);

	if (Row != nullptr)
	{
		if (!Row->OnRowSelected.IsAlreadyBound(this, &UTableView::OnRowSelected_Internal))
		{
			Row->OnRowSelected.AddDynamic(this, &UTableView::OnRowSelected_Internal);
		}
		UScrollBoxSlot* ScrollSlot = Cast<UScrollBoxSlot>(ScrollBox->AddChild(Row));
		if (ScrollSlot != nullptr)
		{
		}
		else
		{
			UE_LOG(LogUMGEx, Error, TEXT("TableView unable to add child row %d and get a ScrollBoxSlot back. This should never happen."), childrenCount+1);
		}
	}
	else
	{
		UE_LOG(LogUMGEx, Error, TEXT("TableView failed to create Table List Row Widget."));
	}
}

void UTableView::ClearTableList()
{
	UScrollBox* ScrollBox = ScrollBoxDelegate();
	if (ScrollBox == nullptr)
	{
		UE_LOG(LogUMGEx, Error, TEXT("UTableView ScrollBoxDelegate needs to return a scroll box"));
		return;
	}

	ScrollBox->ClearChildren();
}

void UTableView::OnRowSelected_Internal_Implementation(class UTableListRow* TableListRow)
{
	OnRowSelected.Broadcast(TableListRow);
}

void UTableView::SetTableItemInfo(int32 TableItemRow, const FWidgetInfo& TagInfo, const TArray<FWidgetInfo>& ItemData)
{
	UScrollBox* ScrollBox = ScrollBoxDelegate();
	if (ScrollBox != nullptr)
	{
		if (TableItemRow < ScrollBox->GetChildrenCount())
		{
			UTableListRow* Row = Cast<UTableListRow>(ScrollBox->GetChildAt(TableItemRow));
			if (Row != nullptr)
			{
				UHorizontalBox* HorzBox = Row->GetRowContainer();
				if (HorzBox != nullptr)
				{
					if (HorzBox->GetChildrenCount() == ItemData.Num())
					{
						for (int i = 0; i < ItemData.Num(); ++i)
						{
							UTextBlockWrapper* TextWrapper = Cast<UTextBlockWrapper>(HorzBox->GetChildAt(i));
							if (TextWrapper != nullptr)
							{
								TextWrapper->Tag = ItemData[i].Tag;
								if (TextWrapper->GetTextBlock() != nullptr)
								{
									TextWrapper->GetTextBlock()->SetText(ItemData[i].Label);
								}
								else
								{
									UE_LOG(LogUMGEx, Warning, TEXT("TableView::SetTableItemInfo called but table row has a TextBlockWrapper that could not get a text block."));
								}
								
							}
							else
							{
								UE_LOG(LogUMGEx, Warning, TEXT("TableView::SetTableItemInfo called but table row has non TextBlockWrapper child."));
							}
						}
					}
					else
					{
						UE_LOG(LogUMGEx, Warning, TEXT("TableView::SetTableItemInfo called but passed ItemData does not match this row's existing children."));
					}
				}
				else
				{
					UE_LOG(LogUMGEx, Warning, TEXT("TableView::SetTableItemInfo called but table row does not have a row container."));
				}
			}
			else
			{
				UE_LOG(LogUMGEx, Warning, TEXT("TableView::SetTableItemInfo called but table row was not found."));
			}
		}
	}
}

