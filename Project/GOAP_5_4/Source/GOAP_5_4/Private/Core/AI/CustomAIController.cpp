// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/AI/CustomAIController.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"

ACustomAIController::ACustomAIController()
{
	BehaviorTreeComponent = CreateDefaultSubobject<UBehaviorTreeComponent>(TEXT("Behavoir Tree Component"));
	BlackboardComponent = CreateDefaultSubobject<UBlackboardComponent>(TEXT("Blackboard Component"));
}

void ACustomAIController::BeginPlay()
{
	Super::BeginPlay();

	//running the behavior tree
	if (IsValid(BehaviorTree.Get())) {
		RunBehaviorTree(BehaviorTree.Get());
		BehaviorTreeComponent->StartTree(*BehaviorTree.Get());
	}
}

void ACustomAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	//initializes the blackboard that is in use of the behavior tree
	if (IsValid(Blackboard.Get()) && IsValid(BehaviorTree.Get())) {
		Blackboard->InitializeBlackboard(*BehaviorTree.Get()->BlackboardAsset.Get());
	}
}
