// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Core/AI/GOAP/Action.h"
#include "EquipPlatinToolAction.generated.h"

/**
 * Action that equips the first PlatinTool in the Inventory, when there is one
 * Changes the PlatinToolEquipped world fact
 */
UCLASS()
class GOAP_5_4_API UEquipPlatinToolAction : public UAction
{
	GENERATED_BODY()

public:
	UEquipPlatinToolAction();

	virtual void Execute()override;
	virtual void Finished()override;
	
};
