// Copyright 2014 Michael Allar. All Rights Reserved.

#pragma once

#include "Blueprint/UserWidget.h"
#include "CrosshairWidget.generated.h"

/**
 * 
 */
UCLASS()
class UMGEXPLUGIN_API UCrosshairWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:

	UCrosshairWidget(const class FObjectInitializer& PCIP);

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Spread")
	float WeaponSpread;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Spread")
	float SpreadScale;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Spread")
	float MinSpread;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Spread")
	float MaxSpread;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Spread")
	float GetTickSpreadOffset() const;
	virtual float GetTickSpreadOffset_Implementation() const;
};
