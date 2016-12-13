// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "GameFramework/HUD.h"
#include "sHUD.generated.h"

/**
 * 
 */
UCLASS()
class STICKMAN_API AsHUD : public AHUD
{
	GENERATED_BODY()
	
public:
	//Font used on the hud
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = HUDFont)
	UFont* hudFont;

	//Font Scale (Size)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = HUDFont)
	float font_scale;
	
	//Screen Dimensions
	FVector2D dims;

	virtual void DrawHUD() override;
};
