// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include <Core/ItemTools/Tool.h>
#include <Components/ShapeComponent.h>
#include "CustomAICharacter.generated.h"


/**
* Custom AI Character class that extends the Character class from Unreal 
* and will be controlled by the CustomAIController and get the AgentComponent attached
*/
class ABlock;

UCLASS()
class GOAP_5_4_API ACustomAICharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ACustomAICharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	//returns the inventory limit
	int GetInventoryLimit();

	//checks if a given Itemsize can fit in the inventory
	UFUNCTION(BlueprintCallable)
	bool CanBeAddedToInventory(int ItemSize);

	//returns the inventory
	TArray<ATool*>& GetToolInventory();
	
	//adds Tool to the inventory
	UFUNCTION(BlueprintCallable)
	void AddToToolInventory(ATool* Tool);

	//removes Tool from the inventory
	void RemoveFromToolInventory(ATool* Tool);

	//returns the equipped Tool
	ATool* GetEquippedTool();

	//sets the EquippedTool_ to null
	void UnequipTool();

	//sets a Tool as the EquippedTool
	void SetEquippedTool(ATool* Tool);

	//returns the credit balance
	UFUNCTION(BlueprintCallable)
	float GetBalance();

	//adds to the balance
	UFUNCTION(BlueprintCallable)
	void AddBalance(float Amount);

	//substracts from the balance
	UFUNCTION(BlueprintCallable)
	void SubstractBalance(float Amount);

	//get all blocks that overlap with the sensor
	TArray<ABlock*>& GetSensorOverlappedBlocks();

	//get all tools that overlap with the sensor
	TArray<ATool*>& GetSensorOverlappedTools();

private:
	UPROPERTY()

	TArray<ABlock*> SensorOverlappedBlocks_;
	UPROPERTY()

	TArray<ATool*> SensorOverlappedTools_;
	UPROPERTY(BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TArray<ATool*> ToolInventory_;
	UPROPERTY()
	ATool* EquippedTool_;

	UPROPERTY(BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	int InventoryLimit_;

	float Balance_;

	UPROPERTY(EditAnywhere, Category = "Sensor")
	UShapeComponent* SensorSphere_;

	// Function to handle overlap begin event
	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	// Function to handle overlap end event
	UFUNCTION()
	void OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

};
