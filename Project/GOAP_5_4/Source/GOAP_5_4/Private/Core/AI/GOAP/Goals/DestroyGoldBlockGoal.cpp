// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/AI/GOAP/Goals/DestroyGoldBlockGoal.h"

UDestroyGoldBlockGoal::UDestroyGoldBlockGoal()
{
	Priority_ = 1;
	Name_ = "GoldBlockDestroyed";
	Value_ = true;
}
