// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/GameBlocks/GoldBlock.h"

AGoldBlock::AGoldBlock(): ABlock()
{
	HitPoints_ = 700;
	CreditValue_ = 500;
	MinToolTier_ = 3;
}

void AGoldBlock::BeginPlay()
{
	Super::BeginPlay();
}

void AGoldBlock::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
