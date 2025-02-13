// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/AI/GOAP/Actions/BuyPurpleToolAction.h"
#include "Core/AI/GOAP/AgentComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Core/AI/CustomAICharacter.h"

UBuyPurpleToolAction::UBuyPurpleToolAction()
{
	Name_ = "BuyPurpleTool";
	Effect_ = TPair<FString, bool>("HasPurpleTool", true);
	Cost_ = 1;
}

void UBuyPurpleToolAction::Execute()
{
	//Get AIController and CustomAIChar and create a PurpleTool
	auto AIPawn = Cast<APawn>(AgentComp_->GetOwner());
	auto AIController = Cast<AAIController>(AIPawn->GetController());
	auto CustomAIChar = Cast<ACustomAICharacter>(AIPawn);
	auto PurpleTool = NewObject<APurpleTool>();

	if (IsValid(AIController) && IsValid(CustomAIChar) && CustomAIChar->GetBalance() >= PurpleTool->GetShopCost()) {
		if (CustomAIChar->CanBeAddedToInventory(PurpleTool->GetInventorySpace())) {
			//add tool to inventory, update AIChar's balance, update the world fact and set the Blackboard component
			CustomAIChar->AddToToolInventory(PurpleTool);
			CustomAIChar->AddBalance(-PurpleTool->GetShopCost());

			AgentComp_->GetWorldMemory()->GetWorldState()[Effect_.Key] = true;
			AIController->GetBlackboardComponent()->SetValueAsBool("BuyToolEnable", true);
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

void UBuyPurpleToolAction::Finished()
{
	auto AIPawn = Cast<APawn>(AgentComp_->GetOwner());
	auto AIController = Cast<AAIController>(AIPawn->GetController());
	if (IsValid(AIController)) {
		//update the blackboard component to deactivate the sequence in the behavior tree
		AIController->GetBlackboardComponent()->SetValueAsBool("BuyToolEnable", false);
	}
}

int32 UBuyPurpleToolAction::GetCost()
{
	auto PurpleTool = NewObject<APurpleTool>();
	auto AIPawn = Cast<APawn>(AgentComp_->GetOwner());
	auto CustomAIChar = Cast<ACustomAICharacter>(AIPawn);
	//if the AIChar has enough credits to buy the tool it gets a cost otherwise it's INT_MAX
	if (IsValid(CustomAIChar) && CustomAIChar->GetBalance() >= PurpleTool->GetShopCost()) {
		return 1;
	}

	return INT32_MAX;
}
