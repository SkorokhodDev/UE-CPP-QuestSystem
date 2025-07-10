// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/QuestGiverComponent.h"
#include "QuestSystemCharacter.h"
#include <Kismet/GameplayStatics.h>
#include "Components/QuestLogComponent.h"
#include "QuestTypes.h"

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
	
}

void UQuestGiverComponent::DisplayQuest()
{
	FQuestDetails* Row = QuestDataHandle.GetRow<FQuestDetails>(QuestDataHandle.RowName.ToString());
	if (Row)
	{
		FString Message = FString::Printf(TEXT("Row find: %s"), *Row->QuestName.ToString());
		GEngine->AddOnScreenDebugMessage(
			-1,                    
			5.0f,                   
			FColor::Green,          
			Message
		);
		OnDisplayQuestDelegate.Broadcast(QuestDataHandle);
	}
}

// Called every frame
void UQuestGiverComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

//TODO: here rewrite to new funk, where transfaring character class, which then casting to our character. 
// Так же тут убрать вообще интефрейс интеракшина и перенести всё в новую функцию.
void UQuestGiverComponent::Interact_Implementation(FString& ObjectiveID)
{
	AQuestSystemCharacter* MyCharacter = Cast<AQuestSystemCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	if (MyCharacter)
	{
		auto QuestLogComponent = MyCharacter->GetQuestLogComponent();
		if (QuestLogComponent->QueryActiveQuest(QuestDataHandle.RowName))
		{
			// here update UI
		}
		else
		{
			DisplayQuest();
		}
	}
	ObjectiveID = GetOwner()->GetName();
}

