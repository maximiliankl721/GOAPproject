// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/ItemTools/Tool.h"
#include <Core/AI/CustomAICharacter.h>

// Sets default values
ATool::ATool()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	PickupArea = CreateDefaultSubobject<UBoxComponent>(TEXT("Pickup Area"));
	PickupArea->SetupAttachment(RootComponent);
	UseCount_ = 0;

	PickupArea->OnComponentBeginOverlap.AddDynamic(this, &ATool::OnOverlapBegin);
	PickupArea->OnComponentEndOverlap.AddDynamic(this, &ATool::OnOverlapEnd);
}

// Called when the game starts or when spawned
void ATool::BeginPlay()
{
	Super::BeginPlay();
	
}

void ATool::AddToAIInventory(ACustomAICharacter* AIChar)
{
}

// Called every frame
void ATool::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

int ATool::GetShopCost()
{
	return ShopCost_;
}

float ATool::GetDamagePerAttack()
{
	return DamagePerAttack_;
}

int ATool::GetInventorySpace()
{
	return InventorySpace_;
}

FString ATool::GetToolName()
{
	return ToolName_;
}

int ATool::GetTier()
{
	return Tier_;
}

int ATool::GetUseCount()
{
	return UseCount_;
}

void ATool::IncreaseUseCount()
{
	if (UseCount_ < MaxUses_) {
		UseCount_++;
	}
}

int ATool::GetMaxUses()
{
	return MaxUses_;
}

void ATool::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor && (OtherActor != this) && OtherComp)
	{
		auto AIChar = Cast<ACustomAICharacter>(OtherActor);
		if (AIChar) {
			UE_LOG(LogTemp, Warning, TEXT("Overlap Begin: %s"), *OtherActor->GetName());

			AddToAIInventory(AIChar);
			//AIChar->AddToToolInventory(NewObject<APurpleTool>());

			Destroy();
		}
		
	}
}

void ATool::OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (OtherActor && (OtherActor != this) && OtherComp)
	{
		UE_LOG(LogTemp, Warning, TEXT("Overlap End: %s"), *OtherActor->GetName());
	}
}

