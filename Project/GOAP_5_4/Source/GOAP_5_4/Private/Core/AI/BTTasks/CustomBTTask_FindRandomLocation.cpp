// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/AI/BTTasks/CustomBTTask_FindRandomLocation.h"
#include "AIController.h"
#include "NavigationSystem.h"
#include "BehaviorTree/BlackboardComponent.h"

UCustomBTTask_FindRandomLocation::UCustomBTTask_FindRandomLocation()
{
	NodeName = TEXT("Find Random Location");

	//accept only vectors
	BlackboardKey.AddVectorFilter(this, GET_MEMBER_NAME_CHECKED(UCustomBTTask_FindRandomLocation, BlackboardKey));
}

EBTNodeResult::Type UCustomBTTask_FindRandomLocation::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	FNavLocation Location{};

	//Get AI Pawn
	AAIController* AIController = OwnerComp.GetAIOwner();
	APawn* AIPawn = AIController->GetPawn();

	//Get Pawn origin
	const FVector Origin = AIPawn->GetActorLocation();

	//Obtain the NavSystem and find a random location
	const UNavigationSystemV1* NavSystem = UNavigationSystemV1::GetCurrent(GetWorld());
	if (IsValid(NavSystem) && NavSystem->GetRandomPointInNavigableRadius(Origin, SearchRadius, Location)) {
		AIController->GetBlackboardComponent()->SetValueAsVector(BlackboardKey.SelectedKeyName, Location.Location);
	}

	//Signal the BehavoirTreeComponenet that the task finished with a Success!
	FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);

	return EBTNodeResult::Succeeded;
}

FString UCustomBTTask_FindRandomLocation::GetStaticDescription() const
{
	return FString::Printf(TEXT("Vector: %s"), *BlackboardKey.SelectedKeyName.ToString());
}
