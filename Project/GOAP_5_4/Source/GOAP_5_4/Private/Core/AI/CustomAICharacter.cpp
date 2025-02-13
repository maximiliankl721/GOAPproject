// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/AI/CustomAICharacter.h"
#include <Core/ItemTools/BlueTool.h>
#include <Components/SphereComponent.h>
#include <Core/GameBlocks/Block.h>

// Sets default values
ACustomAICharacter::ACustomAICharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Balance_ = 85.0f;
	InventoryLimit_ = 30;

	SensorSphere_ = CreateDefaultSubobject<USphereComponent>(TEXT("Sensor"));
	SensorSphere_->SetupAttachment(RootComponent);
	SensorSphere_->SetRelativeScale3D(FVector(21.0f, 21.0f, 21.0f));

	SensorSphere_->OnComponentBeginOverlap.AddDynamic(this, &ACustomAICharacter::OnOverlapBegin);
	SensorSphere_->OnComponentEndOverlap.AddDynamic(this, &ACustomAICharacter::OnOverlapEnd);

}

// Called when the game starts or when spawned
void ACustomAICharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACustomAICharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	

	
}

// Called to bind functionality to input
void ACustomAICharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

int ACustomAICharacter::GetInventoryLimit()
{
	return InventoryLimit_;
}

bool ACustomAICharacter::CanBeAddedToInventory(int ItemSize)
{
	int CurrentSpace = 0;

	for (const auto Tool : ToolInventory_) {
		CurrentSpace += Tool->GetInventorySpace();
	}

	if ((InventoryLimit_ - CurrentSpace) >= ItemSize) {
		return true;
	}

	return false;
}

TArray<ATool*>& ACustomAICharacter::GetToolInventory()
{
	return ToolInventory_;
}

void ACustomAICharacter::AddToToolInventory(ATool* Tool)
{
	if (Tool && CanBeAddedToInventory(Tool->GetInventorySpace())) {
		ToolInventory_.Add(Tool);
	}
}

void ACustomAICharacter::RemoveFromToolInventory(ATool* Tool)
{
	if (Tool) {
		ToolInventory_.Remove(Tool);
	}
}

ATool* ACustomAICharacter::GetEquippedTool()
{
	return EquippedTool_;
}

void ACustomAICharacter::UnequipTool()
{
	EquippedTool_ = nullptr;
}

void ACustomAICharacter::SetEquippedTool(ATool* Tool)
{
	EquippedTool_ = Tool;
}

float ACustomAICharacter::GetBalance()
{
	return Balance_;
}

void ACustomAICharacter::AddBalance(float Amount)
{
	Balance_ += Amount;
}

void ACustomAICharacter::SubstractBalance(float Amount)
{
	Balance_ -= Amount;
}

TArray<ABlock*>& ACustomAICharacter::GetSensorOverlappedBlocks()
{
	return SensorOverlappedBlocks_;
}

TArray<ATool*>& ACustomAICharacter::GetSensorOverlappedTools()
{
	return SensorOverlappedTools_;
}

void ACustomAICharacter::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor && (OtherActor != this) && OtherComp)
	{
		//add Block to the overlapped blocks
		auto Block = Cast<ABlock>(OtherActor);
		if (Block) {
			SensorOverlappedBlocks_.Add(Block);
			UE_LOG(LogTemp, Warning, TEXT("Sphere Overlap Begin: %s"), *OtherActor->GetName());
		}

		//add Tool to the overlapped tools
		auto Tool = Cast<ATool>(OtherActor); 
		if(Tool){
			UE_LOG(LogTemp, Warning, TEXT("Sphere Overlap Begin: %s"), *OtherActor->GetName());
			SensorOverlappedTools_.Add(Tool);
		}

	}
}

void ACustomAICharacter::OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (OtherActor && (OtherActor != this) && OtherComp)
	{
		//remove Block from the overlapped blocks
		auto Block = Cast<ABlock>(OtherActor);
		if (Block) {
			SensorOverlappedBlocks_.Remove(Block);
			UE_LOG(LogTemp, Warning, TEXT("Sphere Overlap Begin: %s"), *OtherActor->GetName());
		}
		//remove Tool from the overlapped tools
		auto Tool = Cast<ATool>(OtherActor);
		if (Tool) {
			UE_LOG(LogTemp, Warning, TEXT("Sphere Overlap Begin: %s"), *OtherActor->GetName());

			SensorOverlappedTools_.Remove(Tool);
		}
	}
}


