//Copyright(c) 2015 Michael Allar

#include "UMGExPlugin.h"

UTitleScreenWidget::UTitleScreenWidget(const class FObjectInitializer& PCIP)
	: Super(PCIP)
{
	/*
	** @TODO: We are heavily relying on UMG Editor to create a CanvasPanel for root when a blueprint
	** class of URadioScrollerWidget is made. When Epic creates more non-bp user widget logic, we should revisit this
	*/
}

TSharedRef<SWidget> UTitleScreenWidget::RebuildWidget()
{
	// Root widget is assumed to be CanvasPanel. See @TODO in Constructor
	TSharedRef<SWidget> RootSlateWidget = Super::RebuildWidget();

	if (!IsDesignTime())
	{

	}

	return RootSlateWidget;
}

void UTitleScreenWidget::HandleLoginUIClosed(TSharedPtr<FUniqueNetId> UniqueId, const int ControllerIndex)
{
	// If they don't currently have a license, let them know, but don't let them proceed
	if (!UUMGExBlueprintLibrary::IsApplicationLicenseValid())
	{
		DisplayApplicationIsNotLicensed();
		return;
	}
	PendingControllerIndex = ControllerIndex;

	if (UniqueId.IsValid())
	{
		// Next step, check privileges
		const auto OnlineSub = IOnlineSubsystem::Get();
		if (OnlineSub)
		{
			const auto IdentityInterface = OnlineSub->GetIdentityInterface();
			if (IdentityInterface.IsValid())
			{
				IdentityInterface->GetUserPrivilege(*UniqueId, EUserPrivileges::CanPlay, IOnlineIdentity::FOnGetUserPrivilegeCompleteDelegate::CreateUObject(this, &UTitleScreenWidget::OnUserCanPlay));
			}
		}
	}
	else
	{
		DisplayUserNotLoggedIn();
	}
}

void UTitleScreenWidget::OnUserCanPlay(const FUniqueNetId & UserId, EUserPrivileges::Type Privilege, uint32 PrivilegeResults)
{
	if (PrivilegeResults == (uint32)IOnlineIdentity::EPrivilegeResults::NoFailures)
	{
		SetControllerAndAdvanceToMainMenu(PendingControllerIndex);
	}
	else
	{
		DisplayUserNotOldEnough();
	}
}

void UTitleScreenWidget::SetControllerAndAdvanceToMainMenu(const int ControllerIndex)
{
	ULocalPlayer * NewPlayerOwner = GetWorld()->GetGameInstance()->GetFirstGamePlayer();

	if (NewPlayerOwner != nullptr && ControllerIndex != -1)
	{
		NewPlayerOwner->SetControllerId(ControllerIndex);
		NewPlayerOwner->SetCachedUniqueNetId(NewPlayerOwner->GetUniqueNetIdFromCachedControllerId());
		AdvanceToMainMenu();
	}
}
