// Fill out your copyright notice in the Description page of Project Settings.


#include "cp_AnimNotifyState.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"

void Ucp_AnimNotifyState::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration)
{
    if (MeshComp && MeshComp->GetOwner())
    {
        //UE_LOG(LogTemp, Warning, TEXT("Notify Begin Triggered: Montage Started"));
        //UKismetSystemLibrary::PrintString(MeshComp->GetWorld(), TEXT("Notify Begin Triggered: Montage Started"), true, true, FLinearColor::Green, 2.0f);
    }

}

void Ucp_AnimNotifyState::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
    if (MeshComp && MeshComp->GetOwner())
    {
        //UE_LOG(LogTemp, Warning, TEXT("Notify End Triggered: Montage Ended"));
        //UKismetSystemLibrary::PrintString(MeshComp->GetWorld(), TEXT("Notify End Triggered: Montage Ended"), true, true, FLinearColor::Red, 2.0f);
    }
}
void Ucp_AnimNotifyState::NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime)
{
    if (MeshComp && MeshComp->GetOwner())
    {
        //UE_LOG(LogTemp, Warning, TEXT("Notify tick Triggered: Montage is playing"));
        //UKismetSystemLibrary::PrintString(MeshComp->GetWorld(), TEXT("Notify tick Triggered: Montage is playing"), true, true, FLinearColor::Red, 2.0f);
    
  
        //Asurvival_templateCharacter* Player = Cast<Asurvival_templateCharacter>(OtherActor);
         // Correct method to access the player
        Asurvival_templateCharacter* Player = Cast<Asurvival_templateCharacter>(MeshComp->GetOwner());

        Player->PerformWeaponTrace();


    }
}