// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Core/GameBlocks/Block.h"
#include "GoldBlock.generated.h"

/**
 * Higher tier block than PurpleBlock, can be destroyed by tier 3 and above tools
 */
UCLASS()
class GOAP_5_4_API AGoldBlock : public ABlock
{
	GENERATED_BODY()
public:
	AGoldBlock();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

};
