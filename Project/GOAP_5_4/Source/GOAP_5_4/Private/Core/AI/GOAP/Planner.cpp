// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/AI/GOAP/Planner.h"


UPlanner::UPlanner()
{
}

void UPlanner::RequestPlan(FString Key)
{

	auto AgentActions = AgentComp_->GetActions();
	auto WorldState = AgentComp_->GetWorldMemory()->GetWorldState();

	FindBestPlan(AgentActions, WorldState);

}



void UPlanner::GeneratePlanFromPath(TArray<FNode>& Path)
{
	for (const auto& node : Path) {
		for (const auto& action : AgentComp_->GetActions()) {
			if (node.Name == action->GetName()) {
				Plan_.Add(action);
			}
		}
	}
}

void UPlanner::Replan(UAction* ExcludeAction)
{
	Plan_.Empty();

	auto AgentActions = AgentComp_->GetActions();
	auto WorldState = AgentComp_->GetWorldMemory()->GetWorldState();

	AgentActions.Remove(ExcludeAction);

	FindBestPlan(AgentActions, WorldState);

}

void UPlanner::FindBestPlan(TArray<UAction*>& AgentActions, TMap<FString, bool>& WorldState)
{
	//create the desired state for the goal and a goal node
	TMap<FString, bool> GoalState;
	GoalState.Add(AgentComp_->GetCurrentPrusuedGoalName(), true);

	auto Graph = NewObject<USearchGraph>();
	auto GoalNode = FNode();
	GoalNode.Name = "GoalNode";
	GoalNode.CostAction = 0;
	GoalNode.CostFromStart = 0;
	GoalNode.CostToEnd = Graph->GetHeuristicCost(GoalNode);
	GoalNode.WorldState = GoalState;

	//GeneratePlan
	auto Path = Graph->FindPathToLeave(AgentActions, WorldState, GoalNode);
	GeneratePlanFromPath(Path);

	if (!Plan_.IsEmpty()) {
		IsPlanAvailable = true;
	}
}

TArray<UAction*> UPlanner::ReturnPlan()
{
	return Plan_;
}

void UPlanner::ResetPlan()
{
	Plan_ = TArray<UAction*>();
}

UAgentComponent* UPlanner::GetAgentComp()
{
	return AgentComp_;
}

void UPlanner::SetAgentComp(UAgentComponent* AgentComp)
{
	if (AgentComp) {
		AgentComp_ = AgentComp;
	}
}
