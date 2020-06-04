#include "bepch.h"
#include "Camera.h"

namespace BE
{

	  /////////////////////////////////////////////////////
	 ///////////ORTHOGRAPHIC//////////////////////////////
	/////////////////////////////////////////////////////

	OrthographicCamera::OrthographicCamera(float left, float right, float bottom, float top)
		: m_ProjectionMatrix(glm::ortho(left, right, bottom, top, -1.0f, 1.0f)), m_ViewMatrix(1.0f)
	{
		m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix; 
	}

	void OrthographicCamera::RecalculateViewMatrix() 
	{
		glm::mat4 transform = glm::translate(glm::mat4(1.0f), m_Position)
							* glm::rotate(glm::mat4(1.0f),
							  glm::radians(m_Rotation),
							  glm::vec3(0,0,1));

		m_ViewMatrix = glm::inverse(transform);
		m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
	}


	  ////////////////////////////////////////////////////
	 ///////////PERSPECTIVE//////////////////////////////
	////////////////////////////////////////////////////

	PerspectiveCamera::PerspectiveCamera(float FOV, float aspectRatio, float nearPlane, float farPlane)
		: m_ProjectionMatrix(glm::perspective(glm::radians(FOV), aspectRatio, nearPlane, farPlane))
	{
		m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
	}
	void PerspectiveCamera::RecalculateViewMatrix()
	{


	}
}