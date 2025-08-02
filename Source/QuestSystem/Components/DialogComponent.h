// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "DialogComponent.generated.h"

class UBehaviorTree;
class UDialogWidget;
class ADialogAIController;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class QUESTSYSTEM_API UDialogComponent : public UActorComponent
{
	GENERATED_BODY()


protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TObjectPtr<UBehaviorTree> DialogTree;

	UPROPERTY()
	TObjectPtr<ADialogAIController> DialogAIController;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<ADialogAIController> DialogAIControllerClass;

	UPROPERTY()
	TObjectPtr<UDialogWidget> DialogWidget;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UDialogWidget> DialogWidgetClass;

public:
	// Sets default values for this component's properties
	UDialogComponent();

	UFUNCTION(BlueprintCallable, Category = "Dialog")
	void InitDialogWidget();

	UFUNCTION()
	void OnExitDialog();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	//// InteractionInterface 
	//void Interaction_Implementation() override;
	//// End InteractionInterface


};
