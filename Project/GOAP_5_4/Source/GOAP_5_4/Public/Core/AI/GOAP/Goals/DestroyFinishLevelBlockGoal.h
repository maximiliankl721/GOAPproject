// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Core/AI/GOAP/Goal.h"
#include "DestroyFinishLevelBlockGoal.generated.h"

/**
 * Represents the Goal for destroying the FinishLevelBlock
 */
UCLASS()
class GOAP_5_4_API UDestroyFinishLevelBlockGoal : public UGoal
{
	GENERATED_BODY()
	
public:
	UDestroyFinishLevelBlockGoal();
};
