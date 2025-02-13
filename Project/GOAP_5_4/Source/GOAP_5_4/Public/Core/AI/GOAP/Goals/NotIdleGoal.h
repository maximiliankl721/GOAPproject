// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Core/AI/GOAP/Goal.h"
#include "NotIdleGoal.generated.h"

/**
 * Represent the Goal for not idling 
 */
UCLASS()
class GOAP_5_4_API UNotIdleGoal : public UGoal
{
	GENERATED_BODY()

public:
	UNotIdleGoal();
	
};
