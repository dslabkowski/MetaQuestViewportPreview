// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Framework/Commands/Commands.h"
#include "OculusQuestViewportPreviewStyle.h"

class FOculusQuestViewportPreviewCommands : public TCommands<FOculusQuestViewportPreviewCommands>
{
public:

	FOculusQuestViewportPreviewCommands()
		: TCommands<FOculusQuestViewportPreviewCommands>(TEXT("OculusQuestViewportPreview"), NSLOCTEXT("Contexts", "OculusQuestViewportPreview", "OculusQuestViewportPreview Plugin"), NAME_None, FOculusQuestViewportPreviewStyle::GetStyleSetName())
	{
	}

	// TCommands<> interface
	virtual void RegisterCommands() override;

public:
	TSharedPtr< FUICommandInfo > PluginAction;
};
