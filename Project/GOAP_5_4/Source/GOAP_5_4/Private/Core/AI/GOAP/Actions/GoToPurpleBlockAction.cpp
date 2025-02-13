// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/AI/GOAP/Actions/GoToPurpleBlockAction.h"
#include "Core/AI/GOAP/AgentComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include <NavigationSystem.h>

UGoToPurpleBlockAction::UGoToPurpleBlockAction()
{
	Name_ = "GoToPurpleBlock";
	Effect_ = TPair<FString, bool>("InPurpleBlockPos", true);
	Preconditions_ = TMap<FString, bool>();
	Preconditions_.Add(TPair<FString, bool>("PurpleToolOrHigherEquipped", true));
	Cost_ = 4;
}

void UGoToPurpleBlockAction::Execute()
{
	//get AIController, AIChar and nearest PurpleBlock
	auto AIPawn = Cast<APawn>(AgentComp_->GetOwner());
	auto AIController = Cast<AAIController>(AIPawn->GetController());

	auto PurpleBlock = AgentComp_->GetWorldMemory()->GetNearestPurpleBlock();
	auto AIChar = Cast<ACustomAICharacter>(AIPawn);

	if (IsValid(AIChar) && IsValid(PurpleBlock) && IsValid(AIController) && AgentComp_->GetWorldMemory()->GetWorldState()["PurpleToolOrHigherEquipped"] == true) {
		//correct the actorlocation for the hit mesh
		FVector GotoLoc = PurpleBlock->GetActorLocation();
		GotoLoc.X -= 70;
		GotoLoc.Y += 20;

		auto World = AIChar->GetWorld();
		UNavigationSystemV1* NavSystem = FNavigationSystem::GetCurrent<UNavigationSystemV1>(World);

		float PathCost = FLT_MAX;
		auto PathExists = NavSystem->GetPathCost(AIChar->GetActorLocation(), GotoLoc, PathCost, nullptr);
		if (PathExists == ENavigationQueryResult::Success && PathCost < FLT_MAX) {
			AgentComp_->GetWorldMemory()->GetWorldState()[Effect_.Key] = true;
			//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString("Path found!"));
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

void UGoToPurpleBlockAction::Finished()
{
	auto AIPawn = Cast<APawn>(AgentComp_->GetOwner());
	auto AIController = Cast<AAIController>(AIPawn->GetController());
	if (IsValid(AIController)) {
		//update blackboard value to disable sequence in the behavior tree
		AIController->GetBlackboardComponent()->SetValueAsBool("GoToEnable", false);
	}
}

int32 UGoToPurpleBlockAction::GetCost()
{
	auto AIPawn = Cast<APawn>(AgentComp_->GetOwner());
	auto AIChar = Cast<ACustomAICharacter>(AIPawn);

	auto PurpleBlock = AgentComp_->GetWorldMemory()->GetNearestPurpleBlock();
	//if the nearest blueblock exists, then the distance to it are the costs. INT_MAX if not
	if (IsValid(PurpleBlock)) {
		FVector GotoLoc = PurpleBlock->GetActorLocation();
		GotoLoc.X -= 40;

		return FVector::Dist(AIChar->GetActorLocation(), GotoLoc);

	}
	else {
		return INT32_MAX;
	}

}
