// Fill out your copyright notice in the Description page of Project Settings.


#include "CRGameMode.h"
#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"

ACRGameMode::ACRGameMode()
{
	CurrentLevelIndex = 0;
}

void ACRGameMode::BeginPlay()
{
	Super::BeginPlay();

	FInputModeGameOnly InputMode;
	Controller = GetWorld()->GetFirstPlayerController();
	Controller->SetInputMode(InputMode);
	Controller -> bShowMouseCursor = false;

	CheckLevel();
}

void ACRGameMode::CheckLevel()
{
	//FString CurrentLevelName = GetWorld()-> GetMapName();
	FString CurrentLevelName = CleanLevelString(GetWorld());
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Level Name:") + CurrentLevelName);
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Index") + FString::FromInt(CurrentLevelIndex));
	Levels.Find(CurrentLevelName, CurrentLevelIndex);
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Index") + FString::FromInt(CurrentLevelIndex));
	if (CurrentLevelIndex < Levels.Num() - 1)
	{
		NextLevel = Levels[CurrentLevelIndex + 1];
	}
	else
		NextLevel = "End";
}

void ACRGameMode::EndGame()
{
	FString LevelString = CleanLevelString(GetWorld());
	FName LevelToLoad = FName(*LevelString);

	UGameplayStatics::OpenLevel(this, LevelToLoad, true);
}

void ACRGameMode::LevelComplete()
{
	if (DefaultLevelCompleteWidget)
	{
		LevelCompleteWidget = CreateWidget<UUserWidget>(GetWorld(), DefaultLevelCompleteWidget);
		LevelCompleteWidget->AddToViewport();
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("No Default level Complete widget Selected!!"));
	}

	GetWorld()->GetTimerManager().SetTimer( LevelSwapTimer , this, &ACRGameMode::LoadNextlevel, 2.0f, false);
}

void ACRGameMode::LoadNextlevel()
{
	if (Levels.Contains(NextLevel))
	{
		FName LevelToLoad = FName(*NextLevel);
		UGameplayStatics::OpenLevel(this, LevelToLoad, true);
	}
	else
	{
		if (LevelCompleteWidget) {
			LevelCompleteWidget->RemoveFromParent();
			if (DefaultGameCompleteWidget)
			{
				GameCompleteWidget = CreateWidget<UUserWidget>(GetWorld(), DefaultGameCompleteWidget);
				GameCompleteWidget->AddToViewport();

				Controller->bShowMouseCursor = true;
				FInputModeUIOnly InputMode;
				Controller->SetInputMode(InputMode);

			}
			else
			{
				UE_LOG(LogTemp, Warning, TEXT("No Default Game Complete widget Selected!!"));

			}
		}
	}
}

FString ACRGameMode::CleanLevelString(UObject* WorldContextObject)
{
	if (GEngine)
	{
		FString Prefix = GEngine->GetWorldFromContextObject(WorldContextObject)->StreamingLevelsPrefix;
		FString LevelName = GetWorld()->GetMapName();

		return LevelName.RightChop(Prefix.Len());
	}
	return "No Map Found";
}
