// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/AI/GOAP/Actions/AttackBlueBlockAction.h"
#include "Core/AI/GOAP/AgentComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include <Core/AI/CustomAICharacter.h>

UAttackBlueBlockAction::UAttackBlueBlockAction()
{
	Name_ = "AttackBlueBlockAction";
	Effect_ = TPair<FString, bool>("BlueBlockDestroyed", true);
	Preconditions_ = TMap<FString, bool>();
	Preconditions_.Add(TPair<FString, bool>("InBlueBlockPos", true));
	Cost_ = 1;
}

void UAttackBlueBlockAction::Execute()
{


	//Get AIController and CustomAIChar
	auto AIPawn = Cast<APawn>(AgentComp_->GetOwner());
	auto AIController = Cast<AAIController>(AIPawn->GetController());
	auto AIChar = Cast<ACustomAICharacter>(AIPawn);

	if (IsValid(AIController) && IsValid(AIChar) && IsValid(AIChar->GetEquippedTool()) && AgentComp_->GetWorldMemory()->GetWorldState()["InBlueBlockPos"] == true) {

		float ToolDamage = AIChar->GetEquippedTool()->GetDamagePerAttack();
		float BlockHP = AgentComp_->GetWorldMemory()->GetNearestBlueBlock()->GetHP();

		//update block HP and set the BlackboardComponent to true, to enable the sequence in the behaviortree
		AgentComp_->GetWorldMemory()->GetNearestBlueBlock()->SetHP(BlockHP - ToolDamage);
		AIController->GetBlackboardComponent()->SetValueAsBool("AttackBlueBlockEnable", true);

		if (BlockHP - ToolDamage <= 0) {
			//add the credits to the AIChar and update the use count of the tool
			AIChar->AddBalance(AgentComp_->GetWorldMemory()->GetNearestBlueBlock()->GetCreditValue());
			AIChar->GetEquippedTool()->IncreaseUseCount();
			if (AIChar->GetEquippedTool()->GetUseCount() == AIChar->GetEquippedTool()->GetMaxUses()) {
				AIChar->GetToolInventory().Remove(AIChar->GetEquippedTool());
				AIChar->UnequipTool();
			}
			//block gets destroyed and world fact will change
			AgentComp_->GetWorldMemory()->GetNearestBlueBlock()->Destroy();
			AgentComp_->GetWorldMemory()->GetWorldState()[Effect_.Key] = true;
			AgentComp_->GetWorldMemory()->ResetNearestBlueBlock();
			GEngine->AddOnScreenDebugMessage(-1, 2.5f, FColor::Red, TEXT("World fact ")+Effect_.Key+TEXT(" changes to true!"));
		}
		SuccessStatus_ = Status::SUCCESS;
	}
	else {
		SuccessStatus_ = Status::FAILED;
	}


}

void UAttackBlueBlockAction::Finished()
{
	auto AIPawn = Cast<APawn>(AgentComp_->GetOwner());
	auto AIController = Cast<AAIController>(AIPawn->GetController());
	auto AIChar = Cast<ACustomAICharacter>(AIPawn);

	if (IsValid(AIController) && IsValid(AIChar)) {
		//update the nearest block and set the blackboard component to false to disable the sequence in the behavior tree
		//AgentComp_->GetWorldMemory()->ResetNearestBlueBlock();
		AIController->GetBlackboardComponent()->SetValueAsBool("AttackBlueBlockEnable", false);
	}
}
