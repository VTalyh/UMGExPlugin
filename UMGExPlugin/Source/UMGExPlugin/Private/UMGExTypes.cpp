//Copyright(c) 2015 Michael Allar
#include "UMGExPlugin.h"

FExposedIntPoint::FExposedIntPoint(const FIntPoint& InIntPoint)
{
	X = InIntPoint.X;
	Y = InIntPoint.Y;
}

FWidgetInfo::FWidgetInfo()
{

}

FWidgetInfo::FWidgetInfo(FText InLabel, FName InTag)
{
	Label = InLabel;
	Tag = InTag;
}