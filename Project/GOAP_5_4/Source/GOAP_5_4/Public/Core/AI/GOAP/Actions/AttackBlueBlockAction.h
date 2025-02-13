// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Core/AI/GOAP/Action.h"
#include "AttackBlueBlockAction.generated.h"

/**
 * An action to attack an BlueBlock and sastisfy the DestroyBlueBlock Goal
 */
UCLASS()
class GOAP_5_4_API UAttackBlueBlockAction : public UAction
{
	GENERATED_BODY()

public:
	UAttackBlueBlockAction();

	virtual void Execute()override;
	virtual void Finished()override;
	
};
