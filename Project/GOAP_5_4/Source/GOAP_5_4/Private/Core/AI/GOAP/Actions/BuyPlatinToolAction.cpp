// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/AI/GOAP/Actions/BuyPlatinToolAction.h"
#include "Core/AI/GOAP/AgentComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Core/AI/CustomAICharacter.h"
#include <Core/ItemTools/PlatinTool.h>

UBuyPlatinToolAction::UBuyPlatinToolAction()
{
	Name_ = "BuyPlatinTool";
	Effect_ = TPair<FString, bool>("HasPlatinTool", true);
	Cost_ = 1;
}

void UBuyPlatinToolAction::Execute()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString("BuyPlatinTool"));
	//Get AIController and CustomAIChar and create a PlatinTool
	auto AIPawn = Cast<APawn>(AgentComp_->GetOwner());
	auto AIController = Cast<AAIController>(AIPawn->GetController());
	auto CustomAIChar = Cast<ACustomAICharacter>(AIPawn);
	auto PlatinTool = NewObject<APlatinTool>();

	if (IsValid(AIController) && IsValid(CustomAIChar) && CustomAIChar->GetBalance() >= PlatinTool->GetShopCost()) {
		//add tool to inventory, update AIChar's balance, update the world fact and set the Blackboard component
		if (CustomAIChar->CanBeAddedToInventory(PlatinTool->GetInventorySpace())) {
			CustomAIChar->AddToToolInventory(PlatinTool);
			CustomAIChar->AddBalance(-PlatinTool->GetShopCost());

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

void UBuyPlatinToolAction::Finished()
{
	auto AIPawn = Cast<APawn>(AgentComp_->GetOwner());
	auto AIController = Cast<AAIController>(AIPawn->GetController());
	if (IsValid(AIController)) {
		//update the blackboard component to deactivate the sequence in the behavior tree
		AIController->GetBlackboardComponent()->SetValueAsBool("BuyToolEnable", false);
	}
}

int32 UBuyPlatinToolAction::GetCost()
{
	auto PlatinTool = NewObject<APlatinTool>();
	auto AIPawn = Cast<APawn>(AgentComp_->GetOwner());
	auto CustomAIChar = Cast<ACustomAICharacter>(AIPawn);
	//if the AIChar has enough credits to buy the tool it gets a cost otherwise it's INT_MAX
	if (IsValid(CustomAIChar) && CustomAIChar->GetBalance() >= PlatinTool->GetShopCost()) {
		return 1;
	}

	return INT32_MAX;
}
