// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/AI/GOAP/Actions/GoToGoldBlockAction.h"
#include "Core/AI/GOAP/AgentComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include <NavigationSystem.h>

UGoToGoldBlockAction::UGoToGoldBlockAction()
{
	Name_ = "GoToGoldBlock";
	Effect_ = TPair<FString, bool>("InGoldBlockPos", true);
	Preconditions_ = TMap<FString, bool>();
	Preconditions_.Add(TPair<FString, bool>("GoldToolOrHigherEquipped", true));
	Cost_ = 4;
}

void UGoToGoldBlockAction::Execute()
{
	//get AIController, AIChar and nearest GoldBlock
	auto AIPawn = Cast<APawn>(AgentComp_->GetOwner());
	auto AIController = Cast<AAIController>(AIPawn->GetController());

	auto GoldBlock = AgentComp_->GetWorldMemory()->GetNearestGoldBlock();
	auto AIChar = Cast<ACustomAICharacter>(AIPawn);

	if (IsValid(AIChar)&&IsValid(GoldBlock) && IsValid(AIController) && AgentComp_->GetWorldMemory()->GetWorldState()["GoldToolOrHigherEquipped"] == true) {
		
		//correct the actorlocation for the hit mesh
		FVector GotoLoc = GoldBlock->GetActorLocation();
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

void UGoToGoldBlockAction::Finished()
{
	auto AIPawn = Cast<APawn>(AgentComp_->GetOwner());
	auto AIController = Cast<AAIController>(AIPawn->GetController());
	if (AIController) {
		//update blackboard value to disable sequence in the behavior tree
		AIController->GetBlackboardComponent()->SetValueAsBool("GoToEnable", false);
	}
}

int32 UGoToGoldBlockAction::GetCost()
{
	auto AIPawn = Cast<APawn>(AgentComp_->GetOwner());
	auto AIChar = Cast<ACustomAICharacter>(AIPawn);


	auto GoldBlock = AgentComp_->GetWorldMemory()->GetNearestGoldBlock();
	if (IsValid(GoldBlock)) {
		FVector GotoLoc = GoldBlock->GetActorLocation();
		GotoLoc.X -= 70;
		//GotoLoc.Y -= 25;
		return FVector::Dist(AIChar->GetActorLocation(), GotoLoc);

	}

	return INT_MAX;

}
