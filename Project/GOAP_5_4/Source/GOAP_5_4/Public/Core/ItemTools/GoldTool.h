// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Core/ItemTools/Tool.h"
#include "GoldTool.generated.h"

/**
 * the secondest high tier tool higher than the PurpleTool
 */
UCLASS(BlueprintType)
class GOAP_5_4_API AGoldTool : public ATool
{
	GENERATED_BODY()
	
public:
	AGoldTool();

protected:

	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;
	virtual void AddToAIInventory(ACustomAICharacter* AIChar)override;
};
