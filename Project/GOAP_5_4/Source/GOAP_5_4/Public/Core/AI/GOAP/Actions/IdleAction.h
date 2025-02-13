// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Core/AI/GOAP/Action.h"
#include "IdleAction.generated.h"

/**
 * Action to execute when Agent is idleing
 */
UCLASS()
class GOAP_5_4_API UIdleAction : public UAction
{
	GENERATED_BODY()
	
public:
	UIdleAction();

	virtual void Execute()override;
	virtual void Finished()override;

	

};
