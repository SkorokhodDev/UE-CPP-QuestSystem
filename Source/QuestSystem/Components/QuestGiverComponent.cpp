// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/QuestGiverComponent.h"
#include "QuestSystemCharacter.h"
#include <Kismet/GameplayStatics.h>
#include "Components/QuestLogComponent.h"
#include "QuestTypes.h"
#include "QuestBase.h"

// Sets default values for this component's properties
UQuestGiverComponent::UQuestGiverComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UQuestGiverComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	if (QuestDataHandle.IsNull())
	{
		check(0);
	}
}

void UQuestGiverComponent::DisplayQuest()
{
	FQuestDetails* Row = QuestDataHandle.GetRow<FQuestDetails>(QuestDataHandle.RowName.ToString());
	if (Row)
	{
		FString Message = FString::Printf(TEXT("Display quest: Row find: %s"), *Row->QuestName.ToString());
		GEngine->AddOnScreenDebugMessage(
			-1,                    
			5.0f,                   
			FColor::Green,          
			Message
		);
		OnDisplayQuestDelegate.Broadcast(QuestDataHandle);
	}
}

void UQuestGiverComponent::DisplayRewards()
{
	FQuestDetails* Row = QuestDataHandle.GetRow<FQuestDetails>(QuestDataHandle.RowName.ToString());
	if (Row)
	{
		FString Message = FString::Printf(TEXT("Display rewards: Row find: %s"), *Row->QuestName.ToString());
		GEngine->AddOnScreenDebugMessage(
			-1,
			5.0f,
			FColor::Green,
			Message
		);
		OnDisplayRewardsDelegate.Broadcast(QuestDataHandle);
	}
}


// Called every frame
void UQuestGiverComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UQuestGiverComponent::HandleQuestInteraction(FString& ObjectiveID)
{
	AQuestSystemCharacter* MyCharacter = Cast<AQuestSystemCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	if (MyCharacter)
	{
		auto QuestLogComponent = MyCharacter->GetQuestLogComponent();
		// if the quest is completed, display rewards
		if (QuestLogComponent->QueryActiveQuest(QuestDataHandle.RowName)) // if this quest is active
		{
			// here update UI
			if (AQuestBase* quest = QuestLogComponent->GetQuestActor(QuestDataHandle.RowName))
			{
				// quest->CurrentStageIndex == quest->QuestDetails.Stages.Num() - 1
				if (quest->ContainsObjectiveType(EObjectiveType::ClaimReward) && quest->AreAllObjectivesCompletedExceptType(EObjectiveType::ClaimReward))
				{
					DisplayRewards();
				}
			}
		}
		else if (!QuestLogComponent->QueryCompletedQuest(QuestDataHandle.RowName)) // display quest if it`s not completed
		{
			FQuestDetails* Row = QuestDataHandle.GetRow<FQuestDetails>(QuestDataHandle.RowName.ToString());
			if (Row && Row->bAutoAccept)
			{
				// Auto accept quest
				MyCharacter->GetQuestLogComponent()->AddNewQuest(QuestDataHandle.RowName);
			}
			else
			{
				// Display quest dialog
				DisplayQuest();
			}
		}
	}
	ObjectiveID = GetOwner()->GetName();
}

//TODO: here rewrite to new funk, where transferring character class, which then casting to our character. 
void UQuestGiverComponent::Interact_Implementation(FString& ObjectiveID)
{
	HandleQuestInteraction(ObjectiveID);
}

