// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Core/AI/GOAP/Action.h"
#include "CollectGoldToolAction.generated.h"

/**
 * Action changes the world fact HasGoldTool when a GoldTool is obtained
 */
UCLASS()
class GOAP_5_4_API UCollectGoldToolAction : public UAction
{
	GENERATED_BODY()

public:
	UCollectGoldToolAction();

	virtual void Execute()override;
	virtual void Finished()override;
};
