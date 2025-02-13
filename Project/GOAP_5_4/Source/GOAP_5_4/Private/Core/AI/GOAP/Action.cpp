// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/AI/GOAP/Action.h"
#include "Core/AI/GOAP/AgentComponent.h"

FString UAction::GetName()
{
	return Name_;
}

TPair<FString, bool> UAction::GetEffect()
{
	return Effect_;
}

TMap<FString, bool> UAction::GetPreconditions()
{
	return Preconditions_;
}

int32 UAction::GetCost()
{
	return Cost_;
}

void UAction::SetEffect(FString Key, bool Value)
{

	Effect_ = TPair<FString, bool>(Key, Value);

}

void UAction::SetPreconditions(TMap<FString, bool> Preconditions)
{
	Preconditions_ = Preconditions;
}

void UAction::SetCost(int32 Cost)
{
	Cost_ = Cost;
}

void UAction::Execute()
{
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString("PlanExecution"));
}

bool UAction::CanBeExecuted()
{
	//if Preconditions exists and all are met it can be executed
	if (!Preconditions_.IsEmpty()) {
		auto WorldState = AgentComp_->GetWorldMemory()->GetWorldState();
		for (const auto Cond : Preconditions_) {
			for (const auto Fact : WorldState) {

				if ((Cond.Key == Fact.Key) && (Cond.Value != Fact.Value)) {
					return false;
				}

			}
		}

		return true;
	}
	else {
		return true;
	}

	
}


void UAction::Finished()
{
}

UAgentComponent* UAction::GetAgentComp()
{
	return AgentComp_;
}

void UAction::SetAgentComp(UAgentComponent* AgentComp)
{
	if (IsValid(AgentComp)) {
		AgentComp_ = AgentComp;
	}
}

Status& UAction::GetSuccessStatus()
{
	return SuccessStatus_;
}

void UAction::SetSuccessStatus(Status Status)
{
	SuccessStatus_ = Status;
}
