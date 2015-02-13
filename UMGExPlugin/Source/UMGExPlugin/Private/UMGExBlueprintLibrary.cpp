//Copyright(c) 2015 Michael Allar

#include "UMGExPlugin.h"
#include "InputCoreClasses.h"

UUMGExBlueprintLibrary::UUMGExBlueprintLibrary(const FObjectInitializer& PCIP)
	: Super(PCIP)
{
}

bool UUMGExBlueprintLibrary::PromptLoginIfNeeded(const int32 UserIndex, const UTitleScreenWidget* TitleWidgetToBindDelegateTo)
{
	bool bLoggedIn = true;

	const auto OnlineSub = IOnlineSubsystem::Get();
	if (OnlineSub)
	{
		const auto IdentityInterface = OnlineSub->GetIdentityInterface();
		if (IdentityInterface.IsValid())
		{
			const auto LoginStatus = IdentityInterface->GetLoginStatus(UserIndex);
			if (LoginStatus == ELoginStatus::NotLoggedIn || !UUMGExBlueprintLibrary::IsApplicationLicenseValid())
			{
				// Show the account picker.
				const auto ExternalUI = OnlineSub->GetExternalUIInterface();
				if (ExternalUI.IsValid())
				{
					//ExternalUI->ShowLoginUI(UserIndex, false, IOnlineExternalUI::FOnLoginUIClosedDelegate::CreateUObject(TitleWidgetToBindDelegateTo, &UTitleScreenWidget::HandleLoginUIClosed));
					bLoggedIn = false;
				}
			}
		}
	}

	return bLoggedIn;
}

bool UUMGExBlueprintLibrary::IsApplicationLicenseValid()
{
	TSharedPtr<GenericApplication> GenericApplication = FSlateApplication::Get().GetPlatformApplication();
	return GenericApplication->ApplicationLicenseValid();
}

FExposedIntPoint UUMGExBlueprintLibrary::ExposeIntPoint(const FIntPoint& InIntPoint)
{
	return FExposedIntPoint(InIntPoint);
}

FIntPoint UUMGExBlueprintLibrary::MakeIntPoint(const FExposedIntPoint& InExposedIntPoint)
{
	return FIntPoint(InExposedIntPoint.X, InExposedIntPoint.Y);
}

class UInputSettings* UUMGExBlueprintLibrary::GetDefaultInputSettings()
{
	return GetMutableDefault<UInputSettings>();
}

TArray<FLabelButtonInfo> UUMGExBlueprintLibrary::GetAllInputMappingLabelButtonInfos(const TArray<FName>& ExclusionList)
{
	const UInputSettings* InputSettings = GetDefault<UInputSettings>();

	TArray<FLabelButtonInfo> Infos;

	for (FInputActionKeyMapping Mapping : InputSettings->ActionMappings)
	{
		if (ExclusionList.Contains(Mapping.ActionName))
		{
			continue;
		}

		FLabelButtonInfo Info;
		Info.Label = FText::FromName(Mapping.ActionName);
		Info.Tag = Mapping.ActionName;
		Info.Caption = Mapping.Key.GetDisplayName();
		Infos.Add(Info);
	}

	for (FInputAxisKeyMapping Mapping : InputSettings->AxisMappings)
	{
		if (ExclusionList.Contains(Mapping.AxisName))
		{
			continue;
		}

		FLabelButtonInfo Info;
		Info.Label = FText::FromName(Mapping.AxisName);
		Info.Tag = Mapping.AxisName;
		Info.Caption = Mapping.Key.GetDisplayName();
		Infos.Add(Info);
	}

	return Infos;
}

FLabelButtonInfo UUMGExBlueprintLibrary::GetInputMappingLabelButtonInfo(const FName& MappingName)
{
	const UInputSettings* InputSettings = GetDefault<UInputSettings>();

	FLabelButtonInfo Info;

	const FInputActionKeyMapping* ActionKeyMapping = InputSettings->ActionMappings.FindByPredicate([MappingName](const FInputActionKeyMapping& Mapping) -> bool
	{
		return Mapping.ActionName == MappingName;
	});

	if (ActionKeyMapping)
	{
		Info.Label = FText::FromName(ActionKeyMapping->ActionName);
		Info.Tag = ActionKeyMapping->ActionName;
		Info.Caption = ActionKeyMapping->Key.GetDisplayName();
		return Info;
	}

	const FInputAxisKeyMapping* AxisKeyMapping = InputSettings->AxisMappings.FindByPredicate([MappingName](const FInputAxisKeyMapping& Mapping) -> bool
	{
		return Mapping.AxisName == MappingName;
	});

	if (AxisKeyMapping)
	{
		Info.Label = FText::FromName(AxisKeyMapping->AxisName);
		Info.Tag = AxisKeyMapping->AxisName;
		Info.Caption = AxisKeyMapping->Key.GetDisplayName();
		return Info;
	}

	return Info;
}

bool UUMGExBlueprintLibrary::SetInputMappingKeyBind(const FName& MappingName, FKey NewKey)
{
	UInputSettings* InputSettings = GetMutableDefault<UInputSettings>();

	FInputActionKeyMapping* ActionKeyMapping = InputSettings->ActionMappings.FindByPredicate([MappingName](FInputActionKeyMapping& Mapping) -> bool
	{
		return Mapping.ActionName == MappingName;
	});

	if (ActionKeyMapping != nullptr)
	{
		ActionKeyMapping->Key = NewKey;
		InputSettings->SaveKeyMappings();
		return true;
	}

	FInputAxisKeyMapping* AxisKeyMapping = InputSettings->AxisMappings.FindByPredicate([MappingName](FInputAxisKeyMapping& Mapping) -> bool
	{
		return Mapping.AxisName == MappingName;
	});

	if (AxisKeyMapping != nullptr)
	{
		AxisKeyMapping->Key = NewKey;
		InputSettings->SaveKeyMappings();
		return true;
	}

	return false;
}
