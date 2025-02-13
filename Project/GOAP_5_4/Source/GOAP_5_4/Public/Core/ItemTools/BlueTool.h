// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Core/ItemTools/Tool.h"
#include "BlueTool.generated.h"

/**
 * The lowest tier tool
 */
UCLASS(BlueprintType)
class GOAP_5_4_API ABlueTool : public ATool
{
	GENERATED_BODY()

public:
	ABlueTool();

protected:

	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;
	virtual void AddToAIInventory(ACustomAICharacter* AIChar)override;
};
