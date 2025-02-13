// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/ItemTools/GoldTool.h"
#include <Core/AI/CustomAICharacter.h>

AGoldTool::AGoldTool(): ATool()
{
	ToolName_ = "GoldTool";
	ShopCost_ = 1100;
	InventorySpace_ = 4;
	DamagePerAttack_ = 120;
	Tier_ = 3;
	MaxUses_ = 10;
}

void AGoldTool::BeginPlay()
{
	Super::BeginPlay();
}

void AGoldTool::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AGoldTool::AddToAIInventory(ACustomAICharacter* AIChar)
{
	AIChar->AddToToolInventory(NewObject<AGoldTool>());
}
