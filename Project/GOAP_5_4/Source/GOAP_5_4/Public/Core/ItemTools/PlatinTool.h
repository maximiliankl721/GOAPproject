// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Core/ItemTools/Tool.h"
#include "PlatinTool.generated.h"

/**
 * the highest tier tool, higher than the GoldTool and can destroy the FinishBlock
 */
UCLASS(BlueprintType)
class GOAP_5_4_API APlatinTool : public ATool
{
	GENERATED_BODY()

public:
	APlatinTool();

protected:

	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;
	virtual void AddToAIInventory(ACustomAICharacter* AIChar)override;

};
