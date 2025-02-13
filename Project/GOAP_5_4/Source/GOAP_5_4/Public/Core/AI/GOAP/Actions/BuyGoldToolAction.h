// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Core/AI/GOAP/Action.h"
#include "BuyGoldToolAction.generated.h"

/**
 * Action to buy a GoldTool and changes the HasGoldTool fact
 */
UCLASS()
class GOAP_5_4_API UBuyGoldToolAction : public UAction
{
	GENERATED_BODY()

public:
	UBuyGoldToolAction();

	virtual void Execute()override;
	virtual void Finished()override;
	virtual int32 GetCost()override;
	
};
