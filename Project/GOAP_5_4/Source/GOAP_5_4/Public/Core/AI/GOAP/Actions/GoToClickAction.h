// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Core/AI/GOAP/Action.h"
#include "GoToClickAction.generated.h"

/**
 * Action that goes to the latest ClickPostion and changes the InClickPos fact, when a Click Position exists
 */
UCLASS()
class GOAP_5_4_API UGoToClickAction : public UAction
{
	GENERATED_BODY()
public:
	UGoToClickAction();
	virtual void Execute()override;
	virtual void Finished()override;
	virtual int32 GetCost()override;
};
