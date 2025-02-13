// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/AI/GOAP/Actions/GoToBlueBlock.h"
#include "Core/AI/GOAP/AgentComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "NavigationSystem.h"
#include "AI/NavigationSystemBase.h"


UGoToBlueBlock::UGoToBlueBlock()
{
	Name_ = "GoToBlueBlock";
	Effect_ = TPair<FString, bool>("InBlueBlockPos", true);
	Preconditions_ = TMap<FString, bool>();
	Preconditions_.Add(TPair<FString, bool>("ToolEquipped", true));
	Cost_ = 4;
}

void UGoToBlueBlock::Execute()
{

	//get AIController, AIChar and nearest BlueBlock
	auto AIPawn = Cast<APawn>(AgentComp_->GetOwner());
	auto AIController = Cast<AAIController>(AIPawn->GetController());
	auto AIChar = Cast<ACustomAICharacter>(AIPawn);
	auto BlueBlock = AgentComp_->GetWorldMemory()->GetNearestBlueBlock();

	if(IsValid(AIChar)&&IsValid(BlueBlock) && IsValid(AIController) && AgentComp_->GetWorldMemory()->GetWorldState()["ToolEquipped"] == true){
		
		//correct the actorlocation for the hit mesh
		FVector GotoLoc = BlueBlock->GetActorLocation();
		GotoLoc.X -= 70;
		GotoLoc.Y += 20;

		//if location is reachable, update world facts and set blackboard values
		auto World = AIChar->GetWorld();
		UNavigationSystemV1* NavSystem = FNavigationSystem::GetCurrent<UNavigationSystemV1>(World);

		FVector::FReal PathCost = FLT_MAX;
		auto PathExists = NavSystem->GetPathCost(AIChar->GetActorLocation(), GotoLoc, PathCost, nullptr);
		if (PathExists == ENavigationQueryResult::Success && PathCost < FLT_MAX) {
			AgentComp_->GetWorldMemory()->GetWorldState()[Effect_.Key] = true;
			//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString("Path found!"));
			AIController->GetBlackboardComponent()->SetValueAsBool("GoToEnable", true);
			AIController->GetBlackboardComponent()->SetValueAsVector("GoToLocation", GotoLoc);
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

void UGoToBlueBlock::Finished()
{
	auto AIPawn = Cast<APawn>(AgentComp_->GetOwner());
	auto AIController = Cast<AAIController>(AIPawn->GetController());

	if (IsValid(AIController)) {
		//update blackboard value to disable sequence in the behavior tree
		AIController->GetBlackboardComponent()->SetValueAsBool("GoToEnable", false);
	}
}

int32 UGoToBlueBlock::GetCost()
{

	auto AIPawn = Cast<APawn>(AgentComp_->GetOwner());
	auto AIChar = Cast<ACustomAICharacter>(AIPawn);


	//if the nearest blueblock exists, then the distance to it are the costs. INT_MAX if not
	auto BlueBlock = AgentComp_->GetWorldMemory()->GetNearestBlueBlock();
	if (IsValid(BlueBlock)) {
		FVector GotoLoc = BlueBlock->GetActorLocation();
		GotoLoc.X -= 70;
		//GotoLoc.Y -= 25;
		return FVector::Dist(AIChar->GetActorLocation(), GotoLoc);
	}
	
	return INT_MAX;


}
