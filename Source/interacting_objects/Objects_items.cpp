// Fill out your copyright notice in the Description page of Project Settings.


#include "Objects_items.h"

// Sets default values
AObjects_items::AObjects_items()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	ObjectSceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("ObjectSceneComponent"));
	RootComponent = ObjectSceneComponent;
	ObjectStaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ObjectStaticMeshComponent"));
	ObjectStaticMeshComponent->AttachTo(RootComponent);
	ObjectWidgetComponentNameAndDescription = CreateDefaultSubobject<UWidgetComponent>(TEXT("ObjectWidgetComponentNameAndDescription"));
	ObjectWidgetComponentNameAndDescription->AttachTo(RootComponent);
}

// Called when the game starts or when spawned
void AObjects_items::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AObjects_items::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

