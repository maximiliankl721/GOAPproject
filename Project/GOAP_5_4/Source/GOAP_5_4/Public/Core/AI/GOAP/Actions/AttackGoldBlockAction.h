// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Core/AI/GOAP/Action.h"
#include "AttackGoldBlockAction.generated.h"

/**
 * An action to attack a GoldBlock and sastisfy the DestroyGoldBlock Goal
 */
UCLASS()
class GOAP_5_4_API UAttackGoldBlockAction : public UAction
{
	GENERATED_BODY()
public:
	UAttackGoldBlockAction();

	virtual void Execute()override;
	virtual void Finished()override;
};
