#include "GameObject.h"
#include "ResourceManager.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Engine.h"
#include "InputManager.h"
#include "RenderComponent.h"

using namespace FME::Graphics;


GameObject::GameObject(const std::string& goName) : IObject()
{
	m_name = goName;
}


void GameObject::Draw()
{
	std::shared_ptr<RenderComponent> rc = std::dynamic_pointer_cast<RenderComponent>(GetComponentByType("Render"));
	if (rc)
	{
		std::string shader = rc->GetShaderName();
		glm::mat4 view, proj;
		if (RENDER3D == rc->GetGameType())	Engine::Instance()->GetCamera(view, proj);
		else
		{
			view = glm::mat4(1.0f);
			proj = glm::mat4(1.0f);
		}
		glm::mat4 model = GetTransformComponent()->GetModelMatrix();;
		glm::mat4 modelViewProj = proj * view * model;
		glm::mat4 transInvModel = transpose(inverse(model));
		FME::Graphics::ResourceManager::Instance()->GetShader(shader).Use();
		glUniformMatrix4fv(glGetUniformLocation(FME::Graphics::ResourceManager::Instance()->GetShader(shader).GetProgramID(), "modelViewProj"), 1, GL_FALSE, glm::value_ptr(modelViewProj));
		glUniformMatrix4fv(glGetUniformLocation(FME::Graphics::ResourceManager::Instance()->GetShader(shader).GetProgramID(), "model"), 1, GL_FALSE, glm::value_ptr(model));
		glUniformMatrix4fv(glGetUniformLocation(FME::Graphics::ResourceManager::Instance()->GetShader(shader).GetProgramID(), "transInvModel"), 1, GL_FALSE, glm::value_ptr(transInvModel));
		for (int i = 0; i < m_components.size(); ++i)
		{
			if (m_components[i]->GetType() != rc->GetType())
			{
				m_components[i]->Draw();
			}
		}
		rc->Draw();
		FME::Graphics::ResourceManager::Instance()->GetShader(shader).UnUse();
	}
	else
	{
		for (int i = 0; i < m_components.size(); ++i)
		{		
			m_components[i]->Draw();		
		}
	}
}



void GameObject::Update(double deltaTime)
{
	for (int i = 0; i < m_components.size(); ++i)
	{
		m_components[i]->Update();
	}
}