// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/AI/GOAP/Actions/AttackGoldBlockAction.h"
#include "Core/AI/GOAP/AgentComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include <Core/AI/CustomAICharacter.h>

UAttackGoldBlockAction::UAttackGoldBlockAction()
{
	Name_ = "AttackGoldBlockAction";
	Effect_ = TPair<FString, bool>("GoldBlockDestroyed", true);
	Preconditions_ = TMap<FString, bool>();
	Preconditions_.Add(TPair<FString, bool>("InGoldBlockPos", true));
	Cost_ = 1;
}

void UAttackGoldBlockAction::Execute()
{

	//Get AIController and CustomAIChar
	auto AIPawn = Cast<APawn>(AgentComp_->GetOwner());
	auto AIController = Cast<AAIController>(AIPawn->GetController());
	auto AIChar = Cast<ACustomAICharacter>(AIPawn);

	if (IsValid(AIController) && IsValid(AIChar) && IsValid(AIChar->GetEquippedTool()) && AgentComp_->GetWorldMemory()->GetWorldState()["InGoldBlockPos"] == true) {

		float ToolDamage = AIChar->GetEquippedTool()->GetDamagePerAttack();
		float BlockHP = AgentComp_->GetWorldMemory()->GetNearestGoldBlock()->GetHP();

		//update block HP and set the BlackboardComponent to true, to enable the sequence in the behaviortree
		AgentComp_->GetWorldMemory()->GetNearestGoldBlock()->SetHP(BlockHP - ToolDamage);
		AIController->GetBlackboardComponent()->SetValueAsBool("AttackGoldBlockEnable", true);

		if (BlockHP - ToolDamage <= 0) {
			//add the credits to the AIChar and update the use count of the tool
			AIChar->AddBalance(AgentComp_->GetWorldMemory()->GetNearestGoldBlock()->GetCreditValue());
			AIChar->GetEquippedTool()->IncreaseUseCount();
			if (AIChar->GetEquippedTool()->GetUseCount() == AIChar->GetEquippedTool()->GetMaxUses()) {
				AIChar->GetToolInventory().Remove(AIChar->GetEquippedTool());
				AIChar->UnequipTool();
			}
			//block gets destroyed and world fact will change
			AgentComp_->GetWorldMemory()->GetNearestGoldBlock()->Destroy();
			AgentComp_->GetWorldMemory()->GetWorldState()[Effect_.Key] = true;
			AgentComp_->GetWorldMemory()->ResetNearestGoldBlock();
			GEngine->AddOnScreenDebugMessage(-1, 2.5f, FColor::Red, TEXT("World fact ") + Effect_.Key + TEXT(" changes to true!"));
		}
		SuccessStatus_ = Status::SUCCESS;
	}
	else {
		SuccessStatus_ = Status::FAILED;
	}
}

void UAttackGoldBlockAction::Finished()
{
	auto AIPawn = Cast<APawn>(AgentComp_->GetOwner());
	auto AIController = Cast<AAIController>(AIPawn->GetController());
	auto AIChar = Cast<ACustomAICharacter>(AIPawn);

	if (IsValid(AIController) && IsValid(AIChar)) {
		//update the nearest block and set the blackboard component to false to disable the sequence in the behavior tree
		AIController->GetBlackboardComponent()->SetValueAsBool("AttackGoldBlockEnable", false);
	}
}
