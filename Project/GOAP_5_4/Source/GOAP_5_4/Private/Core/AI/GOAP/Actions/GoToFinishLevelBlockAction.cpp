// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/AI/GOAP/Actions/GoToFinishLevelBlockAction.h"
#include "Core/AI/GOAP/AgentComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include <Core/AI/CustomAICharacter.h>
#include <NavigationSystem.h>

UGoToFinishLevelBlockAction::UGoToFinishLevelBlockAction()
{
	Name_ = "GoToFinishLevelBlock";
	Effect_ = TPair<FString, bool>("InFinishLevelBlockPos", true);
	Preconditions_ = TMap<FString, bool>();
	Preconditions_.Add(TPair<FString, bool>("PlatinToolEquipped", true));
	Cost_ = 4;
}

void UGoToFinishLevelBlockAction::Execute()
{
	//get AIController, AIChar and FinishLevelBlock
	auto AIPawn = Cast<APawn>(AgentComp_->GetOwner());
	auto AIController = Cast<AAIController>(AIPawn->GetController());
	auto AIChar = Cast<ACustomAICharacter>(AIPawn);
	auto FinishLevelBlock = AgentComp_->GetWorldMemory()->GetFinishLevelBlock();

	if (IsValid(AIChar)&&IsValid(FinishLevelBlock) && IsValid(AIController) && AgentComp_->GetWorldMemory()->GetWorldState()["PlatinToolEquipped"] == true) {
		//correct the actorlocation for the hit mesh
		FVector GotoLoc = FinishLevelBlock->GetActorLocation();
		GotoLoc.X -= 70;
		GotoLoc.Y += 20;

		//if location is reachable, update world facts and set blackboard values
		auto World = AIChar->GetWorld();
		UNavigationSystemV1* NavSystem = FNavigationSystem::GetCurrent<UNavigationSystemV1>(World);

		float PathCost = FLT_MAX;
		auto PathExists = NavSystem->GetPathCost(AIChar->GetActorLocation(), GotoLoc, PathCost, nullptr);
		if (PathExists == ENavigationQueryResult::Success && PathCost < FLT_MAX) {
			//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString("Path found!"));
			AgentComp_->GetWorldMemory()->GetWorldState()[Effect_.Key] = true;
			AIController->GetBlackboardComponent()->SetValueAsBool("GoToEnable", true);
			AIController->GetBlackboardComponent()->SetValueAsVector("GoToLocation", GotoLoc);
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

void UGoToFinishLevelBlockAction::Finished()
{
	auto AIPawn = Cast<APawn>(AgentComp_->GetOwner());
	auto AIController = Cast<AAIController>(AIPawn->GetController());
	if (IsValid(AIController)) {
		//update blackboard value to disable sequence in the behavior tree
		AIController->GetBlackboardComponent()->SetValueAsBool("GoToEnable", false);
	}

}

int32 UGoToFinishLevelBlockAction::GetCost()
{
	auto AIPawn = Cast<APawn>(AgentComp_->GetOwner());
	auto AIChar = Cast<ACustomAICharacter>(AIPawn);

	//if the nearest blueblock exists, then the distance to it are the costs. INT_MAX if not
	auto FinishLevelBlock = AgentComp_->GetWorldMemory()->GetFinishLevelBlock();
	if (IsValid(FinishLevelBlock)) {
		FVector GotoLoc = FinishLevelBlock->GetActorLocation();
		GotoLoc.X -= 75;
		GotoLoc.Y -= 25;

		return FVector::Dist(AIChar->GetActorLocation(), GotoLoc);
	}

	return INT_MAX;

}
