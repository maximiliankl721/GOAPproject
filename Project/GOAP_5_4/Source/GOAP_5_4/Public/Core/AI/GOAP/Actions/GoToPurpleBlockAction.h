// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Core/AI/GOAP/Action.h"
#include "GoToPurpleBlockAction.generated.h"

/**
 * Action that moves the agent to a PurpleBlock and changes the InPurpleBlockPos fact, when a PurpleTool is equipped
 */
UCLASS()
class GOAP_5_4_API UGoToPurpleBlockAction : public UAction
{
	GENERATED_BODY()
	
public:
	UGoToPurpleBlockAction();

	virtual void Execute()override;
	virtual void Finished()override;

	virtual int32 GetCost()override;
};
