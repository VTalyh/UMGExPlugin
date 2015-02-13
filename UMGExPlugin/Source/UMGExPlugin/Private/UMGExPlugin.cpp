// Copyright 2014 Michael Allar. All Rights Reserved.

#include "UMGExPlugin.h"


class FUMGExPlugin : public IUMGExPlugin
{
	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
};

IMPLEMENT_MODULE( FUMGExPlugin, UMGExPlugin )



void FUMGExPlugin::StartupModule()
{
	// This code will execute after your module is loaded into memory (but after global variables are initialized, of course.)
}


void FUMGExPlugin::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
}

DEFINE_LOG_CATEGORY(LogUMGEx)


