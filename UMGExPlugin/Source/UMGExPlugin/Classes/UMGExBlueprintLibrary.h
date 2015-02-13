//Copyright(c) 2015 Michael Allar

#pragma once
#include "UMGExTypes.h"
#include "UMGExBlueprintLibrary.Generated.h"

// Library of helper functions for UMGEx Widgets
UCLASS()
class UMGEXPLUGIN_API UUMGExBlueprintLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_UCLASS_BODY()

	UFUNCTION(BlueprintCallable, Category = "Online")
	static bool IsApplicationLicenseValid();

	UFUNCTION(BlueprintCallable, Category = "Online")
	static bool PromptLoginIfNeeded(const int32 UserIndex, const UTitleScreenWidget* TitleWidgetToBindDelegateTo);

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Utility")
	static FExposedIntPoint ExposeIntPoint(const FIntPoint& InIntPoint);

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Utility")
	static FIntPoint MakeIntPoint(const FExposedIntPoint& InExposedIntPoint);

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Input")
	static class UInputSettings* GetDefaultInputSettings();

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Input")
	static TArray<FLabelButtonInfo> GetAllInputMappingLabelButtonInfos(const TArray<FName>& ExclusionList);

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Input")
	static FLabelButtonInfo GetInputMappingLabelButtonInfo(const FName& MappingName);

	UFUNCTION(BlueprintCallable, Category = "Input")
	static bool SetInputMappingKeyBind(const FName& MappingName, FKey NewKey);

};
