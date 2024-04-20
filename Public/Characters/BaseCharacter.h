// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "BaseCharacter.generated.h"

class UHealthComponent;
class UWeaponComponent;
class UCameraComponent;
class USpringArmComponent;
class UInputMappingContext;
class UInputAction;

UENUM(Blueprintable)
enum EMovementState
{
	JUMPING,
	CROUCHING,
	RUNNING,
	WALKING,
	IDLE,
};

/**
* Base character for player and enemies
*/
UCLASS(Abstract)
class ALPHASTRIKE_API ABaseCharacter : public ACharacter
{
	GENERATED_BODY()

	// Allows UPlayerWidget to access components of character
	friend class UPlayerWidget;

public:
#pragma region ACharacter interface
	virtual void Tick(float DeltaTime) override;
#pragma endregion ACharacter interface

#pragma region ABaseCharacter interface
	ABaseCharacter();
#pragma endregion ABaseCharacter interface

	void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void HandleDeath(AController* CharacterController, AController* KillerController);

protected:
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	virtual void PossessedBy(AController* NewController) override;

	inline virtual void Move(const FInputActionValue& Value);
	inline virtual void Look(const FInputActionValue& Value);
	inline virtual void ZoomIn();
	inline virtual void ResetZoom();
	inline virtual void Sprint();
	inline virtual void StopSprinting();
	virtual void Jump() override
	{
		Super::Jump();
		MovementState = JUMPING;
	}
	virtual void StopJumping() override
	{
		Super::StopJumping();
		MovementState = WALKING;
	}
	virtual void Crouch(bool bClientSimulation) override;

	virtual void UnCrouch(bool bClientSimulation) override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Movement")
	TEnumAsByte<EMovementState> MovementState = RUNNING;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Zoom")
	float ZoomMagnification{ 1.5f };
private:
#pragma region Input Actions
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputMappingContext> DefaultMappingContext;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> LookAction;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> CrouchAction;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> ZoomInAction;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> ShootAction;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> JumpAction;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> PauseAction;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> ShowScoreboardAction;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> MoveAction;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> SprintAction;
#pragma endregion Input Actions

#pragma region Components
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite,
		Category = "Character|Components", meta = (AllowPrivateAccess))
	TObjectPtr<UCameraComponent> CameraComponent;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite,
		Category = "Character|Components", meta = (AllowPrivateAccess))
	TObjectPtr<USpringArmComponent> SpringArm;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite,
		Category = "Character|Components", meta = (AllowPrivateAccess))
	UStaticMeshComponent* WeaponMesh;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite,
		Category = "Character|Components", meta = (AllowPrivateAccess))
	TObjectPtr<UHealthComponent> HealthComponent;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite,
		Category = "Character|Components", meta = (AllowPrivateAccess))
	TObjectPtr<UWeaponComponent> WeaponComponent;
#pragma endregion Components
};
