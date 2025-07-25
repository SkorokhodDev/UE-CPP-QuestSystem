// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/QuestLogComponent.h"
#include "QuestSystem/QuestBase.h"
#include <Kismet/GameplayStatics.h>

// Sets default values for this component's properties
UQuestLogComponent::UQuestLogComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

AQuestBase* UQuestLogComponent::AddNewQuest(FName InQuestID)
{
	CurrentActiveQuests.AddUnique(InQuestID);

	FTransform SpawnTransform;
	AQuestBase* newQuest = Cast<AQuestBase>(UGameplayStatics::BeginDeferredActorSpawnFromClass(this, QuestBaseClass, SpawnTransform));
	if (newQuest)
	{
		newQuest->QuestId = InQuestID;

		UGameplayStatics::FinishSpawningActor(newQuest, SpawnTransform);
		CurrentQuests.Add(newQuest);

		return newQuest;
	}
	return nullptr;
}

void UQuestLogComponent::CompleteQuest(FName InQuestID)
{

}

bool UQuestLogComponent::QueryActiveQuest(FName InQuestID)
{
	return CurrentActiveQuests.Contains(InQuestID);
}

void UQuestLogComponent::TrackQuest(FName InQuestID)
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

