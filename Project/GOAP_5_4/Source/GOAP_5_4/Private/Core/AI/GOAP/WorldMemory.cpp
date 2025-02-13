// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/AI/GOAP/WorldMemory.h"
#include "Core/AI/CustomAICharacter.h"
#include "Core/AI/GOAP/AgentComponent.h"
#include "Core/GameBlocks/BlueBlock.h"
#include "Core/ItemTools/Tool.h"
#include <AIController.h>
#include <Core/ItemTools/PlatinTool.h>
#include <GOAP_5_4/GOAP_5_4Character.h>

// Sets default values
AWorldMemory::AWorldMemory()
{
	FinishLevelBlock_ = nullptr;
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	WorldState_.Add("BlueBlockDestroyed", false);
	WorldState_.Add("InBlueBlockPos", false);
	WorldState_.Add("ToolEquipped", false);
	WorldState_.Add("HasTool", false);
	WorldState_.Add("ObtainedBlueTool", false);

	WorldState_.Add("NotIdle", false);

	WorldState_.Add("PurpleBlockDestroyed", false);
	WorldState_.Add("InPurpleBlockPos", false);
	WorldState_.Add("PurpleToolOrHigherEquipped", false);
	WorldState_.Add("HasPurpleTool", false);
	WorldState_.Add("ObtainedPurpleTool", false);

	WorldState_.Add("GoldBlockDestroyed", false);
	WorldState_.Add("InGoldBlockPos", false);
	WorldState_.Add("GoldToolOrHigherEquipped", false);
	WorldState_.Add("HasGoldTool", false);
	WorldState_.Add("ObtainedGoldTool", false);

	WorldState_.Add("FinishLevelBlockDestroyed", false);
	WorldState_.Add("InFinishLevelBlockPos", false);
	WorldState_.Add("PlatinToolEquipped", false);
	WorldState_.Add("HasPlatinTool", false);

	WorldState_.Add("InClickPos", false);
	WorldState_.Add("ClickPosExists", false);

}


// Called when the game starts or when spawned
void AWorldMemory::BeginPlay()
{
	Super::BeginPlay();
	

}

// Called every frame
void AWorldMemory::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	if (CustomAIChar_) {
		
		
		UpdateNearestBlueBlock(CustomAIChar_);
		UpdateNearestBlueTool(CustomAIChar_);
		UpdateNearestPurpleTool(CustomAIChar_);
		UpdateNearestGoldTool(CustomAIChar_);
		UpdateNearestPurpleBlock(CustomAIChar_);
		UpdateNearestGoldBlock(CustomAIChar_);
		UpdateFinishLevelBlock(CustomAIChar_);

		//change facts based on the equipped tool
		if (IsValid(CustomAIChar_->GetEquippedTool())) {
			WorldState_["ToolEquipped"] = true;
			
	
			if (CustomAIChar_->GetEquippedTool()->GetToolName() == "PurpleTool") {
				WorldState_["PurpleToolOrHigherEquipped"] = true;
				WorldState_["GoldToolOrHigherEquipped"] = false;
				WorldState_["PlatinToolEquipped"] = false;
			}
	
			if (CustomAIChar_->GetEquippedTool()->GetToolName() == "GoldTool") {
				WorldState_["PurpleToolOrHigherEquipped"] = true;
				WorldState_["GoldToolOrHigherEquipped"] = true;
				WorldState_["PlatinToolEquipped"] = false;

			}
	
			if (CustomAIChar_->GetEquippedTool()->GetToolName() == "PlatinTool") {
				WorldState_["PurpleToolOrHigherEquipped"] = true;
				WorldState_["GoldToolOrHigherEquipped"] = true;
				WorldState_["PlatinToolEquipped"] = true;
			}
		}
		else {
			WorldState_["ToolEquipped"] = false;
			WorldState_["PurpleToolOrHigherEquipped"] = false;
			WorldState_["GoldToolOrHigherEquipped"] = false;
			WorldState_["PlatinToolEquipped"] = false;
		}

		//change facts about certain tools that the AIchar has
		if (!CustomAIChar_->GetToolInventory().IsEmpty()) {
			WorldState_["HasTool"] = true;

			int CountPurple = 0;
			int CountGold = 0;
			int CountPlatin = 0;

			for (auto Tool : CustomAIChar_->GetToolInventory()) {
				if (Tool->GetName().Contains(FString("PurpleTool"))) {
					CountPurple++;
				}
				if (Tool->GetName().Contains(FString("GoldTool"))) {
					CountGold++;
				}
				if (Tool->GetName().Contains(FString("PlatinTool"))) {
					CountPlatin++;
				}
			}

			if (CountPurple > 0) {
				WorldState_["HasPurpleTool"] = true;
			}
			else {
				WorldState_["HasPurpleTool"] = false;
			}

			if (CountGold > 0) {
				WorldState_["HasGoldTool"] = true;
			}
			else {
				WorldState_["HasGoldTool"] = false;
			}

			if (CountPlatin > 0) {
				WorldState_["HasPlatinTool"] = true;
			}
			else {
				WorldState_["HasPlatinTool"] = false;
			}

		}
		else if (!AgentComponent_->GetIsBusy()) {
			WorldState_["HasTool"] = false;
			WorldState_["HasPurpleTool"] = false;
			WorldState_["HasGoldTool"] = false;
			WorldState_["HasPlatinTool"] = false;
			WorldState_["ObtainedBlueTool"] = false;
			WorldState_["ObtainedPurpleTool"] = false;
			WorldState_["ObtainedGoldTool"] = false;

		}

		


	}

	//change facts about the click position based from the player
	auto Character = GetWorld()->GetFirstPlayerController()->GetCharacter();
	auto CustomPlayerCharacter = Cast<AGOAP_5_4Character>(Character);
	if (IsValid(CustomPlayerCharacter) && !CustomPlayerCharacter->TargetLocation.IsZero() 
		&& CustomPlayerCharacter->PositionSet && !ClickPosSet_) {
		
		ClickPosition_ = CustomPlayerCharacter->TargetLocation;
		ClickPosSet_ = true;
		WorldState_["InClickPos"] = false;
		WorldState_["ClickPosExists"] = true;
	}
	else if (IsValid(CustomPlayerCharacter) && CustomPlayerCharacter->TargetLocation.IsZero() 
		&& !CustomPlayerCharacter->PositionSet && ClickPosSet_) {
		ClickPosition_ = FVector(0.0f, 0.0f, 0.0f);
		ClickPosSet_ = false;
		WorldState_["ClickPosExists"] = false;
	}

}


void AWorldMemory::UpdateFinishLevelBlock(ACustomAICharacter* CustomAIChar)
{
	auto CharLoc = CustomAIChar->GetActorLocation();

	AFinishLevelBlock* NearestBlock = nullptr;

	for (const auto Block : CustomAIChar->GetSensorOverlappedBlocks()) {

		auto Current = Cast<AFinishLevelBlock>(Block);
		if (Current) {
			FinishLevelBlock_ = Current;
		}

	}
}

void AWorldMemory::UpdateNearestGoldBlock(ACustomAICharacter* CustomAIChar)
{
	auto CharLoc = CustomAIChar->GetActorLocation();

	AGoldBlock* NearestBlock = nullptr;
	float LowestDistance = INFINITY;

	for (const auto Block : CustomAIChar->GetSensorOverlappedBlocks()) {

		auto Current = Cast<AGoldBlock>(Block);
		if (Current) {

			auto Distance = FVector::Dist(CharLoc, Current->GetActorLocation());

			if (Distance < LowestDistance) {
				LowestDistance = Distance;
				NearestBlock = Current;
			}

		}

	}

	if (NearestBlock) {
		NearestGoldBlock_ = NearestBlock;
	}
}

void AWorldMemory::UpdateNearestPurpleBlock(ACustomAICharacter* CustomAIChar)
{
	auto CharLoc = CustomAIChar->GetActorLocation();

	APurpleBlock* NearestBlock = nullptr;
	float LowestDistance = INFINITY;

	for (const auto Block : CustomAIChar->GetSensorOverlappedBlocks()) {

		auto Current = Cast<APurpleBlock>(Block);
		if (Current) {

			auto Distance = FVector::Dist(CharLoc, Current->GetActorLocation());

			if (Distance < LowestDistance) {
				LowestDistance = Distance;
				NearestBlock = Current;
			}

		}

	}

	if (NearestBlock) {
		NearestPurpleBlock_ = NearestBlock;
	}
}

void AWorldMemory::UpdateNearestGoldTool(ACustomAICharacter* CustomAIChar)
{
	auto CharLoc = CustomAIChar->GetActorLocation();

	float LowestDistance = INFINITY;
	for (const auto Tool : CustomAIChar->GetSensorOverlappedTools()) {
		auto Current = Cast<AGoldTool>(Tool);
		if (Current) {
			auto Distance = FVector::Dist(CharLoc, Current->GetActorLocation());
			if (Distance < LowestDistance) {
				LowestDistance = Distance;
				NearestGoldTool_ = Current;
			}
		}
	}
}

void AWorldMemory::UpdateNearestPurpleTool(ACustomAICharacter* CustomAIChar)
{
	auto CharLoc = CustomAIChar->GetActorLocation();

	float LowestDistance = INFINITY;
	for (const auto Tool : CustomAIChar->GetSensorOverlappedTools()) {
		auto Current = Cast<APurpleTool>(Tool);
		if (Current) {
			auto Distance = FVector::Dist(CharLoc, Current->GetActorLocation());
			if (Distance < LowestDistance) {
				LowestDistance = Distance;
				NearestPurpleTool_ = Current;
			}
		}
	}
}

void AWorldMemory::UpdateNearestBlueTool(ACustomAICharacter* CustomAIChar)
{
	auto CharLoc = CustomAIChar->GetActorLocation();

	float LowestDistance = INFINITY;
	for (const auto Tool : CustomAIChar->GetSensorOverlappedTools()) {
		auto Current = Cast<ABlueTool>(Tool);
		if (Current) {
			auto Distance = FVector::Dist(CharLoc, Tool->GetActorLocation());
			if (Distance < LowestDistance) {
				LowestDistance = Distance;
				NearestBlueTool_ = Current;
			}
		}
	}
}

void AWorldMemory::UpdateNearestBlueBlock(ACustomAICharacter* CustomAIChar)
{
	auto CharLoc = CustomAIChar->GetActorLocation();
	ABlueBlock* NearestBlock = nullptr;
	float LowestDistance = INFINITY;

	for (const auto Block : CustomAIChar->GetSensorOverlappedBlocks()) {
		auto Current = Cast<ABlueBlock>(Block);
		if (Current) {

			auto Distance = FVector::Dist(CharLoc, Current->GetActorLocation());
			if (Distance < LowestDistance) {
				LowestDistance = Distance;
				NearestBlock = Current;
			}
		}
	}
	if (NearestBlock) {
		NearestBlueBlock_ = NearestBlock;
	}
}

TMap<FString, bool>& AWorldMemory::GetWorldState()
{
	return WorldState_;
}


ABlueBlock* AWorldMemory::GetNearestBlueBlock()
{
	return NearestBlueBlock_;
}

ABlueTool* AWorldMemory::GetNearestBlueTool()
{
	return NearestBlueTool_;
}

APurpleTool* AWorldMemory::GetNearestPurpleTool()
{
	return NearestPurpleTool_;
}

APurpleBlock* AWorldMemory::GetNearestPurpleBlock()
{
	return NearestPurpleBlock_;
}

AGoldBlock* AWorldMemory::GetNearestGoldBlock()
{
	return NearestGoldBlock_;
}

AGoldTool* AWorldMemory::GetNearestGoldTool()
{
	return NearestGoldTool_;
}

AFinishLevelBlock* AWorldMemory::GetFinishLevelBlock()
{
	return FinishLevelBlock_;
}


void AWorldMemory::ResetNearestBlueBlock()
{
	NearestBlueBlock_ = nullptr;
}

void AWorldMemory::ResetNearestPurpleBlock()
{
	NearestPurpleBlock_ = nullptr;
}

void AWorldMemory::ResetNearestGoldBlock()
{
	NearestGoldBlock_ = nullptr;
}

ACustomAICharacter* AWorldMemory::GetCustomAIChar()
{
	return CustomAIChar_;
}

void AWorldMemory::SetCustomAIChar(ACustomAICharacter* AIChar)
{
	CustomAIChar_ = AIChar;
}

FVector AWorldMemory::GetClickPosition()
{
	return ClickPosition_;
}

bool AWorldMemory::GetClickPosSet()
{
	return ClickPosSet_;
}

UAgentComponent* AWorldMemory::GetAgentComponent()
{
	return AgentComponent_;
}

void AWorldMemory::SetAgentComponent(UAgentComponent* AgentComp)
{
	AgentComponent_ = AgentComp;
}

