// Fill out your copyright notice in the Description page of Project Settings.


#include "Save/QuestSaveGame.h"
#include "QuestBase.h"
#include "Components/QuestLogComponent.h"

void UQuestSaveGame::SaveQuestDetails(const AQuestBase* const InQuest)
{
	if (InQuest == nullptr) return;

	FQuestSaveData questSaveData;
	questSaveData.ObjectiveProgress = InQuest->CurrentObjectiveProgress;
	questSaveData.CurrentStageIndex = InQuest->CurrentStageIndex;
	
	QuestProgress.Add(InQuest->QuestId, questSaveData);
}

void UQuestSaveGame::LoadQuestDetails(UQuestLogComponent* const InQuestComponent)
{
	if (InQuestComponent == nullptr) return;

	for (auto currentActiveQuest : CurrentActiveQuests)
	{
		if (AQuestBase* newQuest = InQuestComponent->AddNewQuest(currentActiveQuest))
		{
			if (FQuestSaveData* questSaveData = QuestProgress.Find(currentActiveQuest))
			{
				newQuest->CurrentStageIndex = questSaveData->CurrentStageIndex;
				newQuest->CurrentObjectiveProgress = questSaveData->ObjectiveProgress;
			}
		}
	}
	InQuestComponent->SetCurrentActiveQuests(CurrentActiveQuests);
	InQuestComponent->SetCompletedQuests(CompletedQuests);
}

void UQuestSaveGame::SaveQuestLog(UQuestLogComponent* const InQuestComponent)
{
	if (InQuestComponent == nullptr) return;

	CurrentActiveQuests = InQuestComponent->GetCurrentActiveQuests();
	CompletedQuests = InQuestComponent->GetCompletedQuests();
}
