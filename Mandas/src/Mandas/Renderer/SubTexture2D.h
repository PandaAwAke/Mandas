#pragma once

#include <glm/glm.hpp>

#include "Texture.h"

namespace Mandas {

	class SubTexture2D
	{
	public:
		virtual ~SubTexture2D() = default;

		SubTexture2D(const Ref<Texture2D>& texture, const glm::vec2& min, const glm::vec2& max);
	
		inline const Ref<Texture2D> GetTexture() const { return m_Texture; }
		inline const glm::vec2* GetTexCoords() const { return m_TexCoords; }
	
		static Ref<SubTexture2D> CreateFromCoords(const Ref<Texture2D>& texture, const glm::vec2& coords, const glm::vec2& cellSize, const glm::vec2& spriteSize = { 1, 1 });
	private:
		Ref<Texture2D> m_Texture;

		glm::vec2 m_TexCoords[4];
	};

}