//Copyright(c) 2015 Michael Allar
#pragma once

#include "UMGExTypes.h"
#include "TextBlockWrapper.generated.h"

/**
*
*/
UCLASS()
class UMGEXPLUGIN_API UTextBlockWrapper : public UUMGExWidget
{
	GENERATED_UCLASS_BODY()

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Widgets")
	UTextBlock* GetTextBlock();

};