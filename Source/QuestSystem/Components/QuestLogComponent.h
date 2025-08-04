// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "QuestLogComponent.generated.h"

class AQuestBase;

DECLARE_MULTICAST_DELEGATE_OneParam(FOnAddNewQuest, AQuestBase*) //, QuestActor);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnQuestCompleted, AQuestBase*, QuestActor);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class QUESTSYSTEM_API UQuestLogComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	//UPROPERTY(BlueprintAssignable)
	FOnAddNewQuest OnAddNewQuestDelegate;

	UPROPERTY(BlueprintAssignable)
	FOnQuestCompleted OnQuestCompletedDelegate;

protected:
	// Base class to spawn quest actors in the world
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AQuestBase> QuestBaseClass;

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
	AQuestBase* AddNewQuest(FName InQuestID);

	UFUNCTION(BlueprintCallable)
	void CompleteQuest(FName InQuestID);

	UFUNCTION(BlueprintCallable, BlueprintPure)
	bool QueryActiveQuest(FName InQuestID);

	UFUNCTION(BlueprintCallable, BlueprintPure)
	bool QueryCompletedQuest(FName InQuestID);

	UFUNCTION(BlueprintCallable)
	void TrackQuest(FName InQuestID);
	
	UFUNCTION(BlueprintCallable)
	void TurnInQuest(FName InQuestID);

	UFUNCTION(BlueprintCallable)
	AQuestBase* GetQuestActor(FName InQuestID);
	//////////////// Setters && Getters

	UFUNCTION(BlueprintCallable, Category = "Quests")
	void SetCurrentActiveQuests(const TArray<FName>& NewActiveQuests) {	CurrentActiveQuests = NewActiveQuests; }

	UFUNCTION(BlueprintCallable, Category = "Quests")
	void SetCompletedQuests(const TArray<FName>& NewCompletedQuests) { CompletedQuests = NewCompletedQuests; }

	UFUNCTION(BlueprintPure, Category = "Quests")
	const TArray<FName>& GetCurrentActiveQuests() const{ return CurrentActiveQuests; }

	UFUNCTION(BlueprintPure, Category = "Quests")
	const TArray<FName>& GetCompletedQuests() const { return CompletedQuests; }

	UFUNCTION(BlueprintPure, Category = "Quests")
	const TArray<AQuestBase*>& GetCurrentQuests();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
