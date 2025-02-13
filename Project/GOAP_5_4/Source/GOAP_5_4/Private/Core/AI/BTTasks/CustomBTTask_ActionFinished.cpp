// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/AI/BTTasks/CustomBTTask_ActionFinished.h"
#include <Core/AI/CustomAIController.h>
#include <Core/AI/GOAP/AgentComponent.h>

UCustomBTTask_ActionFinished::UCustomBTTask_ActionFinished()
{
	NodeName = TEXT("Action Finished");
}

EBTNodeResult::Type UCustomBTTask_ActionFinished::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	//Get AI Pawn
	AAIController* AIController = OwnerComp.GetAIOwner();
	APawn* AIPawn = AIController->GetPawn();
	UAgentComponent* AgentComponent = AIPawn->FindComponentByClass<UAgentComponent>();

	if (IsValid(AgentComponent)) {
		AgentComponent->SetIsBusy(false);
	}

	//Signal the BehavoirTreeComponenet that the task finished with a Success
	FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);

	return EBTNodeResult::Succeeded;
}

FString UCustomBTTask_ActionFinished::GetStaticDescription() const
{
	return FString("Sets IsBusy in the AgentComponent for GOAP");
}
