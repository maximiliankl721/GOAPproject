// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Core/AI/GOAP/Action.h"
#include "EquipPurpleToolAction.generated.h"

/**
 * Action that equips the first PurpleTool in the Inventory, when there is one
 * Changes the PurpleToolEquipped world fact
 */
UCLASS()
class GOAP_5_4_API UEquipPurpleToolAction : public UAction
{
	GENERATED_BODY()

public:
	UEquipPurpleToolAction();

	virtual void Execute()override;
	virtual void Finished()override;
	
};
