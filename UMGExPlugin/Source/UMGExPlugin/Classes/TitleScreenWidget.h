// Copyright 2014 Michael Allar. All Rights Reserved.
#pragma once

#include "OnlineIdentityInterface.h"
#include "TitleScreenWidget.generated.h"

/**
*
*/
UCLASS()
class UMGEXPLUGIN_API UTitleScreenWidget : public UUserWidget
{
	GENERATED_UCLASS_BODY()

	friend class UUMGExBlueprintLibrary;

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Online|Identity")
	void DisplayApplicationIsNotLicensed();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Online|Identity")
	void DisplayUserNotLoggedIn();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Online|Identity")
	void DisplayUserNotOldEnough();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "User Interface")
	void AdvanceToMainMenu();

protected:
	virtual TSharedRef<SWidget> RebuildWidget() override;

	/**
	* The delegate function for external login UI closure when a user has signed in.
	*
	* @param UniqueId The unique Id of the user who just signed in.
	* @param ControllerIndex The controller index of the player who just signed in.
	*/
	void HandleLoginUIClosed(TSharedPtr<FUniqueNetId> UniqueId, const int ControllerIndex);

	/** Handler for querying a user's privileges */
	void OnUserCanPlay(const FUniqueNetId & UserId, EUserPrivileges::Type Privilege, uint32 PrivilegeResults);

	void SetControllerAndAdvanceToMainMenu(const int ControllerIndex);

	/** Cache the user id that tried to advance, so we can use it again after the confirmation dialog */
	int PendingControllerIndex;
};