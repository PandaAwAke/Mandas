#include "mdpch.h"
#include <Mandas.h>
#include <Mandas/Core/EntryPoint.h>

#include "EditorLayer.h"

namespace Mandas {

	class MandasEditor : public Mandas::Application
	{
	public:
		MandasEditor()
			: Application("Mandas Editor")
		{
			PushLayer(new EditorLayer());
		}

		~MandasEditor()
		{

		}

	};

	Mandas::Application* Mandas::CreateApplication()
	{
		return new MandasEditor();
	}

}
