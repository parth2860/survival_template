// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "survival_template/survival_templateCharacter.h"
#include "cp_AnimNotifyState.generated.h"

/**
 * 
 */
UCLASS()
class SURVIVAL_TEMPLATE_API Ucp_AnimNotifyState : public UAnimNotifyState
{
	GENERATED_BODY()

	// Called when montage starts
	virtual void NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration) override;

	// Called when montage ends
	virtual void NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;

	// Called every frame while the notify is active
	virtual void NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime) override;
	
};
