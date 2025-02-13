// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Core/AI/GOAP/Goal.h"
#include "DestroyGoldBlockGoal.generated.h"

/**
 * Represents the Goal for destroying a GoldBlock
 */
UCLASS()
class GOAP_5_4_API UDestroyGoldBlockGoal : public UGoal
{
	GENERATED_BODY()

public:
	UDestroyGoldBlockGoal();
	
};
