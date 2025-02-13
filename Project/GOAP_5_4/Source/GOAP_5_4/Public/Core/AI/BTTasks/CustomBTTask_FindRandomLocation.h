// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "CustomBTTask_FindRandomLocation.generated.h"

/**
 * BTTask for finding a RandomLocation on a NavMesh
 * used for the behavior of the Idle action
 */
UCLASS()
class GOAP_5_4_API UCustomBTTask_FindRandomLocation : public UBTTask_BlackboardBase
{
	GENERATED_BODY()
public:
	UCustomBTTask_FindRandomLocation();

private:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)override;

	virtual FString GetStaticDescription() const override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Search", meta = (AllowPrivateAccess = true))
	float SearchRadius = 500.0f;
};
