// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/GameBlocks/BlueBlock.h"

ABlueBlock::ABlueBlock(): ABlock()
{
	//Super::ABlock();
	MinToolTier_ = 1;
}

void ABlueBlock::BeginPlay()
{
	Super::BeginPlay();
}

void ABlueBlock::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);


}


