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


// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	//Draw a red trace in the world to visualise
	//FColor color = { 255, 0, 0, 0 }; // red
	/*float Reach3 = 30.f;

	FVector PlayerViewPointLocation;
	FRotator PlayerViewPointRotation;
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(PlayerViewPointLocation, PlayerViewPointRotation);
	FVector LineTraceEnd = PlayerViewPointLocation + PlayerViewPointRotation.Vector() * Reach3;

	DrawDebugLine(GetWorld(), GetReachLineStart(), LineTraceEnd, color, false, -1.0f, 5, 1.f);*/

	if (!PhysicsHandle) { return; }

	if (PhysicsHandle->GrabbedComponent) 
	{
		PhysicsHandle->SetTargetLocation(GetReachLineEnd());
	}
}

FVector UGrabber::GetReachLineEnd()
{
	FVector PlayerViewPointLocation;
	FRotator PlayerViewPointRotation;
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(PlayerViewPointLocation, PlayerViewPointRotation);
	FVector LineTraceEnd = PlayerViewPointLocation + PlayerViewPointRotation.Vector() * Reach;

	return LineTraceEnd;
}

FVector UGrabber::GetReachLineStart()
{
	FVector PlayerViewPointLocation;
	FRotator PlayerViewPointRotation;
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(PlayerViewPointLocation, PlayerViewPointRotation);

	return PlayerViewPointLocation;
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
		//UE_LOG(LogTemp, Error, TEXT("The input component found "));
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
	//UE_LOG(LogTemp, Warning, TEXT("The %s position is %s"), *ObjectName, *ObjectPosition);
	//UE_LOG(LogTemp, Warning, TEXT("Position is:  %s,  Rotation is: %s"), *PlayerViewPointLocation.ToString(), *PlayerViewPointRotation.ToString());

	FColor color = { 255, 0, 0, 0 }; // red

	
	
	//Ray -cast (line trace)  out to reach distance 

	//set up query parameters
	FHitResult HitResult;

	GetWorld()->LineTraceSingleByObjectType(
		HitResult,
		GetReachLineStart(),
		GetReachLineEnd(),
		FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody),
		FCollisionQueryParams(FName(TEXT("")), false, GetOwner())
	);

	if (HitResult.GetActor()) {
		FString actorName = HitResult.GetActor()->GetName();
		UE_LOG(LogTemp, Warning, TEXT("I am hitting : %s"), *actorName);
	}

	return HitResult;
}


void UGrabber::Grab() {
	UE_LOG(LogTemp, Warning, TEXT("Grab pressed"));

	// Line trace and Try and reach any actors with physics body collision channel set
	auto HitResult=GetFirstPhysicsBodyInReach();

	UPrimitiveComponent* ComponentToGrab = HitResult.GetComponent();

	auto ActorHit = HitResult.GetActor();

	// if we hit something attach a physics handle
	if (ActorHit) {

		/*PhysicsHandle->GrabComponentAtLocation(
			ComponentToGrab, 
			NAME_None, 
			ComponentToGrab->GetOwner()->GetActorLocation()
		);*/
		if (!PhysicsHandle) { return; }
		PhysicsHandle->GrabComponentAtLocationWithRotation(
			ComponentToGrab, 
			NAME_None, 
			ComponentToGrab->GetOwner()->GetActorLocation(), 
			ComponentToGrab->GetOwner()->GetActorRotation()
		);		
	}
}

void UGrabber::Release() {
	UE_LOG(LogTemp, Warning, TEXT("Grab released"));
	//Relese Physiscs
	if (!PhysicsHandle) { return; } 
	PhysicsHandle->ReleaseComponent();
}

