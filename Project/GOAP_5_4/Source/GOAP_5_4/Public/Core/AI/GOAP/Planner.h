// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "AgentComponent.h"
#include "Core/AI/AStar/SearchGraph.h"
#include "Planner.generated.h"

/**
 * The planner that tries to find a sequence of actions to fufill a given goal
 */


UCLASS()
class GOAP_5_4_API UPlanner : public UObject
{
	GENERATED_BODY()


public:

	UPlanner();


public:
	virtual void RequestPlan(FString Key);
	virtual void GeneratePlanFromPath(TArray<FNode>& Path);
	virtual void Replan(UAction* ExcludeAction);
	void FindBestPlan(TArray<UAction*>& AgentActions, TMap<FString, bool>& WorldState);
	virtual TArray<UAction*> ReturnPlan();
	void ResetPlan();

	bool IsPlanAvailable;

	UAgentComponent* GetAgentComp();
	void SetAgentComp(UAgentComponent* AgentComp);

private:
	UAgentComponent* AgentComp_;
	TArray<UAction*> Plan_;

};
