// Copyright Epic Games, Inc. All Rights Reserved.

#include "Viewport_EXR_ScreenshotCommands.h"

#define LOCTEXT_NAMESPACE "FViewport_EXR_ScreenshotModule"

void FViewport_EXR_ScreenshotCommands::RegisterCommands()
{
	UI_COMMAND(PluginAction, "Viewport_EXR_Screenshot", "Take High Dynamic Range EXR Screenshots", EUserInterfaceActionType::Button, FInputChord());
}

#undef LOCTEXT_NAMESPACE
