// Fill out your copyright notice in the Description page of Project Settings.


#include "MaskSlateWidgetStyle.h"

FMaskSlateStyle::FMaskSlateStyle()
{
}

FMaskSlateStyle::~FMaskSlateStyle()
{
}

const FName FMaskSlateStyle::TypeName(TEXT("FMaskSlateStyle"));

const FMaskSlateStyle& FMaskSlateStyle::GetDefault()
{
	static FMaskSlateStyle Default;
	return Default;
}

void FMaskSlateStyle::GetResources(TArray<const FSlateBrush*>& OutBrushes) const
{
	// Add any brush resources here so that Slate can correctly atlas and reference them
}

