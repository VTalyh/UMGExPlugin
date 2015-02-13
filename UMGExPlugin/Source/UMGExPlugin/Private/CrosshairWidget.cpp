// Copyright 2014 Michael Allar. All Rights Reserved.

#include "UMGExPlugin.h"
#include "CrosshairWidget.h"

UCrosshairWidget::UCrosshairWidget(const class FObjectInitializer& PCIP) : Super(PCIP)
{
	WeaponSpread = 5.0f;
	SpreadScale = 2.0f;
	MaxSpread = 256.0f;
	MinSpread = 0.0f;
}

float UCrosshairWidget::GetTickSpreadOffset_Implementation() const
{
	return FMath::Clamp(WeaponSpread * SpreadScale, MinSpread, MaxSpread);
}


