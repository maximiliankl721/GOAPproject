// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Action.generated.h"

/**
 * Class is the base class for all Actions that will be created and provides the genereal functions and members all other classes should have
 */

/* An enum that represents the states an execution of an action can take*/
UENUM(BlueprintType)
enum class Status : uint8 {
	FAILED = 0 UMETA(DisplayName = "FAILED"),
	SUCCESS = 1 UMETA(DisplayName = "SUCCESS"),
	UNKNOWN = 2 UMETA(DisplayName = "UNKNOWN"),
};


class UAgentComponent;

UCLASS()
class GOAP_5_4_API UAction : public UObject
{
	GENERATED_BODY()
	
public :

	//returns the name of the action
	virtual FString GetName();

	//returns the effect of the action with the fact name and set value
	virtual TPair<FString, bool> GetEffect();

	//returns the preconditions that
	virtual TMap<FString, bool> GetPreconditions();

	//returns the cost of the action to be executed
	virtual int32 GetCost();

	//sets the effect as a String and boolean pair
	virtual void SetEffect(FString Key, bool Value);

	//sets the preconditions as a map of string and boolean pairs
	virtual void SetPreconditions(TMap<FString, bool> Preconditions);

	//sets the cost of the action to be executed
	virtual void SetCost(int32 Cost);

	//the function which will be used as the action execution in the execution of a plan
	//needs overriding and implementation in the derived class
	virtual void Execute();

	//checks if the preconditions are met with the current worldstate
	virtual bool CanBeExecuted();

	//function will be used after the execution of an action is finished and the BehaviorTree executed all tasks
	//needs overriding and implementation in the derived class
	virtual void Finished();

	//returns the AgentComponent
	UAgentComponent* GetAgentComp();

	//sets the AgentComponent
	void SetAgentComp(UAgentComponent* AgentComp);

	//returns the SuccessStatus of the action
	Status& GetSuccessStatus();

	//sets the SuccessStatus
	void SetSuccessStatus(Status Status);

protected:

	FString Name_;
	UPROPERTY()
	Status SuccessStatus_ = Status::UNKNOWN;

	TPair<FString, bool> Effect_;
	TMap<FString, bool> Preconditions_;
	UPROPERTY()
	UAgentComponent* AgentComp_;

	int32 Cost_;

};
