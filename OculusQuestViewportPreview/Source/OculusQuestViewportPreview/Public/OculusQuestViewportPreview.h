// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"

class FToolBarBuilder;
class FMenuBuilder;

class FOculusQuestViewportPreviewModule : public IModuleInterface
{
public:

	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
	
private:
	void RegisterMenus();
	void ToggleQuestPreview();
	void OnButtonPressed();
	
	bool QuestPreviewEnabled = true;
	TSharedPtr<class FUICommandList> PluginCommands;
};
