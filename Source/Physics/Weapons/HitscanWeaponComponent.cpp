// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapons/HitscanWeaponComponent.h"
#include <Kismet/KismetSystemLibrary.h>
#include <Kismet/GameplayStatics.h>
#include "PhysicsCharacter.h"
#include "PhysicsWeaponComponent.h"
#include <Camera/CameraComponent.h>
#include <Components/SphereComponent.h>

void UHitscanWeaponComponent::Fire()
{
	Super::Fire();

	// @TODO: Add firing functionality
	if (!GetOwner()){
		return;
	}

	const FVector Start = Character->FirstPersonCameraComponent->GetComponentLocation();
	const FVector Forward = Character->FirstPersonCameraComponent->GetForwardVector();
	const FVector End = Start + (Forward * m_Range);

	FHitResult HitResult;
	FCollisionQueryParams Params;

	if (GetWorld()->LineTraceSingleByChannel(HitResult, Start, End, ECC_Visibility, Params))
	{
		AActor* OtherActor = HitResult.GetActor();
		ApplyDamage(OtherActor, HitResult,nullptr);
		onHitscanImpact.Broadcast(OtherActor, HitResult.ImpactPoint, Forward);
	}
	
}
