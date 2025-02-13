// Fill out your copyright notice in the Description page of Project Settings.

#include "Core/AI/GOAP/Goal.h"
#include "Core/AI/GOAP/AgentComponent.h"

FString UGoal::GetName()
{
	return Name_;
}

bool UGoal::GetValue()
{
	return Value_;
}

int32 UGoal::GetPriority()
{
	return Priority_;
}

void UGoal::SetName(FString Name)
{
	Name_ = Name;
}

void UGoal::SetValue(bool Value)
{
	Value_ = Value;
}

void UGoal::SetPriority(int Num)
{
	Priority_ = Num;
}

bool UGoal::IsFulfilled()
{
	//goal is fulfilled when the similar fact in the Worldstate is the desired state
	if (AgentComponent_) {
		auto WorldMemory = AgentComponent_->GetWorldMemory();
		auto WorldStateEntryValue = WorldMemory->GetWorldState().Find(Name_);
		if (*WorldStateEntryValue == Value_) {
			return true;
		}
		else {
			return false;
		}

	}

	return false;
}

UAgentComponent* UGoal::GetAgentComponent()
{
	return AgentComponent_;
}

void UGoal::SetAgentComponent(UAgentComponent* AgentComponent)
{
	if (AgentComponent) {
		AgentComponent_ = AgentComponent;
	}


}
