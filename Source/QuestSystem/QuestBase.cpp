// Fill out your copyright notice in the Description page of Project Settings.


#include "QuestBase.h"
#include <Kismet/GameplayStatics.h>
#include "Blueprint/UserWidget.h"

#include "QuestSystemCharacter.h"
#include "QuestTypes.h"
#include "Components/SimpleInventoryComponent.h"
#include "Components/QuestLogComponent.h"

// Sets default values
AQuestBase::AQuestBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

void AQuestBase::InitializeQuest(FName InQuestID)
{
	QuestId = InQuestID;
}

// Called when the game starts or when spawned
void AQuestBase::BeginPlay()
{
	Super::BeginPlay();

	check(QuestNotificationWidgetClass);

	GetQuestDetails();

	AQuestSystemCharacter* MyCharacter = Cast<AQuestSystemCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	if (MyCharacter)
	{
		MyCharacter->OnObjectiveIDCalledDelegate.AddDynamic(this, &AQuestBase::OnObjectiveIdHeard);
	
		
		// Can be moved to BP or made as implementable event in character. (for my DDF project)
		// Check for inventory items
		for (auto& objective : QuestDetails.Stages[CurrentStageIndex].Objectives)
		{
			if (objective.Type == EObjectiveType::Collect)
			{
				int32 itemAmount = MyCharacter->SimpleInventoryComponent->QueryItem(FName(*objective.ObjectiveID));
				if(itemAmount > 0)
					OnObjectiveIdHeard(objective.ObjectiveID, itemAmount);
			}
		}
		bIsCompleted = AreAllObjectivesCompleted();
	}
}

// for updating quest progress
void AQuestBase::OnObjectiveIdHeard(FString InObjectiveID, int32 InValue)
{
	UE_LOG(LogTemp, Log, TEXT("QuestBase: Objective id heard '%s'"), *InObjectiveID);
	if (int32* value = CurrentObjectiveProgress.Find(InObjectiveID))
	{
		UE_LOG(LogTemp, Log, TEXT(" - - - > Objective id was FOUND '%s'"), *InObjectiveID);

		FObjectiveDetails ObjectiveData = GetObjectiveDataByID(InObjectiveID);
		if (InValue < 0) // decrease key value
		{
			CurrentObjectiveProgress.Add(InObjectiveID, FMath::Max(0, *value + InValue));
			OnObjectIDHeardDelegate.Broadcast(this);
		}
		else if (*value < ObjectiveData.Quantity)
		{
			CurrentObjectiveProgress.Add(InObjectiveID, *value + InValue); // Update progress
			if (IsObjectiveCompleted(InObjectiveID))
			{
				//TODO: Remake to set widget controller.
				//UUserWidget* MyWidget = CreateWidget<UUserWidget>(GetWorld(), QuestNotificationWidgetClass);
				//if (MyWidget)
				//{
				//	MyWidget->AddToViewport();
				//}
				CreateWidgetNotificationEvent(ObjectiveData);

				if (AreAllObjectivesCompleted())
				{
					if (QuestDetails.Stages.IsValidIndex(CurrentStageIndex + 1))
					{
						CurrentStageIndex = CurrentStageIndex + 1;
						CurrentObjectiveProgress.Empty();
						for (auto& objective : QuestDetails.Stages[CurrentStageIndex].Objectives)
						{
							CurrentObjectiveProgress.Add(objective.ObjectiveID, 0);
						}
					}
					else
					{
						bIsCompleted = true;
						if (QuestDetails.bAutoComplete)
						{
							if (UQuestLogComponent* questLogComponent = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0)->GetComponentByClass<UQuestLogComponent>())
							{
								questLogComponent->TurnInQuest(QuestId);
							}
						}
					}
				}
			}
			OnObjectIDHeardDelegate.Broadcast(this);
		}
	}
	return;
}

FObjectiveDetails AQuestBase::GetObjectiveDataByID(FString InObjectiveID)
{
	for (auto& objective : QuestDetails.Stages[CurrentStageIndex].Objectives)
	{
		if (objective.ObjectiveID == InObjectiveID)
		{
			return objective;
		}
	}
	return FObjectiveDetails();
}

bool AQuestBase::IsObjectiveCompleted(FString InObjectiveID)
{
	if (int32* key = CurrentObjectiveProgress.Find(InObjectiveID))
	{
		FObjectiveDetails ObjectiveData = GetObjectiveDataByID(InObjectiveID);
		if (*key >= ObjectiveData.Quantity)
		{
			return true;
		}
	}
	return false;
}

bool AQuestBase::AreAllObjectivesCompleted()
{
	for (auto objective : QuestDetails.Stages[CurrentStageIndex].Objectives)
	{
		FObjectiveDetails objectiveData = GetObjectiveDataByID(objective.ObjectiveID);
		if (int32* key = CurrentObjectiveProgress.Find(objective.ObjectiveID))
		{
			if (*key < objectiveData.Quantity)
			{
				return false;
			}
		}
	}
	return true;
}

// Inits quest details from Data Table.
void AQuestBase::GetQuestDetails()
{
	FString ContextString = TEXT("Getting Quest Row");

	FQuestDetails* QuestRow = QuestDataTable->FindRow<FQuestDetails>(QuestId, ContextString);

	if (QuestRow)
	{
		QuestDetails = *QuestRow;
		CurrentObjectiveProgress.Empty();

		for (auto& objective : QuestRow->Stages[CurrentStageIndex].Objectives)
		{
			CurrentObjectiveProgress.Add(objective.ObjectiveID, 0);
		}
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Quest with ID '%s' not found!"), *QuestId.ToString());
	}
}

