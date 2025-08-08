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

		OnAddNewQuestDelegate.Broadcast(newQuest);
		return newQuest;
	}
	return nullptr;
}

void UQuestLogComponent::CompleteQuest(FName InQuestID)
{
	CompletedQuests.AddUnique(InQuestID);
	CurrentActiveQuests.Remove(InQuestID);
	
	OnQuestTurnedInDelegate.Broadcast(GetQuestActor(InQuestID));
}

bool UQuestLogComponent::QueryActiveQuest(FName InQuestID)
{
	return CurrentActiveQuests.Contains(InQuestID);
}

bool UQuestLogComponent::QueryCompletedQuest(FName InQuestID)
{
	return CompletedQuests.Contains(InQuestID);
}

void UQuestLogComponent::TrackQuest(FName InQuestID)
{
}

void UQuestLogComponent::TurnInQuest(FName InQuestID)
{
	if (AQuestBase* quest = GetQuestActor(InQuestID))
	{
		//quest->CurrentStageDetails
		// Here you getting reward for the quest to your custom game components

		FString Message = FString::Printf(TEXT("QuestLogComp -> Turn in quest: %s"), *InQuestID.ToString());
		GEngine->AddOnScreenDebugMessage(
			-1,
			5.0f,
			FColor::Green,
			Message
		);


		CompleteQuest(InQuestID);
	}
}

AQuestBase* UQuestLogComponent::GetQuestActor(FName InQuestID)
{
	for (auto currentQuest : CurrentQuests)
	{
		if (InQuestID == currentQuest->QuestId)
		{
			return currentQuest;
		}
	}
	return nullptr;
}

const TArray<AQuestBase*>& UQuestLogComponent::GetCurrentQuests()
{
	return CurrentQuests;
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

