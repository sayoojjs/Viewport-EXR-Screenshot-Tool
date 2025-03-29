// Copyright Epic Games, Inc. All Rights Reserved.

#include "Viewport_EXR_Screenshot.h"
#include "Viewport_EXR_ScreenshotStyle.h"
#include "Viewport_EXR_ScreenshotCommands.h"
#include "Misc/MessageDialog.h"
#include "ToolMenus.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/DirectionalLight.h"
#include "Components/LightComponent.h"
#include "Engine/GameViewportClient.h"
#include "HighResScreenshot.h"
#include "UnrealClient.h"
#include "Engine/Engine.h"
#include "Engine.h"
#include "EngineMinimal.h"
#include "Engine/World.h"
#include "Misc/Paths.h"
#include "HAL/IConsoleManager.h"
#include "HAL/PlatformFileManager.h"
#include "IImageWrapper.h"
#include "IImageWrapperModule.h"
#include "CoreMinimal.h"
#include "Engine.h"
#include "GameFramework/Actor.h"

static const FName Viewport_EXR_ScreenshotTabName("Viewport_EXR_Screenshot");

#define LOCTEXT_NAMESPACE "FViewport_EXR_ScreenshotModule"

void FViewport_EXR_ScreenshotModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
	
	FViewport_EXR_ScreenshotStyle::Initialize();
	FViewport_EXR_ScreenshotStyle::ReloadTextures();

	FViewport_EXR_ScreenshotCommands::Register();
	
	PluginCommands = MakeShareable(new FUICommandList);

	PluginCommands->MapAction(
		FViewport_EXR_ScreenshotCommands::Get().PluginAction,
		FExecuteAction::CreateRaw(this, &FViewport_EXR_ScreenshotModule::PluginButtonClicked),
		FCanExecuteAction());

	UToolMenus::RegisterStartupCallback(FSimpleMulticastDelegate::FDelegate::CreateRaw(this, &FViewport_EXR_ScreenshotModule::RegisterMenus));
}

void FViewport_EXR_ScreenshotModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.

	UToolMenus::UnRegisterStartupCallback(this);

	UToolMenus::UnregisterOwner(this);

	FViewport_EXR_ScreenshotStyle::Shutdown();

	FViewport_EXR_ScreenshotCommands::Unregister();
}

void FViewport_EXR_ScreenshotModule::PluginButtonClicked()
{


	//Random Integer Generation
	int32 RandomNumber = FMath::RandRange(1, 100);

	//File Path
	FString ScreenshotName = FPaths::ProjectSavedDir() + "Screenshots/HDRScreenshot_"+FString::FromInt(RandomNumber)+".exr";

	//EXR Settings 
	FHighResScreenshotConfig& HighResScreenshotConfig = GetHighResScreenshotConfig();

	// Set the format to EXR
	HighResScreenshotConfig.SetHDRCapture(true);
	HighResScreenshotConfig.bCaptureHDR = true; // Important for EXR
	HighResScreenshotConfig.bForce128BitRendering = true;
	HighResScreenshotConfig.bDumpBufferVisualizationTargets;
	FScreenshotRequest::RequestScreenshot(ScreenshotName, false, false);

	//Log Execution
	UE_LOG(LogTemp, Warning, TEXT("Saved %s"), *ScreenshotName);

	// Put your "OnButtonClicked" stuff here
	FText DialogText = FText::Format(
		LOCTEXT("PluginButtonDialogText", "Screenshot 'HDRScreenshot_" + FString::FromInt(RandomNumber) +"'" " saved!"),
		FText::FromString(TEXT("Viewport_EXR_Screenshot.cpp"))
	);
	FMessageDialog::Open(EAppMsgType::Ok, DialogText);



}

//EXR Console Command Executor

/*void FViewport_EXR_ScreenshotModule::PyExecutor()
{
 FString Command = TEXT("Py");
 FString PythonPath = FPaths::ProjectPluginsDir() + "Viewport_EXR_Screenshot/EXRModule/";
 FString Execution = Command + PythonPath + Filename;
 GEngine->Exec(nullptr, *Execution);
}*/



void FViewport_EXR_ScreenshotModule::RegisterMenus()
{
	// Owner will be used for cleanup in call to UToolMenus::UnregisterOwner
	FToolMenuOwnerScoped OwnerScoped(this);

	{
		UToolMenu* Menu = UToolMenus::Get()->ExtendMenu("LevelEditor.MainMenu.Window");
		{
			FToolMenuSection& Section = Menu->FindOrAddSection("WindowLayout");
			Section.AddMenuEntryWithCommandList(FViewport_EXR_ScreenshotCommands::Get().PluginAction, PluginCommands);
		}
	}

	{
		UToolMenu* ToolbarMenu = UToolMenus::Get()->ExtendMenu("LevelEditor.LevelEditorToolBar.PlayToolBar");
		{
			FToolMenuSection& Section = ToolbarMenu->FindOrAddSection("PluginTools");
			{
				FToolMenuEntry& Entry = Section.AddEntry(FToolMenuEntry::InitToolBarButton(FViewport_EXR_ScreenshotCommands::Get().PluginAction));
				Entry.SetCommandList(PluginCommands);
			}
		}
	}
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FViewport_EXR_ScreenshotModule, Viewport_EXR_Screenshot)