// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Core/AI/GOAP/Action.h"
#include "GoToGoldToolAction.generated.h"

/**
 * Action that goes to a GoldTool and changes the ObtainedGoldTool fact
 */
UCLASS()
class GOAP_5_4_API UGoToGoldToolAction : public UAction
{
	GENERATED_BODY()

public:
	UGoToGoldToolAction();

	virtual void Execute()override;
	virtual void Finished()override;

	virtual int32 GetCost()override;
	
};
