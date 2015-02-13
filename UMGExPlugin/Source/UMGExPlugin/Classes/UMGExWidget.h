//Copyright(c) 2015 Michael Allar
#pragma once

#include "UMGExTypes.h"
#include "UMGExWidget.generated.h"

/**
*
*/
UCLASS()
class UMGEXPLUGIN_API UUMGExWidget : public UUserWidget
{
	GENERATED_UCLASS_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (AlwaysAsPin), Category = "Info")
	FText Label;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (AlwaysAsPin), Category = "Info")
	FName Tag;

};