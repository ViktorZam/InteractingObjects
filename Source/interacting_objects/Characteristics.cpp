// Fill out your copyright notice in the Description page of Project Settings.


#include "Characteristics.h"
#include "Net/UnrealNetwork.h"

// Sets default values for this component's properties
UCharacteristics::UCharacteristics()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UCharacteristics::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UCharacteristics::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UCharacteristics::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(UCharacteristics, HitPoints);
	DOREPLIFETIME(UCharacteristics, Satiety);

	//UBlueprintGeneratedClass* BPClass = Cast<UBlueprintGeneratedClass>(GetClass());
	//if (BPClass) BPClass->GetLifetimeBlueprintReplicationList(OutLifetimeProps);
}
