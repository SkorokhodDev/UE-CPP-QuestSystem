// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/SimpleInventoryComponent.h"
#include <QuestSystemCharacter.h>

// Sets default values for this component's properties
USimpleInventoryComponent::USimpleInventoryComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

void USimpleInventoryComponent::AddItemToInventory(FName InItem, int32 InQuantity)
{
	if (int32* CurrentQuantity = Content.Find(InItem))
	{
		Content.Add(InItem, FMath::Max(0, *CurrentQuantity + InQuantity));
	}
	else
	{
		Content.Add(InItem, FMath::Max(0, InQuantity));
	}
	if (AQuestSystemCharacter* OurCharacter = Cast<AQuestSystemCharacter>(GetOwner()))
	{
		OurCharacter->OnObjectiveIDCalledDelegate.Broadcast(InItem.ToString(), InQuantity);
	}
}

int32 USimpleInventoryComponent::QueryItem(FName InItem)
{
	if (int32* value = Content.Find(InItem))
		return *value;
	return 0;
}


// Called when the game starts
void USimpleInventoryComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void USimpleInventoryComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

