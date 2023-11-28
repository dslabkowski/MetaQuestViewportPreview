// Copyright Epic Games, Inc. All Rights Reserved.

#include "OculusQuestViewportPreviewCommands.h"

#define LOCTEXT_NAMESPACE "FOculusQuestViewportPreviewModule"

void FOculusQuestViewportPreviewCommands::RegisterCommands()
{
	UI_COMMAND(PluginAction, "Oculus Preview", "Switches between the normal viewport view and the way the game looks on Oculus Quest.", EUserInterfaceActionType::Button, FInputGesture());
}

#undef LOCTEXT_NAMESPACE
