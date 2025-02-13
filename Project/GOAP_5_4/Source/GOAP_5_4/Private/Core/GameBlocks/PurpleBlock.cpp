// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/GameBlocks/PurpleBlock.h"

APurpleBlock::APurpleBlock(): ABlock()
{

	HitPoints_ = 250;
	CreditValue_ = 40;
	MinToolTier_ = 2;
}

void APurpleBlock::BeginPlay()
{
	Super::BeginPlay();
}


void APurpleBlock::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
