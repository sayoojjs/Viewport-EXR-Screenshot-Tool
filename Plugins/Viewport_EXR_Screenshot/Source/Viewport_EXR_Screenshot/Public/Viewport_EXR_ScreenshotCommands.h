// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "Framework/Commands/Commands.h"
#include "Viewport_EXR_ScreenshotStyle.h"

class FViewport_EXR_ScreenshotCommands : public TCommands<FViewport_EXR_ScreenshotCommands>
{
public:

	FViewport_EXR_ScreenshotCommands()
		: TCommands<FViewport_EXR_ScreenshotCommands>(TEXT("Viewport_EXR_Screenshot"), NSLOCTEXT("Contexts", "Viewport_EXR_Screenshot", "Viewport_EXR_Screenshot Plugin"), NAME_None, FViewport_EXR_ScreenshotStyle::GetStyleSetName())
	{
	}

	// TCommands<> interface
	virtual void RegisterCommands() override;

public:
	TSharedPtr< FUICommandInfo > PluginAction;
};
