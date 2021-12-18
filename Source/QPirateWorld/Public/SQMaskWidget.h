// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widgets/SCompoundWidget.h"
#include "MaskSlateWidgetStyle.h"

/**
 * 
 */
class QPIRATEWORLD_API SQMaskWidget : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SQMaskWidget)
		: _MaskPosition(FVector2D::ZeroVector), 
		_MaskSize(FVector2D(1, 1)),
		_MaskStyle()
	{
		//: _Style(&FCoreStyle::Get().GetWidgetStyle<FMaskSlateSlate>("MaskWidget"))
		_MaskStyle = FCoreStyle::Get().GetWidgetStyle<FMaskSlateStyle>("MaskWidgetStyle");
		//DECLARE_DELEGATE_RetVal(FReply, FOnClicked)
	}

	SLATE_ARGUMENT(FMaskSlateStyle, MaskStyle)

	SLATE_ATTRIBUTE(FVector2D, MaskPosition)
	
	SLATE_ATTRIBUTE(FVector2D, MaskSize)
	SLATE_END_ARGS()

	/** Constructs this widget with InArgs */
	void Construct(const FArguments& InArgs);


};
