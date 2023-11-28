// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EditorSubsystem.h"
#include "OculusQuestViewportSubsystem.generated.h"

/**
 * 
 */
UCLASS()
class OCULUSQUESTVIEWPORTPREVIEW_API UOculusQuestViewportSubsystem : public UEditorSubsystem
{
	GENERATED_BODY()
	
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
};
