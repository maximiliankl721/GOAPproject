// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Core/GameBlocks/Block.h"
#include "FinishLevelBlock.generated.h"

/**
 * highest tier block represent the goal for the player in the level, can only be destroyed by tier 4 tools
 */
UCLASS()
class GOAP_5_4_API AFinishLevelBlock : public ABlock
{
	GENERATED_BODY()

public: 
	AFinishLevelBlock();

protected:
	virtual void BeginPlay() override;


public:
	virtual void Tick(float DeltaTime) override;

};
