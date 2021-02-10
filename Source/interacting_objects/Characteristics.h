// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Characteristics.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class INTERACTING_OBJECTS_API UCharacteristics : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UCharacteristics();

	UPROPERTY(EditAnywhere, Replicated, BlueprintReadWrite, Category = MyVariables)
	int HitPoints;

	UPROPERTY(EditAnywhere, Replicated, BlueprintReadWrite, Category = MyVariables)
	int Satiety;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
