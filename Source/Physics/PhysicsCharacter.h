// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Logging/LogMacros.h"
#include "PhysicsCharacter.generated.h"

class UInputComponent;
class USkeletalMeshComponent;
class UCameraComponent;
class UInputAction;
class UInputMappingContext;
class UPhysicsHandleComponent;
struct FInputActionValue;

DECLARE_LOG_CATEGORY_EXTERN(LogTemplateCharacter, Log, All);

UCLASS(config=Game)
class APhysicsCharacter : public ACharacter
{
	GENERATED_BODY()
public:
	/** Pawn mesh: 1st person view (arms; seen only by self) */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Mesh, meta = (AllowPrivateAccess = "true"))
	USkeletalMeshComponent* Mesh1P;

	/** First person camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FirstPersonCameraComponent;

	/** MappingContext */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputMappingContext* DefaultMappingContext;

	/** Jump Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	UInputAction* JumpAction;

	/** Move Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	UInputAction* MoveAction;

	/** Look Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* LookAction;

	/** Sprint Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* SprintAction;

	/** PickUp Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* PickUpAction;

	/** Sprinting speed multiplier */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Config, meta = (AllowPrivateAccess = "true"))
	float m_SprintSpeedMultiplier;

	/**Current Stamina*/
	float m_CurrentStamina;
	
	/** Maximum stamina, used when sprinting */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Config, meta = (AllowPrivateAccess = "true"))
	float m_MaxStamina;

	/** Stamina depletion rate, in seconds */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Config, meta = (AllowPrivateAccess = "true"))
	float m_StaminaDepletionRate;

	/** Stamina recovery rate, in seconds */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Config, meta = (AllowPrivateAccess = "true"))
	float m_StaminaRecoveryRate;

	/** Max health poins */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Config, meta = (AllowPrivateAccess = "true"))
	float m_MaxHealth;

	/**Current Health*/
	float m_CurrentHealth;
	
	/** Highlight overlay material */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Config, meta = (AllowPrivateAccess = "true"))
	class UMaterialInterface* m_HighlightMaterial;

	/** Maximum distance to allow component grabbing */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Config, meta = (AllowPrivateAccess = "true"))
	float m_MaxGrabDistance = 1000.f;

	/** Base interpolation factor to move grabbed components*/
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Config, meta = (AllowPrivateAccess = "true"))
	float m_BaseInterpolationSpeed = 1000.f;

	/**Sprint Speed*/
	float m_fSprintSpeed = 2000.0f;
	
	/**Walk Normal Speed*/
	float m_fWalkSpeed = 600.0f;

	bool bBlockSprint;
	bool bIsTryingToRun = false;
	
	float m_fDistanceGrabbedObject;
	TObjectPtr<UPrimitiveComponent> m_GrabComponent;
	
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = DebugData, meta = (AllowPrivateAccess = "true"))
	UMeshComponent* m_HighlightedMesh = nullptr;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = DebugData, meta = (AllowPrivateAccess = "true"))
	UPhysicsHandleComponent* m_PhysicsHandle;
	
public:
	APhysicsCharacter();
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;

protected:

	/** APawn **/
	virtual void NotifyControllerChanged() override;
	virtual void SetupPlayerInputComponent(UInputComponent* InputComponent) override;

	/** APhysicsCharacter **/
	void Move(const FInputActionValue& Value);
	void Look(const FInputActionValue& Value);
	void Sprint(const FInputActionValue& Value);
	void GrabObject(const FInputActionValue& Value);
	void ReleaseObject(const FInputActionValue& Value);

	void SetHighlightMesh(UMeshComponent* StaticMesh);

	void UpdateStamina(float DeltaSeconds);

	FHitResult RayCast() const;
	
	void FindGrabbableObjects();

	void UpdateGrabbedObject();
	
public:
	USkeletalMeshComponent* GetMesh1P() const { return Mesh1P; }
	UCameraComponent* GetFirstPersonCameraComponent() const { return FirstPersonCameraComponent; }
	
	void SetIsSprinting(bool NewIsSprinting);

	UFUNCTION(BlueprintCallable)
	float GetStamina() const {return m_CurrentStamina;};

	UFUNCTION(BlueprintCallable)
	void ChangeLife(float LifeAmount);
	
	UFUNCTION(BlueprintCallable)
	float GetHealth() const {return m_CurrentHealth;};
};
