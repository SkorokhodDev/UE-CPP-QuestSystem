// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/QuestLogComponent.h"
#include "QuestSystem/QuestBase.h"

// Sets default values for this component's properties
UQuestLogComponent::UQuestLogComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

void UQuestLogComponent::AddNewQuest(FName InQuestID)
{
	CurrentActiveQuests.AddUnique(InQuestID);

	CurrentQuests.Add(
		static_cast<AQuestBase*>(
			GetWorld()->SpawnActor(AQuestBase::StaticClass())
			)
	);
}

void UQuestLogComponent::CompleteQuest(FName InQuestID)
{

}

bool UQuestLogComponent::QueryActiveQuest(FName InQuestID)
{
	return CurrentActiveQuests.Contains(InQuestID);
}

void UQuestLogComponent::TackQuest(FName InQuestID)
{
}

// Called when the game starts
void UQuestLogComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UQuestLogComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

