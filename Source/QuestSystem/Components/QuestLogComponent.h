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

	UFUNCTION(Blueprintcallable)
	void TrackQuest(FName InQuestID);
	
	//////////////// Setters && Getters

	UFUNCTION(BlueprintCallable, Category = "Quests")
	void SetCurrentActiveQuests(const TArray<FName>& NewActiveQuests) {	CurrentActiveQuests = NewActiveQuests; }

	UFUNCTION(BlueprintCallable, Category = "Quests")
	void SetCompletedQuests(const TArray<FName>& NewCompletedQuests) { CompletedQuests = NewCompletedQuests; }

	UFUNCTION(BlueprintPure, Category = "Quests")
	const TArray<FName>& GetCurrentActiveQuests() const{ return CurrentActiveQuests; }

	UFUNCTION(BlueprintPure, Category = "Quests")
	const TArray<FName>& GetCompletedQuests() const { return CompletedQuests; }

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
