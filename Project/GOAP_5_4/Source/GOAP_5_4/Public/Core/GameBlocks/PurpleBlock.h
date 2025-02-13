// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Core/GameBlocks/Block.h"
#include "PurpleBlock.generated.h"

/**
 * Higher tier block than BlueBlock, can be destroyed by tier 2 and above tools
 */
UCLASS()
class GOAP_5_4_API APurpleBlock : public ABlock
{
	GENERATED_BODY()
public:
	APurpleBlock();

protected:
	virtual void BeginPlay() override;


public:
	virtual void Tick(float DeltaTime) override;
};
