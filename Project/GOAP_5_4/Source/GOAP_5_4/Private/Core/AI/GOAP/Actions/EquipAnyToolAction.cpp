// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/AI/GOAP/Actions/EquipAnyToolAction.h"
#include "Core/AI/GOAP/AgentComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include <Core/AI/CustomAICharacter.h>

UEquipAnyToolAction::UEquipAnyToolAction()
{
	Name_ = "EquipAnyToolAction";
	Effect_ = TPair<FString, bool>("ToolEquipped", true);
	Preconditions_ = TMap<FString, bool>();
	Preconditions_.Add(TPair<FString, bool>("HasTool", true));
	Cost_ = 1;
}

void UEquipAnyToolAction::Execute()
{

	//get the AIController and AIChar
	auto AIPawn = Cast<APawn>(AgentComp_->GetOwner());
	auto AIController = Cast<AAIController>(AIPawn->GetController());
	auto AIChar = Cast<ACustomAICharacter>(AIPawn);

	if (IsValid(AIController) && IsValid(AIChar) && AgentComp_->GetWorldMemory()->GetWorldState()["HasTool"] == true) {
		
		//equip the first tool in the inventory, update world fact and blackboard value
		if (!AIChar->GetToolInventory().IsEmpty()) {
			AIChar->SetEquippedTool(AIChar->GetToolInventory()[0]);
			AgentComp_->GetWorldMemory()->GetWorldState()[Effect_.Key] = true;
			AIController->GetBlackboardComponent()->SetValueAsBool("EquipAnyToolEnable", true);
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

void UEquipAnyToolAction::Finished()
{
	auto AIPawn = Cast<APawn>(AgentComp_->GetOwner());
	auto AIController = Cast<AAIController>(AIPawn->GetController());
	if (IsValid(AIController)) {
		//update blackboard value
		AIController->GetBlackboardComponent()->SetValueAsBool("EquipAnyToolEnable", false);
	}
}
