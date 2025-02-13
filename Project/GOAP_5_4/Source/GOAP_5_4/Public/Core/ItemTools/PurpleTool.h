// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Core/ItemTools/Tool.h"
#include "PurpleTool.generated.h"

/**
 * higher tier tool than the BlueTool
 */
UCLASS(BlueprintType)
class GOAP_5_4_API APurpleTool : public ATool
{
	GENERATED_BODY()

public:
	APurpleTool();
	
protected:

	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;
	virtual void AddToAIInventory(ACustomAICharacter* AIChar)override;
};
