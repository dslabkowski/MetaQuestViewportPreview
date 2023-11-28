// Copyright Epic Games, Inc. All Rights Reserved.

#include "OculusQuestViewportPreview.h"
#include "OculusQuestViewportSettings.h"
#include "OculusQuestViewportPreviewStyle.h"
#include "OculusQuestViewportPreviewCommands.h"
#include "Kismet/KismetSystemLibrary.h"
#include "ISettingsModule.h"
#include "Misc/MessageDialog.h"
#include "ToolMenus.h"

static const FName OculusQuestViewportPreviewTabName("OculusQuestViewportPreview");

#define LOCTEXT_NAMESPACE "FOculusQuestViewportPreviewModule"

void FOculusQuestViewportPreviewModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
	
	FOculusQuestViewportPreviewStyle::Initialize();
	FOculusQuestViewportPreviewStyle::ReloadTextures();

	FOculusQuestViewportPreviewCommands::Register();
	
	PluginCommands = MakeShareable(new FUICommandList);

	PluginCommands->MapAction(
		FOculusQuestViewportPreviewCommands::Get().PluginAction,
		FExecuteAction::CreateRaw(this, &FOculusQuestViewportPreviewModule::OnButtonPressed),
		FCanExecuteAction());

	UToolMenus::RegisterStartupCallback(FSimpleMulticastDelegate::FDelegate::CreateRaw(this, &FOculusQuestViewportPreviewModule::RegisterMenus));

	// Register settings in ProjectSettings

	if (ISettingsModule* SettingsModule = FModuleManager::GetModulePtr<ISettingsModule>("Settings"))
	{
		SettingsModule->RegisterSettings("Project", "Plugins", "OculusViewportPlugin",
			LOCTEXT("RuntimeSettingsName", "Oculus Viewport"), LOCTEXT("RuntimeSettingsDescription", "Default plugin settings."),
			GetMutableDefault<UOculusQuestViewportSettings>());
	}

	// Get defaults from UOculusQuestViewportSettings

	const UOculusQuestViewportSettings* Settings = GetMutableDefault<UOculusQuestViewportSettings>();
	QuestPreviewEnabled = Settings->RunScriptOnEditorStartup;
}

void FOculusQuestViewportPreviewModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.

	UToolMenus::UnRegisterStartupCallback(this);
	UToolMenus::UnregisterOwner(this);
	FOculusQuestViewportPreviewStyle::Shutdown();
	FOculusQuestViewportPreviewCommands::Unregister();
}

void FOculusQuestViewportPreviewModule::OnButtonPressed()
{
	ToggleQuestPreview();
}

void FOculusQuestViewportPreviewModule::RegisterMenus()
{
	// Owner will be used for cleanup in call to UToolMenus::UnregisterOwner
	FToolMenuOwnerScoped OwnerScoped(this);

	// Add entry under Window Menu
	UToolMenu* Menu = UToolMenus::Get()->ExtendMenu("LevelEditor.MainMenu.Window");
	FToolMenuSection& WindowSection = Menu->FindOrAddSection("WindowLayout");
	WindowSection.AddMenuEntryWithCommandList(FOculusQuestViewportPreviewCommands::Get().PluginAction, PluginCommands);

	// Add entry to Toolbar
	FName ToolbarMenuName ="LevelEditor.LevelEditorToolBar.User"; // Default for Unreal Engine 5
		
	#if ENGINE_MAJOR_VERSION == 4
		ToolbarMenuName = "LevelEditor.LevelEditorToolBar";
	#endif
		
	UToolMenu* ToolbarMenu = UToolMenus::Get()->ExtendMenu(ToolbarMenuName);
	FToolMenuSection& ToolbarSection = ToolbarMenu->FindOrAddSection("Settings");
	FToolMenuEntry& Entry = ToolbarSection.AddEntry(FToolMenuEntry::InitToolBarButton(FOculusQuestViewportPreviewCommands::Get().PluginAction));
	Entry.SetCommandList(PluginCommands);
}

void FOculusQuestViewportPreviewModule::ToggleQuestPreview()
{
	UOculusQuestViewportSettings* Settings = Cast<UOculusQuestViewportSettings>(UOculusQuestViewportSettings::StaticClass()->GetDefaultObject(true));

	for (FString Flag : Settings->Flags)
	{
		FString Command = "ShowFlag." + Flag + " " + FString::FromInt(int(QuestPreviewEnabled));
		UKismetSystemLibrary::ExecuteConsoleCommand(nullptr, Command, nullptr);
	}

	QuestPreviewEnabled = !QuestPreviewEnabled;
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FOculusQuestViewportPreviewModule, OculusQuestViewportPreview)