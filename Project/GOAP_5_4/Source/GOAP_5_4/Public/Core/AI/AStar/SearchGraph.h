// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include <Core/AI/GOAP/Action.h>
#include "SearchGraph.generated.h"



/*
* Struct that represent a Node in the SearchGraph
*/
USTRUCT()
struct FNode {
	GENERATED_BODY()

	
	FString Name;

	FString PreviousNodeName;
	
	int32 CostAction;

	int32 CostFromStart;

	int32 CostToEnd;
	
	TArray<FString> Children;

	TMap<FString, bool> WorldState;
	


	bool operator==(const FNode& other)const ;
};



/**
 * SearchGraph that is constructed by the planner, and searches with a modified A* to find the most efficient series of Action to sastify a goal
 */
UCLASS()
class GOAP_5_4_API USearchGraph : public UObject
{
	GENERATED_BODY()

public:

	//returns all Nodes in the Searchgraph
	TArray<FNode>& GetNodes();

	//add Nodes in the list of all Nodes in the Searchgraph
	void AddNode(FNode NewNode);

	//finds leaf-node for the path with the lowest cost
	TArray<FNode> FindPathToLeave(TArray<UAction*>& AgentActions, TMap<FString, bool>& WorldState, FNode& GoalNode);

	//generates a sequence of nodes from the given node to the root-node (goal)
	TArray<FNode> GeneratePath(FNode& FromNode);

	//returns the heuristic cost to the end of the path from a node
	int32 GetHeuristicCost(FNode& Node);

	//determines the best candidate node with the lowest cost to the end
	FNode& GetBestCandidate(TArray<FNode>& Open);

	

private:

	TArray<FNode> Nodes_;


};
