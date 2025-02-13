// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Core/AI/GOAP/Action.h"
#include "AttackPurpleBlockAction.generated.h"

/**
 * An action to attack a PurpleBlock and sastisfy the DestroyPurpleBlock Goal
 */
UCLASS()
class GOAP_5_4_API UAttackPurpleBlockAction : public UAction
{
	GENERATED_BODY()
public:
	UAttackPurpleBlockAction();
	virtual void Execute()override;
	virtual void Finished()override;
};
