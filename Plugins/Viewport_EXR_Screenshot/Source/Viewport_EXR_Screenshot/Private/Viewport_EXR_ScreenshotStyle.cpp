// Copyright Epic Games, Inc. All Rights Reserved.

#include "Viewport_EXR_ScreenshotStyle.h"
#include "Viewport_EXR_Screenshot.h"
#include "Framework/Application/SlateApplication.h"
#include "Styling/SlateStyleRegistry.h"
#include "Slate/SlateGameResources.h"
#include "Interfaces/IPluginManager.h"
#include "Styling/SlateStyleMacros.h"

#define RootToContentDir Style->RootToContentDir

TSharedPtr<FSlateStyleSet> FViewport_EXR_ScreenshotStyle::StyleInstance = nullptr;

void FViewport_EXR_ScreenshotStyle::Initialize()
{
	if (!StyleInstance.IsValid())
	{
		StyleInstance = Create();
		FSlateStyleRegistry::RegisterSlateStyle(*StyleInstance);
	}
}

void FViewport_EXR_ScreenshotStyle::Shutdown()
{
	FSlateStyleRegistry::UnRegisterSlateStyle(*StyleInstance);
	ensure(StyleInstance.IsUnique());
	StyleInstance.Reset();
}

FName FViewport_EXR_ScreenshotStyle::GetStyleSetName()
{
	static FName StyleSetName(TEXT("Viewport_EXR_ScreenshotStyle"));
	return StyleSetName;
}


const FVector2D Icon16x16(16.0f, 16.0f);
const FVector2D Icon20x20(20.0f, 20.0f);

TSharedRef< FSlateStyleSet > FViewport_EXR_ScreenshotStyle::Create()
{
	TSharedRef< FSlateStyleSet > Style = MakeShareable(new FSlateStyleSet("Viewport_EXR_ScreenshotStyle"));
	Style->SetContentRoot(IPluginManager::Get().FindPlugin("Viewport_EXR_Screenshot")->GetBaseDir() / TEXT("Resources"));

	Style->Set("Viewport_EXR_Screenshot.PluginAction", new IMAGE_BRUSH_SVG(TEXT("ToolbarIcon"), Icon20x20));
	return Style;
}

void FViewport_EXR_ScreenshotStyle::ReloadTextures()
{
	if (FSlateApplication::IsInitialized())
	{
		FSlateApplication::Get().GetRenderer()->ReloadTextureResources();
	}
}

const ISlateStyle& FViewport_EXR_ScreenshotStyle::Get()
{
	return *StyleInstance;
}
