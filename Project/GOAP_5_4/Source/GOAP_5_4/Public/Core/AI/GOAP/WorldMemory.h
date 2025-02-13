// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include <AIController.h>
#include "Core/GameBlocks/BlueBlock.h"
#include "Core/GameBlocks/PurpleBlock.h"
#include "Core/GameBlocks/GoldBlock.h"
#include <Core/ItemTools/PurpleTool.h>
#include <Core/ItemTools/GoldTool.h>
#include <Core/GameBlocks/FinishLevelBlock.h>
#include <Core/ItemTools/BlueTool.h>
#include "WorldMemory.generated.h"

class UAgentComponent;

/**
* Class that contains and keeps track of the worldfacts and nearest objects
* Worldfacts can be changed inside this class or outside this class(actions, agentcomponent)
*/
UCLASS()
class GOAP_5_4_API AWorldMemory : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWorldMemory();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//update the nearest FinishLevelBlock
	void UpdateFinishLevelBlock(ACustomAICharacter* CustomAIChar);

	//update the nearest GoldBlock
	void UpdateNearestGoldBlock(ACustomAICharacter* CustomAIChar);

	//update the nearest PurpleBlock
	void UpdateNearestPurpleBlock(ACustomAICharacter* CustomAIChar);

	//update the nearest GoldTool
	void UpdateNearestGoldTool(ACustomAICharacter* CustomAIChar);
	
	//update the nearest PurpleTool
	void UpdateNearestPurpleTool(ACustomAICharacter* CustomAIChar);

	//update the nearest BlueTool
	void UpdateNearestBlueTool(ACustomAICharacter* CustomAIChar);

	//update the nearest BlueBlock
	void UpdateNearestBlueBlock(ACustomAICharacter* CustomAIChar);
	
	//return the WorldState
	TMap<FString, bool>& GetWorldState();

	//returns the nearest BlueBlock
	ABlueBlock* GetNearestBlueBlock();

	//returns the nearest BlueTool
	ABlueTool* GetNearestBlueTool();

	//returns the nearest PurpleTool
	APurpleTool* GetNearestPurpleTool();

	//returns the nearest PurpleBlock
	APurpleBlock* GetNearestPurpleBlock();

	//returns the nearest GoldBlock
	AGoldBlock* GetNearestGoldBlock();

	//returns the nearest GoldTool
	AGoldTool* GetNearestGoldTool();

	//returns the nearest FinishLevelBlock
	AFinishLevelBlock* GetFinishLevelBlock();
	
	//resets the nearest BlueBlock
	void ResetNearestBlueBlock();

	//resets the nearest PurpleBlock
	void ResetNearestPurpleBlock();

	//resets the nearest GoldBlock
	void ResetNearestGoldBlock();

	//returns the CustomAICharacter assigned to the WorldMemory
	ACustomAICharacter* GetCustomAIChar();

	//sets the CustomAICharacter
	void SetCustomAIChar(ACustomAICharacter* AIChar);

	//returns the Vector-Positions of the mouse-click from the player
	FVector GetClickPosition();

	//returns with a Vector-Position set through the player exists
	bool GetClickPosSet();

	//returns the AgentComponent which uses this WorldMemory
	UAgentComponent* GetAgentComponent();

	//sets the AgentComponent
	void SetAgentComponent(UAgentComponent* AgentComp);

private:

	UPROPERTY()
	ACustomAICharacter* CustomAIChar_;

	bool ClickPosSet_;

	FVector ClickPosition_;

	UPROPERTY()
	UAgentComponent* AgentComponent_;

	TMap<FString, bool> WorldState_;
	UPROPERTY()

	ABlueBlock* NearestBlueBlock_;
	UPROPERTY()

	ABlueTool* NearestBlueTool_;
	UPROPERTY()

	APurpleTool* NearestPurpleTool_;
	UPROPERTY()

	APurpleBlock* NearestPurpleBlock_;
	UPROPERTY()

	AGoldBlock* NearestGoldBlock_;
	UPROPERTY()

	AGoldTool* NearestGoldTool_;
	UPROPERTY()

	AFinishLevelBlock* FinishLevelBlock_;

};
