// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Engine/DataTable.h"
#include "Interfaces/InteractionInterface.h"
#include "QuestGiverComponent.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnDisplayQuest, const FDataTableRowHandle&, DataTableRowHandle);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class QUESTSYSTEM_API UQuestGiverComponent : public UActorComponent, public IInteractionInterface
{
	GENERATED_BODY()

protected:
	UPROPERTY(BlueprintAssignable)
	FOnDisplayQuest OnDisplayQuestDelegate;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FDataTableRowHandle QuestDataHandle;

public:	
	// Sets default values for this component's properties
	UQuestGiverComponent();

	UFUNCTION(BlueprintCallable)
	void DisplayQuest();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	// Interaction interface 
	void Interact_Implementation(FString& ObjectiveID);
};
