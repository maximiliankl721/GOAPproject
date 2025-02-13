// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include <Components/BoxComponent.h>
#include <Core/AI/CustomAICharacter.h>
#include "Block.generated.h"

/**
* The base class of block objects, contains the general block structure
*/
UCLASS()
class GOAP_5_4_API ABlock : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABlock();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, Category = "Stats")
	float HitPoints_ = 50;
	UPROPERTY(VisibleAnywhere, Category = "Stats")
	int CreditValue_ = 5;
	UPROPERTY(VisibleAnywhere, Category = "Stats")
	int MinToolTier_ = 0;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//returns the current HP
	float GetHP();
	
	//sets the HP
	void SetHP(float HitPoints);

	//returns the credit value of the block
	int GetCreditValue();

	//sets the CreditValue
	void SetCreditValue(int CreditValue);


private:

	UPROPERTY(EditAnywhere, Category = "Components")
	UBoxComponent* HitArea_;

	UPROPERTY(EditAnywhere, Category = "Components")
	UStaticMeshComponent* Mesh_;

	UPROPERTY(VisibleAnywhere, Category = "Components")

	USceneComponent* SceneRoot_;

};
