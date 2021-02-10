// Fill out your copyright notice in the Description page of Project Settings.
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/WidgetComponent.h"
#include "WidgetComponentForObjects.h"
#include "Objects_items.generated.h"
UCLASS()
class INTERACTING_OBJECTS_API AObjects_items : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AObjects_items();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Personal_Options)
	FString NameObject;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Personal_Options)
	FString DescriptionObject;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Personal_Options)
	USceneComponent* ObjectSceneComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Personal_Options)
	UStaticMeshComponent* ObjectStaticMeshComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Personal_Options)
	UWidgetComponent* ObjectWidgetComponentNameAndDescription;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
