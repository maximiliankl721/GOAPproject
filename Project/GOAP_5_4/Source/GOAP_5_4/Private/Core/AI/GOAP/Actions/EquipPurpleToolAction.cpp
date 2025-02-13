// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/AI/GOAP/Actions/EquipPurpleToolAction.h"
#include "Core/AI/GOAP/AgentComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Core/ItemTools/PurpleTool.h"
#include <Core/AI/CustomAICharacter.h>

UEquipPurpleToolAction::UEquipPurpleToolAction()
{
	Name_ = "EquipPurpleToolAction";
	Effect_ = TPair<FString, bool>("PurpleToolOrHigherEquipped", true);
	Preconditions_ = TMap<FString, bool>();
	Preconditions_.Add(TPair<FString, bool>("HasPurpleTool", true));
	Cost_ = 1;
}

void UEquipPurpleToolAction::Execute()
{

	//get the AIController and AIChar
	auto AIPawn = Cast<APawn>(AgentComp_->GetOwner());
	auto AIController = Cast<AAIController>(AIPawn->GetController());
	auto AIChar = Cast<ACustomAICharacter>(AIPawn);

	if (IsValid(AIController) && IsValid(AIChar) && AgentComp_->GetWorldMemory()->GetWorldState()["HasPurpleTool"] == true && !AIChar->GetToolInventory().IsEmpty()) {
		//search for a GoldTool in the Inventory and equip it
		for (const auto Tool : AIChar->GetToolInventory()) {

			if (Tool->IsA(APurpleTool::StaticClass())) {
				AIChar->SetEquippedTool(Tool);
				AgentComp_->GetWorldMemory()->GetWorldState()[Effect_.Key] = true;
				AIController->GetBlackboardComponent()->SetValueAsBool("EquipAnyToolEnable", true);
				GEngine->AddOnScreenDebugMessage(-1, 2.5f, FColor::Red, TEXT("World fact ") + Effect_.Key + TEXT(" changes to true!"));

				SuccessStatus_ = Status::SUCCESS;
				break;
			}

		}
		if (!AIChar->GetEquippedTool()) {
			SuccessStatus_ = Status::FAILED;
		}

	}
	else {
		SuccessStatus_ = Status::FAILED;
	}
}

void UEquipPurpleToolAction::Finished()
{
	auto AIPawn = Cast<APawn>(AgentComp_->GetOwner());
	auto AIController = Cast<AAIController>(AIPawn->GetController());
	if (IsValid(AIController)) {
		//update blackboard value
		AIController->GetBlackboardComponent()->SetValueAsBool("EquipAnyToolEnable", false);
	}
}
