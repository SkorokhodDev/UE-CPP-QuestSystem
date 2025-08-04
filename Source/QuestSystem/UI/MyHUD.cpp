// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/MyHUD.h"

#include "Blueprint/UserWidget.h"
#include "UI/Widgets/OverlayWidget.h"
#include "WidgetControllers/OverlayWidgetController.h"
#include "WidgetControllers/QuestMenuWidgetControllerBase.h"

void AMyHUD::BeginPlay()
{
    Super::BeginPlay();


    if (OverlayWidgetClass)
    {
        OverlayWidget = CreateWidget<UOverlayWidget>(GetWorld(), OverlayWidgetClass);
        if (OverlayWidget)
        {
            OverlayWidget->SetWidgetController(GetOverlayWidgetController());

            OverlayWidget->AddToViewport();
            OverlayWidget->SetVisibility(ESlateVisibility::Visible);
        }
    }
}


// TODO: Make player controller a widget controller for overlay, then set it on begin play and make a delegate to controll toggle widgets. 
// or make a separate widget controller for overaly and control toggling using this controller from PlayerController.
void AMyHUD::ToggleQuestMenu()
{
    if (OverlayWidget)
        OverlayWidget->ToggleQuestMenu();
}

UOverlayWidgetController* AMyHUD::GetOverlayWidgetController()
{
    if (OverlayWidgetController == nullptr)
    {
        OverlayWidgetController = NewObject<UOverlayWidgetController>(this, OverlayWidgetControllerClass);
        //OverlayWidgetController->SetWidgetControllerParams(WCParams);
        OverlayWidgetController->BindCallbacksToDependencies(); // Bind our delegates to changed delegate
    }
    return OverlayWidgetController;
}

UQuestMenuWidgetControllerBase* AMyHUD::GetQuestMenuWidgetController()
{
    if (QuestMenuWidgetController == nullptr)
    {
        QuestMenuWidgetController = NewObject<UQuestMenuWidgetControllerBase>(this, QuestMenuWidgetControllerClass);
        //OverlayWidgetController->SetWidgetControllerParams(WCParams);
        QuestMenuWidgetController->BindCallbacksToDependencies(); // Bind our delegates to changed delegate
    }
    return QuestMenuWidgetController;
}
