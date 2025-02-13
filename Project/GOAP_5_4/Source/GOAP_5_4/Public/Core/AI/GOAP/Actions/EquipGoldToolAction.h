// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Core/AI/GOAP/Action.h"
#include "EquipGoldToolAction.generated.h"

/**
 * Action that equips the first GoldTool in the Inventory, when there is one
 * Changes the GoldToolEquipped world fact
 */
UCLASS()
class GOAP_5_4_API UEquipGoldToolAction : public UAction
{
	GENERATED_BODY()

public:
	UEquipGoldToolAction();

	virtual void Execute()override;
	virtual void Finished()override;
	
};
