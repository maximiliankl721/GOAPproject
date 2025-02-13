// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Core/AI/GOAP/Action.h"
#include "GoToBlueToolAction.generated.h"

/**
 * Action that goes to a BlueTool and changes the ObtainedBlueTool fact
 */
UCLASS()
class GOAP_5_4_API UGoToBlueToolAction : public UAction
{
	GENERATED_BODY()

public:
	UGoToBlueToolAction();

	virtual void Execute()override;
	virtual void Finished()override;

	virtual int32 GetCost()override;
	
};
