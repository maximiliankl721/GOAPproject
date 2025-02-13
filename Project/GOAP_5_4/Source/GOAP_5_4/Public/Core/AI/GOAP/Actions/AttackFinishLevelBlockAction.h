// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Core/AI/GOAP/Action.h"
#include "AttackFinishLevelBlockAction.generated.h"

/**
 * An action to attack the FinishLevelBlock and sastisfy the DestroyFinishLevel Goal
 */
UCLASS()
class GOAP_5_4_API UAttackFinishLevelBlockAction : public UAction
{
	GENERATED_BODY()
	
public:
	UAttackFinishLevelBlockAction();

	virtual void Execute()override;
	virtual void Finished()override;
};
