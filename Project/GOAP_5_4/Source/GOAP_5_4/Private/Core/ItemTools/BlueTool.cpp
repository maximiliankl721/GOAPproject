// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/ItemTools/BlueTool.h"
#include <Core/AI/CustomAICharacter.h>


ABlueTool::ABlueTool() : ATool()
{
	ToolName_ = "BlueTool";
	ShopCost_ = 2;
	InventorySpace_ = 1;
	DamagePerAttack_ = 20;
	Tier_ = 1;
	MaxUses_ = 4;
}

void ABlueTool::BeginPlay()
{
	Super::BeginPlay();
}

void ABlueTool::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ABlueTool::AddToAIInventory(ACustomAICharacter* AIChar)
{
	AIChar->AddToToolInventory(NewObject<ABlueTool>());
}
