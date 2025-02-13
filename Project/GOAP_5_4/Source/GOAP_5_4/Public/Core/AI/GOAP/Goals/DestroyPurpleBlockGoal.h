// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Core/AI/GOAP/Goal.h"
#include "DestroyPurpleBlockGoal.generated.h"

/**
 * Represents the Goal for destroying a PurpleBlock
 */
UCLASS()
class GOAP_5_4_API UDestroyPurpleBlockGoal : public UGoal
{
	GENERATED_BODY()
public:
	UDestroyPurpleBlockGoal();
};
