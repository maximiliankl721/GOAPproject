// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/AI/AStar/SearchGraph.h"

TArray<FNode>& USearchGraph::GetNodes()
{
	return Nodes_;
}

void USearchGraph::AddNode(FNode NewNode)
{
	Nodes_.Add(NewNode);
}


TArray<FNode> USearchGraph::FindPathToLeave(TArray<UAction*>& AgentActions, TMap<FString, bool>& WorldState, FNode& GoalNode)
{

	TArray<FNode> Leaves;

	TArray<FNode> Open;
	Open.Add(GoalNode);



	//modified A* 
	while (!Open.IsEmpty()) {

		auto CurrentNode = GetBestCandidate(Open);

		if (Leaves.Contains(CurrentNode)) {
			Nodes_.Add(CurrentNode);
			return GeneratePath(CurrentNode);
		}

		for (const auto& Prop : CurrentNode.WorldState) {
			//check if property don't match the current world fact and search all action that changes that
			
			for (const auto& Action : AgentActions) {
				//if the action cost is >= INT32_MAX it can't be executed, so it will be skipped
				if (Prop.Key == Action->GetEffect().Key) {
					if (Action->GetCost() >= INT32_MAX) {
						break;
					}
					auto NewNode = FNode();
					NewNode.Name = Action->GetName();
					NewNode.CostAction = Action->GetCost();
					NewNode.PreviousNodeName = CurrentNode.Name;
					CurrentNode.Children.Add(NewNode.Name);
					//if the Action has Preconditions, and they also don't match with the current world facts
					//add them to the Open list and create a new World state, else they're are a leave in the tree
					bool PrecondNotMet = false;
					if (!Action->GetPreconditions().IsEmpty()) {

						for (const auto& Cond : Action->GetPreconditions()) {
							if (Cond.Value != WorldState[Cond.Key]) {
								NewNode.WorldState.Add(Cond);
								PrecondNotMet = true;
							}
						}

					}
					if (!PrecondNotMet) {
						Leaves.Add(NewNode);
					}

					//regular A* 
					if (!Nodes_.Contains(NewNode) && !Open.Contains(NewNode)) {
						NewNode.CostFromStart = CurrentNode.CostFromStart + NewNode.CostAction;
						NewNode.CostToEnd = GetHeuristicCost(CurrentNode);

						Open.Add(NewNode);
					}

					else if (Open.Contains(NewNode)) {

						int index = Open.IndexOfByKey(NewNode);

						if (index != INDEX_NONE && CurrentNode.CostFromStart + NewNode.CostAction < Open[index].CostFromStart) {
							Open[index].CostFromStart = CurrentNode.CostFromStart + NewNode.CostAction;
							Open[index].CostToEnd = GetHeuristicCost(CurrentNode);
							Open[index].PreviousNodeName = NewNode.PreviousNodeName;
						}
					}


				}
			}
			
		}
		Open.Remove(CurrentNode);
		Nodes_.Add(CurrentNode);
		
	}


	return TArray<FNode>();
}

TArray<FNode> USearchGraph::GeneratePath(FNode& FromNode)
{

	TArray<FNode> Path;

	FNode currentNode = FromNode;
	Path.Add(currentNode);

	while (!currentNode.PreviousNodeName.IsEmpty()) {

		for (const auto& Node : Nodes_) {
			if (currentNode.PreviousNodeName == Node.Name) {
				Path.Add(Node);
				currentNode = Node;
				break;
			}
		}

	}

	return Path;
}



int32 USearchGraph::GetHeuristicCost(FNode& Node)
{
	//the heuristic is the number of facts in the state of the node to satisfy 

	int32 HeuristicCost = INT32_MAX;

	HeuristicCost = Node.WorldState.Num();


	return HeuristicCost;
}


FNode& USearchGraph::GetBestCandidate(TArray<FNode>& Open)
{
	int BestIndex = 0;
	int BestCost = INT_MAX;

	for (int i = 0; i < Open.Num(); i++) {
		
		if (Open[i].CostFromStart + GetHeuristicCost(Open[i]) < BestCost) {
			BestIndex = i;
			BestCost = Open[i].CostFromStart + GetHeuristicCost(Open[i]);
		}

	}

	return Open[BestIndex];
}


bool FNode::operator==(const FNode& other) const
{
	return this->Name == other.Name;
}
