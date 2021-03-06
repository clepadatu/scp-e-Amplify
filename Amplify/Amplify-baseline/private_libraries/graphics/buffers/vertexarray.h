#pragma once

#include <GL\glew.h>
#include "buffer.h"
#include <vector>

namespace Erebos{
	namespace graphics{
		class VertexArray
		{
		private:
			GLuint m_ArrayID;
			std::vector<Buffer*> m_Buffers;

		public:
			VertexArray();
			~VertexArray();
			void addBuffer(Buffer* buffer, GLuint index);
			void bind() const;
			void unbind() const;
		};

	}
}
