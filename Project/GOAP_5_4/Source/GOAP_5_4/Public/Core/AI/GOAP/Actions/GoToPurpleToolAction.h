// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Core/AI/GOAP/Action.h"
#include "GoToPurpleToolAction.generated.h"

/**
 * Action that goes to a PurpleTool and changes the ObtainedPurpleTool fact
 */
UCLASS()
class GOAP_5_4_API UGoToPurpleToolAction : public UAction
{
	GENERATED_BODY()
public:
	UGoToPurpleToolAction();

	virtual void Execute()override;
	virtual void Finished()override;

	virtual int32 GetCost()override;
};
