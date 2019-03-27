// Fill out your copyright notice in the Description page of Project Settings.

#include "FPSHUD.h"

void AFPSHUD::DrawHUD()
{
	Super::DrawHUD();

	if (CrosshairTexture)
	{
		// ��������
		FVector2D Center(Canvas->ClipX * 0.5f, Canvas->ClipY * 0.5f);

		// ����ά�Ƚ���һ��ƫ�ƣ�ʹ�������ĺͻ������Ķ��롣
		FVector2D CrosshairDrawPosition(Center.X - (CrosshairTexture->GetSurfaceWidth() * 0.5f),
			Center.Y - (CrosshairTexture->GetSurfaceWidth() * 0.5f));

		// �����ĵ����׼�ǡ�
		FCanvasTileItem TileItem(CrosshairDrawPosition, CrosshairTexture->Resource, FLinearColor::White);
		TileItem.BlendMode = SE_BLEND_Translucent;
		Canvas->DrawItem(TileItem);
	}
}
