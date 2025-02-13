// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "CustomBTTask_ActionFinished.generated.h"

/**
 * BTTask for setting the IsBusy Variable in the AgenComponent for GOAP
 * While the behavior of an Action is executed on the BehaviorTree the next Action to execute for the planner in the plan has to wait
 */
UCLASS()
class GOAP_5_4_API UCustomBTTask_ActionFinished : public UBTTask_BlackboardBase
{
	GENERATED_BODY()

public:
	UCustomBTTask_ActionFinished();

private:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)override;

	virtual FString GetStaticDescription() const override;
	
};
