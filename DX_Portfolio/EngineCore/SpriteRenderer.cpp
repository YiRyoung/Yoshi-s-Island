#include "PreCompile.h"
#include "SpriteRenderer.h"

USpriteRenderer::USpriteRenderer()
{
}

USpriteRenderer::~USpriteRenderer()
{
}

ENGINEAPI void USpriteRenderer::SetSprite(std::string_view _Name)
{
	SetTexture(_Name);
}

