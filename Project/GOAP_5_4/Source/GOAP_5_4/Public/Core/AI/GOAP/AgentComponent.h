// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Action.h"
#include "Goal.h"
#include "WorldMemory.h"
#include "AgentComponent.generated.h"



/*Agent for the Planning process, that pursue goals and execute Actions provided from the planner.*/
class UPlanner;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class GOAP_5_4_API UAgentComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UAgentComponent();




protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	//runs the currentPlan and executes the current action
	void ExecutePlan();

	//tries to replan or abort current plan
	void Replan();

	//returns the array of the action the AgentComponent has access to
	TArray<UAction*>& GetActions();

	//returns the goals of the AgentComponent
	TArray<UGoal*>& GetGoals();

	//returns if the AgentComponent runs an action execution 
	bool GetIsBusy();

	//returns the WorldMemory attached to the AgentComponent
	AWorldMemory* GetWorldMemory();

	//sets the WorldMemory
	void SetWorldMemory(AWorldMemory*);

	//returns the name of the current prusued Goal
	FString GetCurrentPrusuedGoalName();

	//signals the simulation stopped, used when FinishLevelBlock gets destroyed
	void SetSimulationStop();
	
	//sets the IsBusy variable
	UFUNCTION(BlueprintCallable)
	void SetIsBusy(bool IsBusy);

	//returns the map of PriorityRules, which are String and int pairs
	UFUNCTION(BlueprintCallable)
	TMap<FString, int>& GetGoalPriorityRules();

	//change the priority of one existing rule
	UFUNCTION(BlueprintCallable)
	void ChangeGoalPriorityRule(FString RuleName, int32 Value);

	//resets the current plan and all members needed for the plan execution
	UFUNCTION(BlueprintCallable)
	void ResetPlan();

private:

	UPROPERTY()
	UAction* CurrentAction_;
	UPROPERTY()
	UPlanner* Planner_;

	TMap<FString, int> GoalPriorityRules_;
	UPROPERTY()
	TArray<UAction*> CurrentPlan_;

	UPROPERTY()
	TArray<UAction*> Actions_;
	UPROPERTY()
	TArray<UGoal*> Goals_;
	UPROPERTY()

	AWorldMemory* WorldMemory_;

	UPROPERTY(BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	bool SimulationStop_ = false;

	
	TArray<UGoal*> FailedGoals_;

	bool IsBusy_ = false;
	FString CurrentPrusuedGoalName_;
	int32 CurrentActionInd_;
};
