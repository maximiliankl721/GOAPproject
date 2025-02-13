// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/AI/GOAP/Actions/EquipGoldToolAction.h"
#include "Core/AI/GOAP/AgentComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Core/ItemTools/GoldTool.h"
#include <Core/AI/CustomAICharacter.h>

UEquipGoldToolAction::UEquipGoldToolAction()
{
	Name_ = "EquipGoldToolAction";
	Effect_ = TPair<FString, bool>("GoldToolOrHigherEquipped", true);
	Preconditions_ = TMap<FString, bool>();
	Preconditions_.Add(TPair<FString, bool>("HasGoldTool", true));
	Cost_ = 1;
}

void UEquipGoldToolAction::Execute()
{
	//get the AIController and AIChar
	auto AIPawn = Cast<APawn>(AgentComp_->GetOwner());
	auto AIController = Cast<AAIController>(AIPawn->GetController());
	auto AIChar = Cast<ACustomAICharacter>(AIPawn);

	if (IsValid(AIController) && IsValid(AIChar) && AgentComp_->GetWorldMemory()->GetWorldState()["HasGoldTool"] == true && !AIChar->GetToolInventory().IsEmpty()) {

		//search for a GoldTool in the Inventory and equip it
		for (const auto Tool : AIChar->GetToolInventory()) {

			if (Tool->IsA(AGoldTool::StaticClass())) {
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

void UEquipGoldToolAction::Finished()
{
	auto AIPawn = Cast<APawn>(AgentComp_->GetOwner());
	auto AIController = Cast<AAIController>(AIPawn->GetController());
	if (IsValid(AIController)) {
		//update blackboard value
		AIController->GetBlackboardComponent()->SetValueAsBool("EquipAnyToolEnable", false);
	}
}
