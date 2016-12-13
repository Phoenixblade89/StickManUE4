// Fill out your copyright notice in the Description page of Project Settings.

#include "StickMan.h"
#include "sHUD.h"
#include "StickManCharacter.h"
#include "Engine/Canvas.h"

void AsHUD::DrawHUD()
{
	Super::DrawHUD();
	//get a pointer to stickman so we can read the coins from him
	AStickManCharacter* stickMan = Cast<AStickManCharacter>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
	//figure out exactly how wide the bars should be using default values
	float barWidth = 200, barHeight = 50, barPad = 12, barMargin = 50;
	//Display the number of coins stickman has on the screen
	DrawText("Coins: " + FString::FromInt(stickMan->coins), FLinearColor::White, Canvas->SizeX - barWidth - barMargin, Canvas->SizeY - barHeight - barMargin,
		hudFont, font_scale);
}

