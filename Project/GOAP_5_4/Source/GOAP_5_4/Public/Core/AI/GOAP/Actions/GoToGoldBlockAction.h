// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Core/AI/GOAP/Action.h"
#include "GoToGoldBlockAction.generated.h"

/**
 * Action that moves the agent to a GoldBlock and changes the InGoldBlockPos fact, when a GoldTool is equipped
 */
UCLASS()
class GOAP_5_4_API UGoToGoldBlockAction : public UAction
{
	GENERATED_BODY()

public:
	UGoToGoldBlockAction();

	virtual void Execute()override;
	virtual void Finished()override;

	virtual int32 GetCost()override;
	
};
