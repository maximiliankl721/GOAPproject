// Fill out your copyright notice in the Description page of Project Settings.

#include "Core/AI/GOAP/AgentComponent.h"
#include "Core/AI/GOAP/Planner.h"
#include <Kismet/KismetMathLibrary.h>
#include <Core/AI/GOAP/Actions/IdleAction.h>
#include <Core/AI/GOAP/Actions/AttackBlueBlockAction.h>
#include <Core/AI/GOAP/Actions/GoToBlueBlock.h>
#include <Core/AI/GOAP/Goals/DestroyBlueBlockGoal.h>
#include <Core/AI/GOAP/Goals/NotIdleGoal.h>
#include <Core/AI/GOAP/Actions/EquipAnyToolAction.h>
#include <Core/AI/GOAP/Actions/CollectToolAction.h>
#include <Core/AI/GOAP/Goals/DestroyPurpleBlockGoal.h>
#include <Core/AI/GOAP/Actions/AttackPurpleBlockAction.h>
#include <Core/AI/GOAP/Actions/GoToPurpleBlockAction.h>
#include <Core/AI/GOAP/Actions/GoToBlueToolAction.h>
#include <Core/AI/GOAP/Actions/EquipPurpleToolAction.h>
#include <Core/AI/GOAP/Actions/CollectPurpleToolAction.h>
#include <Core/AI/GOAP/Actions/GoToPurpleToolAction.h>
#include <Core/AI/GOAP/Actions/BuyPurpleToolAction.h>
#include <Core/AI/GOAP/Goals/DestroyGoldBlockGoal.h>
#include <Core/AI/GOAP/Actions/AttackGoldBlockAction.h>
#include <Core/AI/GOAP/Actions/GoToGoldBlockAction.h>
#include <Core/AI/GOAP/Actions/EquipGoldToolAction.h>
#include <Core/AI/GOAP/Actions/CollectGoldToolAction.h>
#include <Core/AI/GOAP/Actions/GoToGoldToolAction.h>
#include <Core/AI/GOAP/Actions/BuyGoldToolAction.h>
#include <Core/AI/GOAP/Goals/DestroyFinishLevelBlockGoal.h>
#include <Core/AI/GOAP/Actions/AttackFinishLevelBlockAction.h>
#include <Core/AI/GOAP/Actions/GoToFinishLevelBlockAction.h>
#include <Core/AI/GOAP/Actions/EquipPlatinToolAction.h>
#include <Core/AI/GOAP/Actions/BuyPlatinToolAction.h>
#include <Core/AI/GOAP/Goals/GoToClickGoal.h>
#include <Core/AI/GOAP/Actions/GoToClickAction.h>
#include <GOAP_5_4/GOAP_5_4Character.h>
#include "BrainComponent.h"
#include <NavigationSystem.h>
#include <Core/ItemTools/PlatinTool.h>

// Sets default values for this component's properties
UAgentComponent::UAgentComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

}


// Called when the game starts
void UAgentComponent::BeginPlay()
{
	Super::BeginPlay();

	
	// Get the Actor to which this component is attached to

	FVector Location(0.0f, 0.0f, 0.0f);
	FRotator Rotation(0.0f, 0.0f, 0.0f);
	FActorSpawnParameters SpawnParams;
	AWorldMemory* MyActorInstance = GetWorld()->SpawnActor<AWorldMemory>(Location, Rotation, SpawnParams);

	WorldMemory_ = MyActorInstance;
	auto AIChar = Cast<ACustomAICharacter>(GetOwner());
	WorldMemory_->SetCustomAIChar(AIChar);
	WorldMemory_->SetAgentComponent(this);
	


	Planner_ = NewObject<UPlanner>();
	Planner_->SetAgentComp(this);


	//instanciate goal and add to goal array
	auto  DestroyBlueBlockGoal = NewObject<UDestroyBlueBlockGoal>();
	DestroyBlueBlockGoal->SetAgentComponent(this);

	auto NotIdleGoal = NewObject<UNotIdleGoal>();
	NotIdleGoal->SetAgentComponent(this);

	auto DestroyPurpleBlockGoal = NewObject<UDestroyPurpleBlockGoal>();
	DestroyPurpleBlockGoal->SetAgentComponent(this);

	auto DestroyGoldBlockGoal = NewObject<UDestroyGoldBlockGoal>();
	DestroyGoldBlockGoal->SetAgentComponent(this);

	auto DestroyFinishLevelBlockGoal = NewObject<UDestroyFinishLevelBlockGoal>();
	DestroyFinishLevelBlockGoal->SetAgentComponent(this);

	auto GoToClickGoal = NewObject<UGoToClickGoal>();
	GoToClickGoal->SetAgentComponent(this);

	Goals_.Add(DestroyBlueBlockGoal);
	Goals_.Add(NotIdleGoal);
	Goals_.Add(DestroyPurpleBlockGoal);
	Goals_.Add(DestroyGoldBlockGoal);
	Goals_.Add(DestroyFinishLevelBlockGoal);
	Goals_.Add(GoToClickGoal);


	//add Goal priority rules
	GoalPriorityRules_.Add(TPair<FString, int>(DestroyBlueBlockGoal->GetName(), 4));
	GoalPriorityRules_.Add(TPair<FString, int>(DestroyPurpleBlockGoal->GetName(), 3));
	GoalPriorityRules_.Add(TPair<FString, int>(DestroyGoldBlockGoal->GetName(), 2));
	GoalPriorityRules_.Add(TPair<FString, int>(NotIdleGoal->GetName(), 1));
	GoalPriorityRules_.Add(TPair<FString, int>(DestroyFinishLevelBlockGoal->GetName(), 0));
	GoalPriorityRules_.Add(TPair<FString, int>(GoToClickGoal->GetName(), -1));

	//add actions

	auto IdleAction = NewObject<UIdleAction>();
	IdleAction->SetAgentComp(this);

	auto AttackBlueBlockAction = NewObject<UAttackBlueBlockAction>();
	AttackBlueBlockAction->SetAgentComp(this);

	auto GoToBlueBlock = NewObject<UGoToBlueBlock>();
	GoToBlueBlock->SetAgentComp(this);

	auto EquipAnyToolAction = NewObject<UEquipAnyToolAction>();
	EquipAnyToolAction->SetAgentComp(this);

	auto CollectToolAction = NewObject<UCollectToolAction>();
	CollectToolAction->SetAgentComp(this);

	auto GoToBlueToolAction = NewObject<UGoToBlueToolAction>();
	GoToBlueToolAction->SetAgentComp(this);

	auto AttackPurpleBlockAction = NewObject<UAttackPurpleBlockAction>();
	AttackPurpleBlockAction->SetAgentComp(this);

	auto GoToPurpleBlockAction = NewObject<UGoToPurpleBlockAction>();
	GoToPurpleBlockAction->SetAgentComp(this);

	auto EquipPurpleToolAction = NewObject<UEquipPurpleToolAction>();
	EquipPurpleToolAction->SetAgentComp(this);

	auto CollectPurpleToolAction = NewObject<UCollectPurpleToolAction>();
	CollectPurpleToolAction->SetAgentComp(this);

	auto GoToPurpleToolAction = NewObject<UGoToPurpleToolAction>();
	GoToPurpleToolAction->SetAgentComp(this);

	auto BuyPurpleToolAction = NewObject<UBuyPurpleToolAction>();
	BuyPurpleToolAction->SetAgentComp(this);

	auto AttackGoldBlockAction = NewObject<UAttackGoldBlockAction>();
	AttackGoldBlockAction->SetAgentComp(this);

	auto GoToGoldBlockAction = NewObject<UGoToGoldBlockAction>();
	GoToGoldBlockAction->SetAgentComp(this);

	auto EquipGoldToolAction = NewObject<UEquipGoldToolAction>();
	EquipGoldToolAction->SetAgentComp(this);

	auto CollectGoldToolAction = NewObject<UCollectGoldToolAction>();
	CollectGoldToolAction->SetAgentComp(this);

	auto GoToGoldToolAction = NewObject<UGoToGoldToolAction>();
	GoToGoldToolAction->SetAgentComp(this);

	auto BuyGoldToolAction = NewObject<UBuyGoldToolAction>();
	BuyGoldToolAction->SetAgentComp(this);

	auto AttackFinishLevelBlockAction = NewObject<UAttackFinishLevelBlockAction>();
	AttackFinishLevelBlockAction->SetAgentComp(this);

	auto GoToFinishLevelBlockAction = NewObject<UGoToFinishLevelBlockAction>();
	GoToFinishLevelBlockAction->SetAgentComp(this);

	auto EquipPlatinToolAction = NewObject<UEquipPlatinToolAction>();
	EquipPlatinToolAction->SetAgentComp(this);

	auto BuyPlatinToolAction = NewObject<UBuyPlatinToolAction>();
	BuyPlatinToolAction->SetAgentComp(this);

	auto GoToClickAction = NewObject<UGoToClickAction>();
	GoToClickAction->SetAgentComp(this);

	Actions_.Add(IdleAction);
	Actions_.Add(AttackBlueBlockAction);
	Actions_.Add(GoToBlueBlock);
	Actions_.Add(EquipAnyToolAction);
	Actions_.Add(CollectToolAction);
	Actions_.Add(GoToBlueToolAction);
	Actions_.Add(AttackPurpleBlockAction);
	Actions_.Add(GoToPurpleBlockAction);
	Actions_.Add(EquipPurpleToolAction);
	Actions_.Add(CollectPurpleToolAction);
	Actions_.Add(GoToPurpleToolAction);
	Actions_.Add(BuyPurpleToolAction);
	Actions_.Add(AttackGoldBlockAction);
	Actions_.Add(GoToGoldBlockAction);
	Actions_.Add(EquipGoldToolAction);
	Actions_.Add(CollectGoldToolAction);
	Actions_.Add(GoToGoldToolAction);
	Actions_.Add(BuyGoldToolAction);
	Actions_.Add(AttackFinishLevelBlockAction);
	Actions_.Add(GoToFinishLevelBlockAction);
	Actions_.Add(EquipPlatinToolAction);
	Actions_.Add(BuyPlatinToolAction);
	Actions_.Add(GoToClickAction);


}


// Called every frame
void UAgentComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	//Tick from the general Component behavior
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	
	// Create a string with the dynamic value
	FString DebugMessage = TEXT("Current Goal: ") + CurrentPrusuedGoalName_;

	// Location to draw the debug string in the world (this example uses the actor's location)
	FVector Location = GetOwner()->GetActorLocation() + FVector(0, 0, 210); // Draw above the actor

	// Draw the debug string
	DrawDebugString(GetWorld(), Location, DebugMessage, nullptr, FColor::Magenta, 0.0f, true);

	if (IsValid(CurrentAction_)) {
		Location = GetOwner()->GetActorLocation() + FVector(0, 0, 140);
		DrawDebugString(GetWorld(), Location, TEXT("Current Action: ")+CurrentAction_->GetName(), nullptr, FColor::Cyan, 0.0f, true);
	}

	if (!CurrentPlan_.IsEmpty()) {
		
		float ZValue = 50.0f;
		float XValue = -270.0f;
		Location = GetOwner()->GetActorLocation() + FVector(-30, XValue, ZValue);
		DrawDebugString(GetWorld(), Location, TEXT("Current Plan: "), nullptr, FColor::Green, 0.0f, true);
		for (auto Action : CurrentPlan_) {
			ZValue -= 25.0f;
			Location = GetOwner()->GetActorLocation() + FVector(-30, XValue, ZValue);
			DrawDebugString(GetWorld(), Location, Action->GetName(), nullptr, FColor::Green, 0.0f, true);
		}
	}


	if (CurrentPlan_.IsEmpty() && !IsBusy_) {

		//set the goal priorities and change facts

		//set the Goal priorities from their priority rule
		for (const auto Goal : Goals_) {
			for (const auto Rules : GoalPriorityRules_) {
				if (Goal->GetName() == Rules.Key && Goal->GetPriority() != Rules.Value) {
					
						Goal->SetPriority(Rules.Value);
				}	
			}
		}

		//changing facts if agent is not in position of the nearest block  and if block not reachable lower priority of that goal
		auto CustomAIChar = Cast<ACustomAICharacter>(GetOwner());
		bool BlueNotReachable = false;
		bool PurpleNotReachable = false; 
		bool GoldNotReachable = false;
		bool PlatinNotReachable = false;

		auto PlatinTool = NewObject<APlatinTool>();
		auto PurpleTool = NewObject<APurpleTool>();
		auto GoldTool = NewObject<AGoldTool>();

		if (IsValid(WorldMemory_->GetNearestBlueBlock())) {
			WorldMemory_->GetWorldState()["BlueBlockDestroyed"] = false;
			BlueNotReachable = false;
			auto GoToPos = WorldMemory_->GetNearestBlueBlock()->GetActorLocation();
			GoToPos.X -= 70;
			float DistanceSquared = FVector::DistSquared(GoToPos, GetOwner()->GetActorLocation());
			if (DistanceSquared > FMath::Square(70)) {
				WorldMemory_->GetWorldState()["InBlueBlockPos"] = false;
			}
			auto World = GetOwner()->GetWorld();
			UNavigationSystemV1* NavSystem = FNavigationSystem::GetCurrent<UNavigationSystemV1>(World);

			float PathCost = FLT_MAX;
			auto PathExists = NavSystem->GetPathCost(GetOwner()->GetActorLocation(), GoToPos, PathCost, nullptr);
			if (PathExists != ENavigationQueryResult::Success || PathCost >= FLT_MAX) {
				BlueNotReachable = true;
			}
			else if (!WorldMemory_->GetWorldState()["HasTool"] && !WorldMemory_->GetNearestBlueTool()) {
				BlueNotReachable = true;

			}

		}
		else {
			BlueNotReachable = true;
		}

		if (IsValid(WorldMemory_->GetNearestPurpleBlock())) {
			WorldMemory_->GetWorldState()["PurpleBlockDestroyed"] = false;

			auto GoToPos = WorldMemory_->GetNearestPurpleBlock()->GetActorLocation();
			GoToPos.X -= 70;
			float DistanceSquared = FVector::DistSquared(GoToPos, GetOwner()->GetActorLocation());
			if (DistanceSquared > FMath::Square(70)) {
				WorldMemory_->GetWorldState()["InPurpleBlockPos"] = false;
			}
			auto World = GetOwner()->GetWorld();
			UNavigationSystemV1* NavSystem = FNavigationSystem::GetCurrent<UNavigationSystemV1>(World);

			float PathCost = FLT_MAX;
			auto PathExists = NavSystem->GetPathCost(GetOwner()->GetActorLocation(), GoToPos, PathCost, nullptr);
			if (PathExists != ENavigationQueryResult::Success || PathCost >= FLT_MAX) {
				PurpleNotReachable = true;
			}
			else if (!WorldMemory_->GetWorldState()["HasPurpleTool"] && (CustomAIChar->GetBalance() < PurpleTool->GetShopCost()
				|| !CustomAIChar->CanBeAddedToInventory(PurpleTool->GetInventorySpace()))) {
				PurpleNotReachable = true;
			}

		}
		else {
			PurpleNotReachable = true;
		}

		if (IsValid(WorldMemory_->GetNearestGoldBlock())) {
			WorldMemory_->GetWorldState()["GoldBlockDestroyed"] = false;
			auto GoToPos = WorldMemory_->GetNearestGoldBlock()->GetActorLocation();
			GoToPos.X -= 70;
			float DistanceSquared = FVector::DistSquared(GoToPos, GetOwner()->GetActorLocation());
			if (DistanceSquared > FMath::Square(70)) {
				WorldMemory_->GetWorldState()["InGoldBlockPos"] = false;
			}
			auto World = GetOwner()->GetWorld();
			UNavigationSystemV1* NavSystem = FNavigationSystem::GetCurrent<UNavigationSystemV1>(World);

			float PathCost = FLT_MAX;
			auto PathExists = NavSystem->GetPathCost(GetOwner()->GetActorLocation(), GoToPos, PathCost, nullptr);
			if (PathExists != ENavigationQueryResult::Success || PathCost >= FLT_MAX) {
				GoldNotReachable = true;
			}
			else if (!WorldMemory_->GetWorldState()["HasGoldTool"] && (CustomAIChar->GetBalance() < GoldTool->GetShopCost()
				|| !CustomAIChar->CanBeAddedToInventory(GoldTool->GetInventorySpace()))){
				GoldNotReachable = true;

			}
		}
		else {
			GoldNotReachable = true;
		}

		if (IsValid(WorldMemory_->GetFinishLevelBlock())) {
			//WorldMemory_->GetWorldState()["GoldBlockDestroyed"] = false;
			auto GoToPos = WorldMemory_->GetFinishLevelBlock()->GetActorLocation();
			GoToPos.X -= 70;
			//GoToPos.Y -= 25;
			float DistanceSquared = FVector::DistSquared(GoToPos, GetOwner()->GetActorLocation());
			if (DistanceSquared > FMath::Square(70)) {
				WorldMemory_->GetWorldState()["InFinishLevelBlockPos"] = false;
			}
			auto World = GetOwner()->GetWorld();
			UNavigationSystemV1* NavSystem = FNavigationSystem::GetCurrent<UNavigationSystemV1>(World);

			float PathCost = FLT_MAX;
			auto PathExists = NavSystem->GetPathCost(GetOwner()->GetActorLocation(), GoToPos, PathCost, nullptr);
			if (PathExists != ENavigationQueryResult::Success || PathCost >= FLT_MAX) {
				PlatinNotReachable = true;
			}
			else if (!WorldMemory_->GetWorldState()["HasPlatinTool"] && (CustomAIChar->GetBalance() < PlatinTool->GetShopCost() 
				|| !CustomAIChar->CanBeAddedToInventory(PlatinTool->GetInventorySpace()))) {
				PlatinNotReachable = true;

			}
		}
		else {
			PlatinNotReachable = true;
		}

		//when there is no nearest block of any type idle behavior should be a high priority
		//if (!IsValid(WorldMemory_->GetNearestBlueBlock()) && !IsValid(WorldMemory_->GetNearestPurpleBlock()) && !IsValid(WorldMemory_->GetNearestGoldBlock())) {
		if(BlueNotReachable && PurpleNotReachable && GoldNotReachable) {
			for (auto Goal : Goals_) {
				
				if (Goal->GetName() == "NotIdle") {
					Goal->SetPriority(5);
					WorldMemory_->GetWorldState()["NotIdle"] = false;
					GEngine->AddOnScreenDebugMessage(-1, 2.5f, FColor::Red, TEXT("No Blocks can destroyed, World fact NotIdle changes to true!"));

				}
			}
		}


		//if the agent has enough credits to buy a platin tool or owns it already
		//it should priotize destroying the Finish level block
		//only if the location of it is known
		if (IsValid(CustomAIChar) && ((CustomAIChar->GetBalance() >= PlatinTool->GetShopCost())
			|| WorldMemory_->GetWorldState()["HasPlatinTool"])
			&& IsValid(WorldMemory_->GetFinishLevelBlock())) {
			for (auto Goal : Goals_) {

				if (Goal->GetName() == "FinishLevelBlockDestroyed") {
					Goal->SetPriority(6);
				}
			}
		}

		//if there is a click position the click goal should be followed
		if (WorldMemory_->GetClickPosSet()) {
			for (auto Goal : Goals_) {

				if (Goal->GetName() == "InClickPos") {
					Goal->SetPriority(7);
				}
			}
		}

		//check and update failed goals
		for (int32 i = FailedGoals_.Num() - 1; i >= 0; --i ) {
			if ((FailedGoals_[i]->GetName() == "BlueBlockDestroyed")) {
				if (BlueNotReachable) {
					FailedGoals_[i]->SetPriority(-1);
				}
				else {
					FailedGoals_.RemoveAt(i, 1, false);
				}
			}
			else if ((FailedGoals_[i]->GetName() == "PurpleBlockDestroyed")) {
				if (PurpleNotReachable) {
					FailedGoals_[i]->SetPriority(-1);
				}
				else {
					FailedGoals_.RemoveAt(i, 1, false);
				}
			}
			else if ((FailedGoals_[i]->GetName() == "GoldBlockDestroyed")) {
				if (GoldNotReachable) {
					FailedGoals_[i]->SetPriority(-1);
				}
				else {
					FailedGoals_.RemoveAt(i, 1, false);
				}
			}
			else if ((FailedGoals_[i]->GetName() == "FinishLevelBlockDestroyed")) {
				if (PlatinNotReachable) {
					FailedGoals_[i]->SetPriority(-1);
				}
				else {
					FailedGoals_.RemoveAt(i, 1, false);
				}
			}
		}


		//Find all goals that are unsatisfied with the current WorldState
		TArray<UGoal*> UnsatisfiedGoals;

		for (const auto goal : Goals_) {

			for (const auto& worldEntry : WorldMemory_->GetWorldState()) {
				if (goal && &worldEntry) {
					if ((goal->GetName() == worldEntry.Key) && (goal->GetValue() != worldEntry.Value)) {

						UnsatisfiedGoals.Add(goal);

					}
				}
			}

		}

		if (!UnsatisfiedGoals.IsEmpty()) {
			//search unsatisfied goal with the highest priority
			UGoal* HighPrioGoal = nullptr;
			int HighestPrio = -1;

			for (const auto goal : UnsatisfiedGoals) {
				if (HighestPrio < goal->GetPriority()) {
					HighestPrio = goal->GetPriority();
					HighPrioGoal = goal;
				}
			}

			if (HighPrioGoal) {
				CurrentPrusuedGoalName_ = HighPrioGoal->GetName();
				Planner_->RequestPlan(CurrentPrusuedGoalName_);
				if (Planner_->IsPlanAvailable) {
					CurrentPlan_ = Planner_->ReturnPlan();
					CurrentActionInd_ = 0;
					GEngine->AddOnScreenDebugMessage(-1, 2.5f, FColor::Turquoise, 
						TEXT("Plan found to satisfy ")+ CurrentPrusuedGoalName_);
				}
				else {
					FailedGoals_.Add(HighPrioGoal);
					GEngine->AddOnScreenDebugMessage(-1, 2.5f, FColor::Turquoise, 
						TEXT("No Plan to satisfy ") + CurrentPrusuedGoalName_);
				}
			}
		}
	}
	else if (!CurrentPlan_.IsEmpty() && !IsBusy_) {

		ExecutePlan();

	}


	
}

void UAgentComponent::ExecutePlan()
{
	
	if ((CurrentActionInd_ >0 )&& IsValid(CurrentAction_)) {
			CurrentAction_->Finished();
	}

	if ((CurrentActionInd_ >= 0) && (CurrentActionInd_ < CurrentPlan_.Num())) {
		CurrentAction_ = CurrentPlan_[CurrentActionInd_];
		if (CurrentAction_->CanBeExecuted()) {
			IsBusy_ = true;
			CurrentActionInd_++;
			CurrentAction_->Execute();

		}
		else {
			//replan logic
			GEngine->AddOnScreenDebugMessage(-1, 2.5f, FColor::Turquoise, TEXT("Replanning because current action ") + CurrentAction_->GetName() + TEXT(" couldn't be executed"));
			Replan();

		}

		if (IsBusy_ && CurrentAction_->GetSuccessStatus() != Status::SUCCESS) {
			//replan logic
			GEngine->AddOnScreenDebugMessage(-1, 2.5f, FColor::Turquoise, TEXT("Replanning because ") + CurrentAction_->GetName() + TEXT("'s execution failed"));
			Replan();
		}
	}
	else {
		if (IsValid(Planner_)) {
			Planner_->IsPlanAvailable = false;
			Planner_->ResetPlan();
		}
		CurrentPlan_.Empty();
		CurrentAction_ = nullptr;
		CurrentActionInd_ = -1;
	}
	

}

void UAgentComponent::Replan()
{
	CurrentPlan_.Empty();
	Planner_->IsPlanAvailable = false;
	Planner_->ResetPlan();
	Planner_->Replan(CurrentAction_);
	if (!Planner_->IsPlanAvailable) {
		//After unsuccessful replan attempt reset and restart whole logic
		GEngine->AddOnScreenDebugMessage(-1, 2.5f, FColor::Turquoise, 
			TEXT("Replanning attempt failed, trying to prusue another goal"));
		IsBusy_ = false;
		ResetPlan();
		auto AIPawn = Cast<APawn>(GetOwner());
		auto AIController = Cast<AAIController>(AIPawn->GetController());
		auto BrainComp = AIController->GetBrainComponent();
		BrainComp->RestartLogic();
		for (auto Goal : Goals_) {
			if (Goal->GetName() == CurrentPrusuedGoalName_) {
				FailedGoals_.Add(Goal);
			}
		}
	}
	else {
		CurrentPlan_ = Planner_->ReturnPlan();	
		CurrentAction_ = nullptr;
		CurrentActionInd_ = 0;
	}

}

TArray<UAction*>& UAgentComponent::GetActions()
{
	return Actions_;
}

TArray<UGoal*>& UAgentComponent::GetGoals()
{
	return Goals_;
}

bool UAgentComponent::GetIsBusy()
{
	return IsBusy_;
}

void UAgentComponent::SetIsBusy(bool IsBusy)
{
	IsBusy_ = IsBusy;
}

AWorldMemory* UAgentComponent::GetWorldMemory()
{
	return WorldMemory_;
}

void UAgentComponent::SetWorldMemory(AWorldMemory* WorldMemory)
{
	if (WorldMemory) {
		WorldMemory_ = WorldMemory;
	}
}

FString UAgentComponent::GetCurrentPrusuedGoalName()
{
	return CurrentPrusuedGoalName_;
}

void UAgentComponent::SetSimulationStop()
{
	SimulationStop_ = true;
}

TMap<FString, int>& UAgentComponent::GetGoalPriorityRules()
{
	return GoalPriorityRules_;
}

void UAgentComponent::ChangeGoalPriorityRule(FString RuleName, int32 Value)
{
	GoalPriorityRules_[RuleName] = Value;
}

void UAgentComponent::ResetPlan()
{
	if (IsValid(Planner_)) {
		Planner_->IsPlanAvailable = false;
		Planner_->ResetPlan();
	}
	CurrentPlan_.Empty();
	if (IsValid(CurrentAction_)) {
		CurrentAction_->Finished();
	}
	CurrentAction_ = nullptr;
	CurrentActionInd_ = -1;
	

}


