// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/AI/GOAP/Actions/GoToClickAction.h"
#include "Core/AI/GOAP/AgentComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "NavigationSystem.h"
#include "AI/NavigationSystemBase.h"
#include <GOAP_5_4/GOAP_5_4Character.h>


UGoToClickAction::UGoToClickAction()
{
	Name_ = "GoToClick";
	Effect_ = TPair<FString, bool>("InClickPos", true);
	Preconditions_ = TMap<FString, bool>();
	Preconditions_.Add(TPair<FString, bool>("ClickPosExists", true));
	Cost_ = 4;
}

void UGoToClickAction::Execute()
{
	
	//get AIController and AIChar 
	auto AIPawn = Cast<APawn>(AgentComp_->GetOwner());
	auto AIController = Cast<AAIController>(AIPawn->GetController());
	auto AIChar = Cast<ACustomAICharacter>(AIPawn);

	//get the WorldMemory and CustomPlayerCharacter
	auto WorldMemory = AgentComp_->GetWorldMemory();
	auto Character = AIChar->GetWorld()->GetFirstPlayerController()->GetCharacter();
	auto CustomPlayerCharacter = Cast<AGOAP_5_4Character>(Character);

	if (IsValid(Character)&& IsValid(AIChar) && IsValid(WorldMemory) && IsValid(AIController) && AgentComp_->GetWorldMemory()->GetWorldState()["ClickPosExists"] == true) {

		FVector GotoLoc = WorldMemory->GetClickPosition();
		
		//if click location is reachable, update world facts and set blackboard values
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
		CustomPlayerCharacter->TargetLocation = FVector(0.0f, 0.0f, 0.0f);
		CustomPlayerCharacter->PositionSet = false;

	}
	else {
		SuccessStatus_ = Status::FAILED;
	}
}

void UGoToClickAction::Finished()
{
	auto AIPawn = Cast<APawn>(AgentComp_->GetOwner());
	auto AIController = Cast<AAIController>(AIPawn->GetController());

	if (IsValid(AIController)) {
		//update blackboard value to disable sequence in the behavior tree
		AIController->GetBlackboardComponent()->SetValueAsBool("GoToEnable", false);
	}
}

int32 UGoToClickAction::GetCost()
{
	auto AIPawn = Cast<APawn>(AgentComp_->GetOwner());
	auto AIChar = Cast<ACustomAICharacter>(AIPawn);


	//if the click position exists, then the distance to it are the costs. INT_MAX if not
	FVector GotoLoc = AgentComp_->GetWorldMemory()->GetClickPosition();
	if (!GotoLoc.IsZero()) {
		return FVector::Dist(AIChar->GetActorLocation(), GotoLoc);
	}

	return INT_MAX;
}
