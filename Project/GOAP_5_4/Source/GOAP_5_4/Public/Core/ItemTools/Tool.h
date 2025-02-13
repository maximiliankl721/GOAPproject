// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include <Components/BoxComponent.h>
#include "Tool.generated.h"


class ACustomAICharacter;
/*
	Baseclass for Tools, shares the behavior and members all Tools should have
*/
UCLASS(BlueprintType)
class GOAP_5_4_API ATool : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATool();
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//add the Tool to the AIInventory, every sub-class needs to override and implement this
	virtual void AddToAIInventory(ACustomAICharacter* AIChar);

	//returns the shop cost
	UFUNCTION(BlueprintCallable)
	int GetShopCost();

	//returns the space the tool occupies in an inventory
	UFUNCTION(BlueprintCallable)
	int GetInventorySpace();

	//returns the tool name
	UFUNCTION(BlueprintCallable)
	FString GetToolName();

	//returns the damage 
	float GetDamagePerAttack();

	//returns the tool tier
	int GetTier();

	//returns the use count
	int GetUseCount();

	//increases the use count by 1
	void IncreaseUseCount();

	//returns the use limit
	int GetMaxUses();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


	int ShopCost_;
	float DamagePerAttack_;
	int InventorySpace_;
	int MaxUses_;
	int UseCount_;
	int Tier_;

	UPROPERTY(BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	FString ToolName_;


private:

	UPROPERTY(EditAnywhere, Category = "Components")
	UBoxComponent* PickupArea;

	// Function to handle overlap begin event
	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	// Function to handle overlap end event
	UFUNCTION()
	void OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
};
