// Fill out your copyright notice in the Description page of Project Settings.


#include "QuestBase.h"
#include <Kismet/GameplayStatics.h>
#include "Blueprint/UserWidget.h"

#include "QuestSystemCharacter.h"
#include "QuestTypes.h"

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

	GetQuestDetails();

	AQuestSystemCharacter* MyCharacter = Cast<AQuestSystemCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	if (MyCharacter)
	{
		MyCharacter->OnObjectiveIDCalledDelegate.AddDynamic(this, &AQuestBase::OnObjectiveIdHeard);
	}
}

// for updating quest progress
void AQuestBase::OnObjectiveIdHeard(FString InObjectiveID)
{
	UE_LOG(LogTemp, Log, TEXT("QuestBase: Objective id heard '%s'"), *InObjectiveID);
	if (int32* key = CurrentObjectiveProgress.Find(InObjectiveID))
	{
		UE_LOG(LogTemp, Log, TEXT(" - - - > Objective id was FOUND '%s'"), *InObjectiveID);

		FObjectiveDetails ObjectiveData = GetObjectiveDataByID(InObjectiveID);
		if (*key < ObjectiveData.Quantity)
		{
			CurrentObjectiveProgress.Add(InObjectiveID, *key + 1); // Update progress
			if (IsObjectiveCompleted(InObjectiveID))
			{
				//TODO: Remake to set widget controller.
				//UUserWidget* MyWidget = CreateWidget<UUserWidget>(GetWorld(), QuestNotificationWidgetClass);
				//if (MyWidget)
				//{
				//	MyWidget->AddToViewport();
				//}
				CreateWidgetNotificationEvent(ObjectiveData);
			}
		}
	}
	return;
}

FObjectiveDetails AQuestBase::GetObjectiveDataByID(FString InObjectiveID)
{
	for (auto& objective : CurrentStageDetails.Objectives)
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

// Inits quest details from Data Table.
void AQuestBase::GetQuestDetails()
{
	FString ContextString = TEXT("Getting Quest Row");

	FQuestDetails* QuestRow = QuestDataTable->FindRow<FQuestDetails>(QuestId, ContextString);

	if (QuestRow)
	{
		CurrentStageDetails = QuestRow->Stages[CurrentStage];
		CurrentObjectiveProgress.Empty();

		for (auto& objective : CurrentStageDetails.Objectives)
		{
			CurrentObjectiveProgress.Add(objective.ObjectiveID, 0);
		}
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Quest with ID '%s' not found!"), *QuestId.ToString());
	}
}

