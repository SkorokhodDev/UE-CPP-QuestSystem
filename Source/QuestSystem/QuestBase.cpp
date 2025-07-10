// Fill out your copyright notice in the Description page of Project Settings.


#include "QuestBase.h"

// Sets default values
AQuestBase::AQuestBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

void AQuestBase::InitializeQuest(FName InQuestID)
{
	QuestId = InQuestID;
}

// Called when the game starts or when spawned
void AQuestBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AQuestBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

