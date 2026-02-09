// Copyright Epic Games, Inc. All Rights Reserved.

#include "Senecal415PickUpComponent.h"

USenecal415PickUpComponent::USenecal415PickUpComponent()
{
	// Setup the Sphere Collision
	SphereRadius = 32.f;
}

void USenecal415PickUpComponent::BeginPlay()
{
	Super::BeginPlay();

	// Register our Overlap Event
	OnComponentBeginOverlap.AddDynamic(this, &USenecal415PickUpComponent::OnSphereBeginOverlap);
}

void USenecal415PickUpComponent::OnSphereBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	// Checking if it is a First Person Character overlapping
	ASenecal415Character* Character = Cast<ASenecal415Character>(OtherActor);
	if(Character != nullptr)
	{
		// Notify that the actor is being picked up
		OnPickUp.Broadcast(Character);

		// Unregister from the Overlap Event so it is no longer triggered
		OnComponentBeginOverlap.RemoveAll(this);
	}
}
