// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/ItemTools/PlatinTool.h"
#include <Core/AI/CustomAICharacter.h>

APlatinTool::APlatinTool(): ATool()
{
	ToolName_ = "PlatinTool";
	ShopCost_ = 5000;
	InventorySpace_ = 10;
	DamagePerAttack_ = 240;
	Tier_ = 4;
	MaxUses_ = 20;
}

void APlatinTool::BeginPlay()
{
	Super::BeginPlay();
}

void APlatinTool::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void APlatinTool::AddToAIInventory(ACustomAICharacter* AIChar)
{
	AIChar->AddToToolInventory(NewObject<APlatinTool>());
}
