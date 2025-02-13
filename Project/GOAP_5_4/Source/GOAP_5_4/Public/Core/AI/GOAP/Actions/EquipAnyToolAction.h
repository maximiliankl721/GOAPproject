// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Core/AI/GOAP/Action.h"
#include "EquipAnyToolAction.generated.h"

/**
 * Action that equips the first Tool in the Inventory, when it's not empty
 * Changes the ToolEquipped world fact
 */
UCLASS()
class GOAP_5_4_API UEquipAnyToolAction : public UAction
{
	GENERATED_BODY()

public:
	UEquipAnyToolAction();

	virtual void Execute()override;
	virtual void Finished()override;
	
};
