// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Core/AI/GOAP/Action.h"
#include "CollectPurpleToolAction.generated.h"

/**
 * Action changes the world fact HasPurpleTool when a PurpleTool is obtained
 */
UCLASS()
class GOAP_5_4_API UCollectPurpleToolAction : public UAction
{
	GENERATED_BODY()

public:
	UCollectPurpleToolAction();
	virtual void Execute()override;
	virtual void Finished()override;
};
