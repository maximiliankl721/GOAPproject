// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Core/AI/GOAP/Action.h"
#include "BuyPlatinToolAction.generated.h"

/**
 * Action to buy a PlatinTool and change the HasPlatinTool fact
 */
UCLASS()
class GOAP_5_4_API UBuyPlatinToolAction : public UAction
{
	GENERATED_BODY()

public:
	UBuyPlatinToolAction();

	virtual void Execute()override;
	virtual void Finished()override;

	virtual int32 GetCost()override;
	
};
