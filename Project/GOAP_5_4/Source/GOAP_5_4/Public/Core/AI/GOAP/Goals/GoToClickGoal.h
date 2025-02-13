// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Core/AI/GOAP/Goal.h"
#include "GoToClickGoal.generated.h"

/**
 * Represents the Goal for going to the Click Position
 */
UCLASS()
class GOAP_5_4_API UGoToClickGoal : public UGoal
{
	GENERATED_BODY()
public:
	UGoToClickGoal();
	
};
