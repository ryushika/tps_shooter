// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/BaseCharacter.h"
#include "Camera/CameraComponent.h"
#include "Camera/CameraShakeBase.h"
#include "GameFramework/SpringArmComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Components/InputComponent.h"
#include "FrameworkClasses/BaseGameMode.h"
#include "FrameworkClasses/AlphaStrikeGameState.h"
#include "FrameworkClasses/AlphaStrikeHUD.h"
#include "ActorComponents/HealthComponent.h"
#include "ActorComponents/WeaponComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include <Kismet/GameplayStatics.h>

// Sets default values
ABaseCharacter::ABaseCharacter() : Super()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));
	SpringArm->SetupAttachment(RootComponent);
	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	CameraComponent->SetupAttachment(SpringArm);
	WeaponMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Weapon Mesh"));
	WeaponMesh->SetupAttachment(RootComponent);
	HealthComponent = CreateDefaultSubobject<UHealthComponent>("Health Component");
	WeaponComponent = CreateDefaultSubobject<UWeaponComponent>("Weapon Component");
}

void ABaseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered,
			this, &ABaseCharacter::Look);

		//EnhancedInputComponent->BindAction(PauseAction, ETriggerEvent::Completed,
		// this, &ABaseCharacter::Pause);
		if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
		{
			AAlphaStrikeHUD* Hud{ Cast<AAlphaStrikeHUD>(PlayerController->GetHUD()) };
			if (Hud)
			{
				EnhancedInputComponent->BindAction(ShowScoreboardAction, ETriggerEvent::Started,
					Hud, &AAlphaStrikeHUD::ShowScoreboardWidget);
				EnhancedInputComponent->BindAction(ShowScoreboardAction, ETriggerEvent::Completed,
					Hud, &AAlphaStrikeHUD::HideScoreboardWidget);
			}
		}

		EnhancedInputComponent->BindAction(ZoomInAction, ETriggerEvent::Started,
			this, &ABaseCharacter::ZoomIn);
		EnhancedInputComponent->BindAction(ZoomInAction, ETriggerEvent::Completed,
			this, &ABaseCharacter::ResetZoom);

		if (WeaponComponent)
		{
			EnhancedInputComponent->BindAction(ShootAction, ETriggerEvent::Triggered,
				WeaponComponent.Get(), &UWeaponComponent::Fire);
		}

		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered,
			this, &ABaseCharacter::Move);

		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started,
			this, &ABaseCharacter::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed,
			this, &ABaseCharacter::StopJumping);

		EnhancedInputComponent->BindAction(SprintAction, ETriggerEvent::Started,
			this, &ABaseCharacter::Sprint);
		EnhancedInputComponent->BindAction(SprintAction, ETriggerEvent::Completed,
			this, &ABaseCharacter::StopSprinting);

		EnhancedInputComponent->BindAction(CrouchAction, ETriggerEvent::Started,
			this, &ABaseCharacter::Crouch, false);
		EnhancedInputComponent->BindAction(CrouchAction, ETriggerEvent::Completed,
			this, &ABaseCharacter::UnCrouch, false);
	}
}

// Called when the game starts or when spawned
void ABaseCharacter::BeginPlay()
{
	Super::BeginPlay();

	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}
}

void ABaseCharacter::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

}

void ABaseCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	ABaseGameMode* GameMode{ Cast<ABaseGameMode>(UGameplayStatics::GetGameMode(this)) };
	if (GameMode)
	{
		HealthComponent->OnDeath.BindUObject(GameMode, &ABaseGameMode::OnPlayerDeath);
	}
}

inline void ABaseCharacter::Move(const FInputActionValue& Value)
{
	FVector2D MovementVector = Value.Get<FVector2D>();

	const FRotator Rotation = Controller->GetControlRotation();
	const FRotator YawRotation(0, Rotation.Yaw, 0);

	const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
	const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);

	AddMovementInput(ForwardDirection, MovementVector.Y);
	AddMovementInput(RightDirection, MovementVector.X);
}

inline void ABaseCharacter::Look(const FInputActionValue& Value)
{
	FVector2D LookInput = Value.Get<FVector2D>();

	AddControllerYawInput(LookInput.X);
	AddControllerPitchInput(LookInput.Y);
}

inline void ABaseCharacter::ZoomIn()
{
	SpringArm->TargetArmLength = SpringArm->TargetArmLength / ZoomMagnification;
}

inline void ABaseCharacter::ResetZoom()
{
	SpringArm->TargetArmLength = SpringArm->TargetArmLength * ZoomMagnification;
}

inline void ABaseCharacter::Sprint()
{

	if (MovementState != CROUCHING && MovementState != JUMPING)
	{
		MovementState = RUNNING;
		GetCharacterMovement()->MaxWalkSpeed = 800.0f;
	}
	else
	{
		GetCharacterMovement()->MaxWalkSpeed = 600.0f;
	}
}

inline void ABaseCharacter::StopSprinting()
{
	if (MovementState == RUNNING)
	{
		MovementState = WALKING;
		GetCharacterMovement()->MaxWalkSpeed = 600.0f;
	}
}

void ABaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ABaseCharacter::Crouch(bool bClientSimulation)
{
	MovementState = CROUCHING;
	GetCharacterMovement()->MaxWalkSpeed = 200.0f;
}
void ABaseCharacter::UnCrouch(bool bClientSimulation)
{
	MovementState = WALKING;
	GetCharacterMovement()->MaxWalkSpeed = 600.0f;
}