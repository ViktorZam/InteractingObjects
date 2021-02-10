// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Objects_items.h"
#include "UseObjects_items.generated.h"

/**
 * 
 */
UCLASS()
class INTERACTING_OBJECTS_API AUseObjects_items : public AObjects_items
{
	GENERATED_BODY()
public:
	AUseObjects_items();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Personal_Options)
	int ResHitPoints;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Personal_Options)
	int ResSatiety;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Personal_Options)
	UWidgetComponent* ButtonE_WidgetComponent;

};
