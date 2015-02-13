// Copyright 2014 Michael Allar. All Rights Reserved.

#include "UMGExPlugin.h"

UUMGExWidget::UUMGExWidget(const class FObjectInitializer& PCIP)
	: Super(PCIP)
{
	/*
	** @TODO: We are heavily relying on UMG Editor to create a CanvasPanel for root when a blueprint
	** class of URadioScrollerWidget is made. When Epic creates more non-bp user widget logic, we should revisit this
	*/
}
