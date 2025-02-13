// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Goal.generated.h"

/**
 * Base class for all Goals that will be created and provides the genereal functions and members all other derived classes should have
 */

class UAgentComponent;

UCLASS()
class GOAP_5_4_API UGoal : public UObject
{
	GENERATED_BODY()

public:

	virtual FString GetName();
	virtual bool GetValue();
	virtual int32 GetPriority();


	virtual void SetName(FString Name);
	virtual void SetValue(bool Value);
	virtual void SetPriority(int Num);

	virtual bool IsFulfilled();

	UAgentComponent* GetAgentComponent();
	void SetAgentComponent(UAgentComponent* AgentComponent);

protected:

	UAgentComponent* AgentComponent_ = nullptr;
	FString Name_;
	bool Value_;
	int32 Priority_;

	
};
