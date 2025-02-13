// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/GameBlocks/Block.h"
#include <Engine/TriggerBox.h>
#include <Components/BoxComponent.h>
#include <GOAP_5_4/GOAP_5_4Character.h>
#include <Core/AI/CustomAICharacter.h>

// Sets default values
ABlock::ABlock()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SceneRoot_ = CreateDefaultSubobject<USceneComponent>(TEXT("DefaultSceneRoot"));
	RootComponent = SceneRoot_;

	HitArea_ = CreateDefaultSubobject<UBoxComponent>(TEXT("HitArea"));
	HitArea_->SetupAttachment(RootComponent);
	Mesh_ = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh_->SetupAttachment(RootComponent);

	// Find and set the static mesh
	static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshAsset(TEXT("/Game/LevelPrototyping/Meshes/SM_Cube.SM_Cube"));
	if (MeshAsset.Succeeded())
	{
		Mesh_->SetStaticMesh(MeshAsset.Object);
	}

	HitArea_->SetRelativeScale3D(FVector(1.75f, 1.75f, 1.75f));
	auto HitAreaLoc = HitArea_->GetRelativeLocation();
	Mesh_->SetRelativeLocation(FVector(50.0f, -50.0f, -50.0f));
	Mesh_->SetRelativeRotation(FRotator(0.0f, 90.0f, 0.0f));
	HitArea_->SetRelativeLocation(FVector(HitAreaLoc.X, HitAreaLoc.Y + 100, HitAreaLoc.Z));


}

// Called when the game starts or when spawned
void ABlock::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ABlock::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

float ABlock::GetHP()
{
	return HitPoints_;
}

void ABlock::SetHP(float HitPoints)
{
	HitPoints_ = HitPoints;
}

int ABlock::GetCreditValue()
{
	return CreditValue_;
}

void ABlock::SetCreditValue(int CreditValue)
{
	CreditValue_ = CreditValue;
}

