// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "DialogAIController.generated.h"

class UBehaviorTreeComponent;
/**
 * 
 */
UCLASS()
class QUESTSYSTEM_API ADialogAIController : public AAIController
{
	GENERATED_BODY()

protected:
	UPROPERTY()
	TObjectPtr<UBehaviorTreeComponent> BehaviorTreeComponent;

public:
	ADialogAIController();
};
