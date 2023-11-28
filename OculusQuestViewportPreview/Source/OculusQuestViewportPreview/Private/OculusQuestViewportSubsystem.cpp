// Fill out your copyright notice in the Description page of Project Settings.

#include "OculusQuestViewportSubsystem.h"
#include "Kismet/KismetSystemLibrary.h"
#include "OculusQuestViewportSettings.h"

void UOculusQuestViewportSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	if(UOculusQuestViewportSettings* Settings = GetMutableDefault<UOculusQuestViewportSettings>(); Settings->RunScriptOnEditorStartup)
	{
		for (FString Flag : Settings->Flags)
		{
			FString Command = "ShowFlag." + Flag + " 0";
			UKismetSystemLibrary::ExecuteConsoleCommand(nullptr, Command, nullptr);
		}
	}
}
