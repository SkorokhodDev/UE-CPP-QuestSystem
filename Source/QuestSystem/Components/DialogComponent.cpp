// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/DialogComponent.h"

#include "AI/Controllers/DialogAIController.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "UI/Widgets/DialogWidget.h"
#include "Kismet/GameplayStatics.h"

#include "GameFramework/PlayerController.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Character.h"

// Sets default values for this component's properties
UDialogComponent::UDialogComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}


void UDialogComponent::InitDialogWidget()
{
	APlayerController* PlayerController = Cast<APlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	if (PlayerController && DialogAIController && DialogTree)
	{
		// Init Widget
		UUserWidget* Widget = CreateWidget<UDialogWidget>(PlayerController, DialogWidgetClass);
		DialogWidget = Cast<UDialogWidget>(Widget);

		DialogWidget->OnExitDelegate.AddDynamic(this, &UDialogComponent::OnExitDialog);

		if (ACharacter* PlayerChar = Cast<ACharacter>(PlayerController->GetPawn()))
			PlayerChar->GetCharacterMovement()->DisableMovement();
		PlayerController->SetInputMode(FInputModeUIOnly());

		Widget->AddToViewport();

		// Right Order
		DialogAIController->GetBlackboardComponent()->InitializeBlackboard(*DialogTree->BlackboardAsset);
		DialogAIController->RunBehaviorTree(DialogTree);

		DialogAIController->GetBlackboardComponent()->SetValueAsObject(FName("DialogWidget"), DialogWidget);
	}
}

void UDialogComponent::OnExitDialog()
{
	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	if (PlayerController)
	{
		if (ACharacter* PlayerChar = Cast<ACharacter>(PlayerController->GetPawn()))
			PlayerChar->GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Walking);
		PlayerController->SetInputMode(FInputModeGameOnly());

		DialogWidget->RemoveFromParent();

		if (DialogAIController && DialogAIController->GetBrainComponent())
		{
			DialogAIController->GetBrainComponent()->StopLogic(FString("OnExitDialog"));
		}
	}
}

// Called when the game starts
void UDialogComponent::BeginPlay()
{
	Super::BeginPlay();

	if (DialogAIControllerClass)
	{
		DialogAIController = GetWorld()->SpawnActor<ADialogAIController>(DialogAIControllerClass);
	}
}





