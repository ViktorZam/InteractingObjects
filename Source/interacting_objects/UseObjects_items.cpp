// Fill out your copyright notice in the Description page of Project Settings.


#include "UseObjects_items.h"

AUseObjects_items::AUseObjects_items() {

	ButtonE_WidgetComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("ButtonE_WidgetComponent"));
	ButtonE_WidgetComponent->AttachTo(RootComponent);
}

