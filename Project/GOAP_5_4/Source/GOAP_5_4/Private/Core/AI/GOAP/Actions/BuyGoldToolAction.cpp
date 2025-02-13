// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/AI/GOAP/Actions/BuyGoldToolAction.h"
#include "Core/AI/GOAP/AgentComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Core/AI/CustomAICharacter.h"

UBuyGoldToolAction::UBuyGoldToolAction()
{
	Name_ = "BuyGoldTool";
	Effect_ = TPair<FString, bool>("HasGoldTool", true);
	Cost_ = 1;
}

void UBuyGoldToolAction::Execute()
{

	//Get AIController and CustomAIChar and create a GoldTool
	auto AIPawn = Cast<APawn>(AgentComp_->GetOwner());
	auto AIController = Cast<AAIController>(AIPawn->GetController());
	auto CustomAIChar = Cast<ACustomAICharacter>(AIPawn);
	auto GoldTool = NewObject<AGoldTool>();

	if (IsValid(AIController) && IsValid(CustomAIChar) && CustomAIChar->GetBalance() >= GoldTool->GetShopCost()) {
		//add tool to inventory, update AIChar's balance, update the world fact and set the Blackboard component
		if (CustomAIChar->CanBeAddedToInventory(GoldTool->GetInventorySpace())) {
			CustomAIChar->AddToToolInventory(GoldTool);
			CustomAIChar->AddBalance(-GoldTool->GetShopCost());
			AgentComp_->GetWorldMemory()->GetWorldState()[Effect_.Key] = true;
			AIController->GetBlackboardComponent()->SetValueAsBool("BuyToolEnable", true);
			SuccessStatus_ = Status::SUCCESS;
			GEngine->AddOnScreenDebugMessage(-1, 2.5f, FColor::Red, TEXT("World fact ") + Effect_.Key + TEXT(" changes to true!"));
		}
		else {
			SuccessStatus_ = Status::FAILED;
		}
	}
	else {
		SuccessStatus_ = Status::FAILED;
	}
}

void UBuyGoldToolAction::Finished()
{
	auto AIPawn = Cast<APawn>(AgentComp_->GetOwner());
	auto AIController = Cast<AAIController>(AIPawn->GetController());
	if (IsValid(AIController)) {
		//update the blackboard component to deactivate the sequence in the behavior tree
		AIController->GetBlackboardComponent()->SetValueAsBool("BuyToolEnable", false);
	}
}

int32 UBuyGoldToolAction::GetCost()
{
	auto GoldTool = NewObject<AGoldTool>();
	auto AIPawn = Cast<APawn>(AgentComp_->GetOwner());
	auto CustomAIChar = Cast<ACustomAICharacter>(AIPawn);
	//if the AIChar has enough credits to buy the tool it gets a cost otherwise it's INT_MAX
	if (IsValid(CustomAIChar) && CustomAIChar->GetBalance() >= GoldTool->GetShopCost()) {
		return 1;
	}

	return INT32_MAX;
}
