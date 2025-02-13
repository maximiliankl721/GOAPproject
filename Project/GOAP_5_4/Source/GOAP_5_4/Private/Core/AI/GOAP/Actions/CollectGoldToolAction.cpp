// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/AI/GOAP/Actions/CollectGoldToolAction.h"
#include "Core/AI/GOAP/AgentComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include <Core/AI/CustomAICharacter.h>

UCollectGoldToolAction::UCollectGoldToolAction()
{
	Name_ = "CollectGoldToolAction";
	Effect_ = TPair<FString, bool>("HasGoldTool", true);
	Preconditions_ = TMap<FString, bool>();
	Preconditions_.Add(TPair<FString, bool>("ObtainedGoldTool", true));
	Cost_ = 1;
}

void UCollectGoldToolAction::Execute()
{

	//Get AIController
	auto AIPawn = Cast<APawn>(AgentComp_->GetOwner());
	auto AIController = Cast<AAIController>(AIPawn->GetController());


	if (IsValid(AIController) && AgentComp_->GetWorldMemory()->GetWorldState()["ObtainedGoldTool"] == true) {

		//update world fact and set the blackboard value
		AgentComp_->GetWorldMemory()->GetWorldState()[Effect_.Key] = true;
		AIController->GetBlackboardComponent()->SetValueAsBool("CollectToolEnable", true);
		GEngine->AddOnScreenDebugMessage(-1, 2.5f, FColor::Red, TEXT("World fact ") + Effect_.Key + TEXT(" changes to true!"));

		SuccessStatus_ = Status::SUCCESS;
	}
	else {
		SuccessStatus_ = Status::FAILED;

	}
}

void UCollectGoldToolAction::Finished()
{
	auto AIPawn = Cast<APawn>(AgentComp_->GetOwner());
	auto AIController = Cast<AAIController>(AIPawn->GetController());
	if (IsValid(AIController)) {
		//set the blackboard value to deactivate sequence in the behavior tree
		AIController->GetBlackboardComponent()->SetValueAsBool("CollectToolEnable", false);
	}

}
