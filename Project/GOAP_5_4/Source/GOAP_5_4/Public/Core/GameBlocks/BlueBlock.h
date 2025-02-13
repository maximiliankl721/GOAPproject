// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Core/GameBlocks/Block.h"
#include "Core/AI/CustomAICharacter.h"
#include "BlueBlock.generated.h"

/**
 * The lowest tier block, can be destroyed by every tool
 */
UCLASS()
class GOAP_5_4_API ABlueBlock : public ABlock
{
	GENERATED_BODY()

public:
	ABlueBlock();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

};
