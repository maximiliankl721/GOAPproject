// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Core/AI/GOAP/Action.h"
#include "GoToBlueBlock.generated.h"

/**
 * Action that moves to a BlueBlock and changes the InBlueBlockPos fact, when a Tool is equipped
 */
UCLASS()
class GOAP_5_4_API UGoToBlueBlock : public UAction
{
	GENERATED_BODY()
public:
	UGoToBlueBlock();
	virtual void Execute()override;
	virtual void Finished()override;
	virtual int32 GetCost()override;
};
