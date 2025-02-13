// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Core/AI/GOAP/Action.h"
#include "CollectToolAction.generated.h"

/**
 * Action changes the world fact HasTool when a BlueTool is obtained
 */
UCLASS()
class GOAP_5_4_API UCollectToolAction : public UAction
{
	GENERATED_BODY()
public:
	UCollectToolAction();

	virtual void Execute()override;
	virtual void Finished()override;
	
};
