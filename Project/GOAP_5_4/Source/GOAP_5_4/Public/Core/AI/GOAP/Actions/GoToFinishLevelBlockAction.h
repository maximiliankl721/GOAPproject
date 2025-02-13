// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Core/AI/GOAP/Action.h"
#include "GoToFinishLevelBlockAction.generated.h"

/**
 * Action that moves to a FinishLevelBlock and changes the InFinishLevelBlockPos fact, when a PlatinTool is equipped
 */
UCLASS()
class GOAP_5_4_API UGoToFinishLevelBlockAction : public UAction
{
	GENERATED_BODY()
public:
	UGoToFinishLevelBlockAction();

	virtual void Execute()override;
	virtual void Finished()override;

	virtual int32 GetCost()override;
};
