// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "QuestLogComponent.generated.h"

class AQuestBase;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class QUESTSYSTEM_API UQuestLogComponent : public UActorComponent
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TArray<FName> CurrentActiveQuests;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TArray<FName> CompletedQuests;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TArray<FName> CurrentTrackedQuest;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TArray<AQuestBase*> CurrentQuests;


public:	
	// Sets default values for this component's properties
	UQuestLogComponent();

	UFUNCTION(BlueprintCallable)
	void AddNewQuest(FName InQuestID);

	UFUNCTION(BlueprintCallable)
	void CompleteQuest(FName InQuestID);

	UFUNCTION(BlueprintCallable, BlueprintPure)
	bool QueryActiveQuest(FName InQuestID);

	UFUNCTION(Blueprintcallable)
	void TackQuest(FName InQuestID);

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
