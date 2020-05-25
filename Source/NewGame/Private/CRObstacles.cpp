// Fill out your copyright notice in the Description page of Project Settings.


#include "CRObstacles.h"
#include "Components/BoxComponent.h"

// Sets default values
ACRObstacles::ACRObstacles()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	Cube = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Cube"));
	RootComponent = Cube;

}

// Called when the game starts or when spawned
void ACRObstacles::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame

