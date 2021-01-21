#pragma once

#ifdef MD_PLATFORM_WINDOWS

extern Mandas::Application* Mandas::CreateApplication();

int main(int argc, char** argv)
{
	printf(">>> Welcome to Mandas Engine! <<<\n");
	Mandas::Log::Init();

	MD_PROFILE_BEGIN_SESSION("Startup", "MandasProfile-Startup.json");
	auto App = Mandas::CreateApplication();
	MD_PROFILE_END_SESSION();

	MD_PROFILE_BEGIN_SESSION("Startup", "MandasProfile-Runtime.json");
	App->Run();
	MD_PROFILE_END_SESSION();

	MD_PROFILE_BEGIN_SESSION("Startup", "MandasProfile-Shutdown.json");
	delete App;
	MD_PROFILE_END_SESSION();
}


#endif