// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/AI/GOAP/Actions/GoToPurpleToolAction.h"
#include "Core/AI/GOAP/AgentComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include <NavigationSystem.h>

UGoToPurpleToolAction::UGoToPurpleToolAction()
{
	Name_ = "GoToPurpleToolAction";
	Effect_ = TPair<FString, bool>("ObtainedPurpleTool", true);
	Cost_ = 4;
}

void UGoToPurpleToolAction::Execute()
{

	//get AIController, AIChar and nearest PurpleTool
	auto AIPawn = Cast<APawn>(AgentComp_->GetOwner());
	auto AIController = Cast<AAIController>(AIPawn->GetController());
	auto AIChar = Cast<ACustomAICharacter>(AIPawn);
	auto Tool = AgentComp_->GetWorldMemory()->GetNearestPurpleTool();

	if (IsValid(AIChar)&&IsValid(Tool) && IsValid(AIController)) {

		//correct the Actor location for the hit mesh
		auto ToolLoc = Tool->GetActorLocation();
		ToolLoc.X += 10;

		//if location is reachable, update world facts and set blackboard values
		auto World = AIChar->GetWorld();
		UNavigationSystemV1* NavSystem = FNavigationSystem::GetCurrent<UNavigationSystemV1>(World);

		float PathCost = FLT_MAX;
		auto PathExists = NavSystem->GetPathCost(AIChar->GetActorLocation(), ToolLoc, PathCost, nullptr);
		if (PathExists == ENavigationQueryResult::Success && PathCost < FLT_MAX) {
			//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString("Path found!"));
			AgentComp_->GetWorldMemory()->GetWorldState()[Effect_.Key] = true;
			AIController->GetBlackboardComponent()->SetValueAsBool("PickUpToolEnable", true);
			AIController->GetBlackboardComponent()->SetValueAsVector("ToolLocation", ToolLoc);
			GEngine->AddOnScreenDebugMessage(-1, 2.5f, FColor::Red, TEXT("World fact ") + Effect_.Key + TEXT(" changes to true!"));

			SuccessStatus_ = Status::SUCCESS;
		}
		else {
			SuccessStatus_ = Status::FAILED;
		}

	}
	else {
		SuccessStatus_ = Status::FAILED;
	}
}

void UGoToPurpleToolAction::Finished()
{
	auto AIPawn = Cast<APawn>(AgentComp_->GetOwner());
	auto AIController = Cast<AAIController>(AIPawn->GetController());
	if (IsValid(AIController)) {
		//update blackboard value to disable sequence in the behavior tree
		AIController->GetBlackboardComponent()->SetValueAsBool("PickUpToolEnable", false);
	}
}

int32 UGoToPurpleToolAction::GetCost()
{
	auto AIPawn = Cast<APawn>(AgentComp_->GetOwner());
	auto AIChar = Cast<ACustomAICharacter>(AIPawn);

	auto PurpleTool = AgentComp_->GetWorldMemory()->GetNearestPurpleTool();
	//if the nearest PurpleTool exists, then the distance to it are the costs. INT_MAX if no
	if (IsValid(PurpleTool)) {
		return FVector::Dist(AIChar->GetActorLocation(), PurpleTool->GetActorLocation());
	}

	return INT_MAX;
}
