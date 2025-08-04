// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/WidgetControllers/QuestMenuWidgetControllerBase.h"
#include <Kismet/GameplayStatics.h>

#include <QuestSystemCharacter.h>
#include "Components/QuestLogComponent.h"
#include "QuestBase.h"

void UQuestMenuWidgetControllerBase::BindCallbacksToDependencies()
{
	AQuestSystemCharacter* MyCharacter = Cast<AQuestSystemCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	if (MyCharacter)
	{
		auto QuestLogComponent = MyCharacter->GetQuestLogComponent();
		QuestLogComponent->OnAddNewQuestDelegate.AddLambda(
			[&](AQuestBase* InQuestBase) {
				NewQuestWasAddedDelegate.Broadcast(InQuestBase);
				}
		);
	}
}



void UQuestMenuWidgetControllerBase::BroadcastInitialValues()
{
	AQuestSystemCharacter* MyCharacter = Cast<AQuestSystemCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	if (MyCharacter)
	{
		auto QuestLogComponent = MyCharacter->GetQuestLogComponent();
		for (auto quest : QuestLogComponent->GetCurrentQuests())
		{
			NewQuestWasAddedDelegate.Broadcast(quest);
		}
	}
}