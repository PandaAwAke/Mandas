#pragma once

#ifdef MD_PLATFORM_WINDOWS

extern Mandas::Application* Mandas::CreateApplication();

int main(int argc, char** argv)
{
	// printf(">>> Entering Mandas Engine <<<\n");
	Mandas::Log::Init();
	MD_CORE_WARN("Initialized Log!");
	int a = 5;
	MD_INFO("Hello! Var={0}", a);

	auto App = Mandas::CreateApplication();

	App->Run();

	delete App;
}


#endif