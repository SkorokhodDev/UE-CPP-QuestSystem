// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "QuestTypes.h"
#include "QuestBase.generated.h"

class UUserWidget;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnObjectIDHeard);

UCLASS()
class QUESTSYSTEM_API AQuestBase : public AActor
{
	GENERATED_BODY()
	

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	UDataTable* QuestDataTable;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UUserWidget> QuestNotificationWidgetClass; 

public:

	UPROPERTY(BlueprintAssignable)
	FOnObjectIDHeard OnObjectIDHeardDelegate;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	FName QuestId; // Row name in DataTable

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	FQuestDetails QuestDetails;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	int32 CurrentStageIndex;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TMap<FString, int32> CurrentObjectiveProgress;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	bool bIsCompleted = false;

public:
	// Sets default values for this actor's properties
	AQuestBase();

	UFUNCTION(BlueprintImplementableEvent)
	void CreateWidgetNotificationEvent(const FObjectiveDetails& InObjectiveDetails);

	UFUNCTION(BlueprintCallable)
	void InitializeQuest(FName InQuestID);
	
	UFUNCTION()
	void OnObjectiveIdHeard(FString InObjectiveID, int32 InValue);

	UFUNCTION(BlueprintCallable)
	FObjectiveDetails GetObjectiveDataByID(FString InObjectiveID);

	UFUNCTION(BlueprintCallable)
	bool IsObjectiveCompleted(FString InObjectiveID);

	UFUNCTION(BlueprintCallable)
	bool AreAllObjectivesCompleted();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
	void GetQuestDetails();
};
