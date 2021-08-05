// Copyright BitPatterns Cybersys 2021.

#include "Grabber.h"

// Sets default values for this component's properties
UGrabber::UGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

}


// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();

	// ...
	//UE_LOG(LogTemp, Warning, TEXT("Grabber reporting for duty9988!!!!!!"));

	FindPhysicsHandleComponent();
	SetUpInputComponent();
	
}


void UGrabber::FindPhysicsHandleComponent()
{
	//Look for attached Physics handle
	PhysicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();

	if (PhysicsHandle) {

	}
	else {
		UE_LOG(LogTemp, Error, TEXT("The physics handle for %s,  is missing"), *(GetOwner()->GetName()));
	}
}

void UGrabber::SetUpInputComponent()
{
	//Look for Input Component
	InputComponent = GetOwner()->FindComponentByClass<UInputComponent>();

	if (InputComponent) {
		UE_LOG(LogTemp, Error, TEXT("The input component found 99933 "));
		//Bind the input axis
		InputComponent->BindAction("Grab", IE_Pressed, this, &UGrabber::Grab);
		InputComponent->BindAction("Grab", IE_Released, this, &UGrabber::Release);

	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("The Input Component for %s,  is missing"), *(GetOwner()->GetName()));
	}


}

const FHitResult UGrabber::GetFirstPhysicsBodyInReach()
{
	//Get player viewpoint 

	//UE_LOG(LogTemp, Warning, TEXT("Grabber reporting for duty9988!!!!!!"));

	FVector PlayerViewPointLocation;
	FRotator PlayerViewPointRotation;

	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(PlayerViewPointLocation, PlayerViewPointRotation);

	//UE_LOG(LogTemp, Warning, TEXT("The %s position is %s"), *ObjectName, *ObjectPosition);

	//UE_LOG(LogTemp, Warning, TEXT("Position is:  %s,  Rotation is: %s"), *PlayerViewPointLocation.ToString(), *PlayerViewPointRotation.ToString());

	//Draw a red trace in the world to visualise
	//DrawDebugLine(GetWorld(), PlayerViewPointLocation, LineTraceEnd, color, false, -1.0f, 0, 5.f);

	FColor color = { 255, 0, 0, 0 }; // red

	FVector LineTraceEnd = PlayerViewPointLocation + PlayerViewPointRotation.Vector() * Reach;

	//Ray -cast (line trace)  out to reach distance 

	//set up query parameters
	FHitResult Hit;

	GetWorld()->LineTraceSingleByObjectType(
		Hit,
		PlayerViewPointLocation,
		LineTraceEnd,
		FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody),
		FCollisionQueryParams(FName(TEXT("")), false, GetOwner())
	);



	if (Hit.GetActor()) {
		FString actorName = Hit.GetActor()->GetName();
		UE_LOG(LogTemp, Warning, TEXT("I am hitting : %s"), *actorName);
	}

	/*AActor * actor = Hit.GetActor();

	if (actor) {

		UE_LOG(LogTemp, Warning, TEXT("I am hitting : %s"), *actor->GetName());
	}*/


	return FHitResult();
}


void UGrabber::Grab() {
	UE_LOG(LogTemp, Warning, TEXT("Grab pressed"));

	// Line trace and Try and reach any actors with physics body collision channel set
	GetFirstPhysicsBodyInReach();

	// if we hit something attach a physics handle
}

void UGrabber::Release() {
	UE_LOG(LogTemp, Warning, TEXT("Grab released"));

	//Relese Physiscs
}

// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	

}

