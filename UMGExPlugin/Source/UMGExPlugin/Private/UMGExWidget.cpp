//Copyright(c) 2015 Michael Allar

#include "UMGExPlugin.h"

UUMGExWidget::UUMGExWidget(const class FObjectInitializer& PCIP)
	: Super(PCIP)
{
	/*
	** @TODO: We are heavily relying on UMG Editor to create a CanvasPanel for root when a blueprint
	** class of URadioScrollerWidget is made. When Epic creates more non-bp user widget logic, we should revisit this
	*/
}
