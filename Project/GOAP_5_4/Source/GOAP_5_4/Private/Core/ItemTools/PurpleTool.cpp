// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/ItemTools/PurpleTool.h"
#include <Core/AI/CustomAICharacter.h>

APurpleTool::APurpleTool() : ATool()
{
	ToolName_ = "PurpleTool";
	ShopCost_ = 100;
	InventorySpace_ = 2;
	DamagePerAttack_ = 70;
	Tier_ = 2;
	MaxUses_ = 7;
}

void APurpleTool::BeginPlay()
{
	Super::BeginPlay();
}

void APurpleTool::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void APurpleTool::AddToAIInventory(ACustomAICharacter* AIChar)
{
	AIChar->AddToToolInventory(NewObject<APurpleTool>());
}
