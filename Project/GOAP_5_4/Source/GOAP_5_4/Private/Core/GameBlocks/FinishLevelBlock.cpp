// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/GameBlocks/FinishLevelBlock.h"

AFinishLevelBlock::AFinishLevelBlock(): ABlock()
{
	HitPoints_ = 2700;
	CreditValue_ = 200;
	MinToolTier_ = 4;
}

void AFinishLevelBlock::BeginPlay()
{
	Super::BeginPlay();
}

void AFinishLevelBlock::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
