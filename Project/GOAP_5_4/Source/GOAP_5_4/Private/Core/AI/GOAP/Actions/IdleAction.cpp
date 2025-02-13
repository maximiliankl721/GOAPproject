// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/AI/GOAP/Actions/IdleAction.h"
#include "Core/AI/GOAP/AgentComponent.h"
#include "BehaviorTree/BlackboardComponent.h"

UIdleAction::UIdleAction()
{
	Name_ = "IdleAction";
	Effect_ = TPair<FString, bool>("NotIdle", true);
	Cost_ = 1;
}

void UIdleAction::Execute()
{
	//Get AIController
	auto AIPawn = Cast<APawn>(AgentComp_->GetOwner());
	auto AIController = Cast<AAIController>(AIPawn->GetController());

	if (IsValid(AIController)) {
		//update world fact and blackboard value
		AgentComp_->GetWorldMemory()->GetWorldState()[Effect_.Key] = true;
		AIController->GetBlackboardComponent()->SetValueAsBool("Idle", true);
		GEngine->AddOnScreenDebugMessage(-1, 2.5f, FColor::Red, TEXT("World fact ") + Effect_.Key + TEXT(" changes to true!"));

		SuccessStatus_ = Status::SUCCESS;
	}
	else {
		SuccessStatus_ = Status::FAILED;
	}
}

void UIdleAction::Finished()
{
	auto AIPawn = Cast<APawn>(AgentComp_->GetOwner());
	auto AIController = Cast<AAIController>(AIPawn->GetController());
	if (IsValid(AIController)) {
		//disable sequence in the behavior tree
		AIController->GetBlackboardComponent()->SetValueAsBool("Idle", false);
	}
}
