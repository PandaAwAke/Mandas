#pragma once

#ifdef MD_PLATFORM_WINDOWS

extern Mandas::Application* Mandas::CreateApplication();

int main(int argc, char** argv)
{
	printf(">>> Welcome to Mandas Engine! <<<\n");
	Mandas::Log::Init();

	auto App = Mandas::CreateApplication();

	App->Run();

	delete App;
}


#endif