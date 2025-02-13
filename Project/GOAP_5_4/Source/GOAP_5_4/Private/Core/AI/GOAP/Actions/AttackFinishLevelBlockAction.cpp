// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/AI/GOAP/Actions/AttackFinishLevelBlockAction.h"
#include "Core/AI/GOAP/AgentComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include <Core/AI/CustomAICharacter.h>

UAttackFinishLevelBlockAction::UAttackFinishLevelBlockAction()
{
	Name_ = "AttackFinishLevelBlockAction";
	Effect_ = TPair<FString, bool>("FinishLevelBlockDestroyed", true);
	Preconditions_ = TMap<FString, bool>();
	Preconditions_.Add(TPair<FString, bool>("InFinishLevelBlockPos", true));
	Cost_ = 1;
}

void UAttackFinishLevelBlockAction::Execute()
{
	
	//Get AIController and CustomAIChar
	auto AIPawn = Cast<APawn>(AgentComp_->GetOwner());
	auto AIController = Cast<AAIController>(AIPawn->GetController());
	auto AIChar = Cast<ACustomAICharacter>(AIPawn);

	if (IsValid(AIController) && IsValid(AIChar) && IsValid(AIChar->GetEquippedTool()) && AgentComp_->GetWorldMemory()->GetWorldState()["InFinishLevelBlockPos"] == true) {

		float ToolDamage = AIChar->GetEquippedTool()->GetDamagePerAttack();
		float BlockHP = AgentComp_->GetWorldMemory()->GetFinishLevelBlock()->GetHP();

		//update block HP and set the BlackboardComponent to true, to enable the sequence in the behaviortree

		AgentComp_->GetWorldMemory()->GetFinishLevelBlock()->SetHP(BlockHP - ToolDamage);
		AIController->GetBlackboardComponent()->SetValueAsBool("AttackFinishLevelBlockEnable", true);

		if (BlockHP - ToolDamage <= 0) {
			//add the credits to the AIChar and update the use count of the tool
			AIChar->AddBalance(AgentComp_->GetWorldMemory()->GetNearestGoldBlock()->GetCreditValue());
			AIChar->GetEquippedTool()->IncreaseUseCount();
			if (AIChar->GetEquippedTool()->GetUseCount() == AIChar->GetEquippedTool()->GetMaxUses()) {
				AIChar->GetToolInventory().Remove(AIChar->GetEquippedTool());
				AIChar->UnequipTool();
			}
			//block gets destroyed and world fact will change
			AgentComp_->GetWorldMemory()->GetFinishLevelBlock()->Destroy();
			AgentComp_->GetWorldMemory()->GetWorldState()[Effect_.Key] = true;
			//since the FinishLevelBlock is the end goal, it pauses the game
			AgentComp_->SetSimulationStop();
			GEngine->AddOnScreenDebugMessage(-1, 2.5f, FColor::Red, TEXT("World fact ") + Effect_.Key + TEXT(" changes to true!"));
		}
		SuccessStatus_ = Status::SUCCESS;
	}
	else {
		SuccessStatus_ = Status::FAILED;
	}
}

void UAttackFinishLevelBlockAction::Finished()
{
	auto AIPawn = Cast<APawn>(AgentComp_->GetOwner());
	auto AIController = Cast<AAIController>(AIPawn->GetController());
	auto AIChar = Cast<ACustomAICharacter>(AIPawn);

	if (IsValid(AIController) && IsValid(AIChar)) {
		//set the blackboard component to false to disable the sequence in the behavior tree
		AIController->GetBlackboardComponent()->SetValueAsBool("AttackFinishLevelBlockEnable", false);
	}
}
