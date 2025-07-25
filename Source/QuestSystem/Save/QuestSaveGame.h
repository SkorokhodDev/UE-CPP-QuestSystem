// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "QuestSaveGame.generated.h"


class AQuestBase;
class UQuestLogComponent;

USTRUCT(BlueprintType)
struct FQuestSaveData
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite)
	TMap<FString, int32> ObjectiveProgress;

	UPROPERTY(BlueprintReadWrite)
	int32 CurrentStage;

};
/**
 * 
 */
UCLASS()
class QUESTSYSTEM_API UQuestSaveGame : public USaveGame
{
	GENERATED_BODY()

protected:	
	//TODO: Make it in one struct
	UPROPERTY(BlueprintReadWrite)
	TArray<FName> CurrentActiveQuests;

	UPROPERTY(BlueprintReadWrite)
	TArray<FName> CompletedQuests;

	UPROPERTY(BlueprintReadWrite)
	TMap<FName, FQuestSaveData> QuestProgress;

public:
	UFUNCTION(BlueprintCallable)
	void SaveQuestDetails(const AQuestBase* const InQuest);

	UFUNCTION(BlueprintCallable)
	void LoadQuestDetails(UQuestLogComponent* const InQuestComponent);

	UFUNCTION(BlueprintCallable)
	void SaveQuestLog(UQuestLogComponent* const InQuestComponent);

};
