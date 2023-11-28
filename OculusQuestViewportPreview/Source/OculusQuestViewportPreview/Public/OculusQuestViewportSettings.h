// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "OculusQuestViewportSettings.generated.h"

/**
 * 
 */
UCLASS(Config = MySetting)
class OCULUSQUESTVIEWPORTPREVIEW_API UOculusQuestViewportSettings : public UObject
{
	GENERATED_BODY()
	
public:

	UPROPERTY(Config, EditAnywhere, Category = "Settings")
	bool RunScriptOnEditorStartup = true;
	
	UPROPERTY(Config, EditAnywhere, Category = "Settings")
	TArray<FString> Flags = { "PostProcessing", "DynamicShadows", "Tessellation", "InstancedGrass", "Bloom",
										"LensFlares", "EyeAdaptation", "Vignette", "Grain", "ToneCurve", "Tonemapper",
										"MotionBlur", "Decals", "VolumetricFog", "CameraImperfections", "ColorGrading",
										"DepthOfField", "PostProcessMaterial", "SceneColorFringe" };
};
