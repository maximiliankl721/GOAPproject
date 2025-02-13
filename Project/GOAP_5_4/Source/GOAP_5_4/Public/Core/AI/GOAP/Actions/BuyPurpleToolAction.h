// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Core/AI/GOAP/Action.h"
#include "BuyPurpleToolAction.generated.h"

/**
 * Action to buy a PurpleTool and change the HasPurpleTool fact
 */
UCLASS()
class GOAP_5_4_API UBuyPurpleToolAction : public UAction
{
	GENERATED_BODY()

public:
	UBuyPurpleToolAction();

	virtual void Execute()override;
	virtual void Finished()override;

	virtual int32 GetCost()override;
	
};
