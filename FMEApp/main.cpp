
#include <iostream>
#include <chrono>
#include <experimental/filesystem>

#include "FullMetalEngine.h"


int main()
{
	FME::Graphics::FullMetalEngine fme;
	fme.SetFPS(30.0);
	fme.SetWindowSize(2560, 1440);
	fme.SetScene("scene.json");
	fme.SetEffects("effects.json");

	std::chrono::duration<double> diff(0.0);

	while (fme.Alive())
	{
		std::chrono::time_point<std::chrono::system_clock> start = std::chrono::system_clock::now();

		fme.Update(diff.count());
		fme.Draw();
		std::chrono::time_point<std::chrono::system_clock> end = std::chrono::system_clock::now();

		diff = end - start;
	}

	return 0;
}



#if 0
void frameLoader()
{
	std::vector<unsigned char*> texturesToUpdate;
	std::vector<std::string> texturePaths;
	std::string path = "D:/Dev/Data/video/CarCameraRigTop/";

	std::experimental::filesystem::directory_iterator path_it(path);
	std::experimental::filesystem::directory_iterator end_it;
	int width, height, channels;
	int i = 0;

	while (path_it != end_it)
	{
		++i;
		if (i < 55) continue;
		if (i > 100) break;
		std::vector<unsigned char*> vec;
		texturePaths.push_back(path_it->path().string());
		std::string texturePath = path_it->path().string();
		++path_it;
		unsigned char* image = SOIL_load_image(texturePath.c_str(), &width, &height, &channels, false);
		//texturesToUpdate.push_back(image);		
		vec.push_back(image);
		//FME::Graphics::Engine::Instance()->PushFrame(texturesToUpdate[texturesToUpdate.size() - 1], 1920, 1080, true, i  - 1);
		FME::Graphics::Engine::Instance()->PushFrame(vec, width, height, true, i - 1);
		std::this_thread::sleep_for(std::chrono::milliseconds(33));
	}
}

void SkyBoxLoader()
{
	std::vector<unsigned char*> texturesToUpdate;
	std::vector<std::vector<unsigned char*>> textures;
	std::string path = "D:/Dev/Data/video/skybox/Movies/Angle0New/Frame";
	int width, height, channels;

	for (int frame = 0; frame < 70; ++frame)
	{
		std::vector<unsigned char*> data;

		std::string texturePath = path + std::to_string(frame) + "/";
		std::vector<std::string> faces{
			texturePath + "posx.jpg",
			texturePath + "negx.jpg",
			texturePath + "posy.jpg",
			texturePath + "negy.jpg",
			texturePath + "posz.jpg",
			texturePath + "negz.jpg"
		};

		for (int i = 0; i < faces.size(); ++i)
		{
			std::string textureName = texturePath + faces[i];
			unsigned char* image = SOIL_load_image(faces[i].c_str(), &width, &height, &channels, false);
			data.push_back(image);
		}
		textures.push_back(data);
		FME::Graphics::Engine::Instance()->PushFrame(textures[frame], width, height, true, frame);
		//std::this_thread::sleep_for(std::chrono::milliseconds(33));
	}

	/*for(int frame = 0; frame < textures.size(); ++frame)
	{
	FME::Graphics::Engine::Instance()->PushFrame(textures[frame], width, height, true, frame);
	//std::this_thread::sleep_for(std::chrono::milliseconds(33));
	}*/
}
#endif