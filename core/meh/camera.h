#pragma once
#include "../ew/ewMath/mat4.h"
#include "../ew/ewMath/vec3.h"
#include "../ew/ewMath/ewMath.h"
#include "../meh/transformations.h"
#include <imgui_impl_glfw.h>
#include <GLFW/glfw3.h>

namespace myLib {
	struct Camera {
		ew::Vec3 position = ew::Vec3(0.0f, 0.0f, 5.0f); //Camera body position
		ew::Vec3 target = ew::Vec3(0.0f, 0.0f, 0.0f); //Position to look at
		float fov = 60.0f; //Vertical field of view in degrees
		float aspectRatio; //Screen width / Screen height
		float nearPlane = 0.1f; //Near plane distance (+Z)
		float farPlane = 100.0f; //Far plane distance (+Z)
		bool orthographic; //Perspective or orthographic?
		float orthoSize = 6.0f; //Height of orthographic frustum
		ew::Mat4 ViewMatrix() {
			return LookAt(position, target, ew::Vec3(0.0f, 1.0f, 0.0f));
		}; //World->View
		ew::Mat4 ProjectionMatrix() {
			if (orthographic == false) {
				return Perspective(fov, aspectRatio, nearPlane, farPlane);
			}
			else
				return Orthographic(orthoSize, aspectRatio, nearPlane, farPlane);
		}; //View->Clip
	};

	struct CameraControls {
		double prevMouseX, prevMouseY; //Mouse position from previous frame
		float yaw = 0, pitch = 0; //Degrees
		float mouseSensitivity = 0.1f; //How fast to turn with mouse
		bool firstMouse = true; //Flag to store initial mouse position
		float moveSpeed = 5.0f; //How fast to move with arrow keys (M/S)
		void moveCamera(GLFWwindow* window, Camera* camera, CameraControls* controls, float time) {
			//If right mouse is not held, release cursor and return early.
			if (!glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_2)) {
				//Release cursor
				glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
				controls->firstMouse = true;
				return;
			}
			//GLFW_CURSOR_DISABLED hides the cursor, but the position will still be changed as we move our mouse.
			glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

			//Get screen mouse position this frame
			double mouseX, mouseY;
			glfwGetCursorPos(window, &mouseX, &mouseY);

			//If we just started right clicking, set prevMouse values to current position.
			//This prevents a bug where the camera moves as soon as we click.
			if (controls->firstMouse) {
				controls->firstMouse = false;
				controls->prevMouseX = mouseX;
				controls->prevMouseY = mouseY;
			}

			//TODO: Get mouse position delta for this frame
			float xOffSet = mouseX - controls->prevMouseX;
			float yOffSet = mouseY - controls->prevMouseY;
			xOffSet *= controls->mouseSensitivity;
			yOffSet *= controls->mouseSensitivity;
			
			//TODO: Add to yaw and pitch
			controls->yaw += xOffSet;
			controls->pitch += yOffSet;
			
			//TODO: Clamp pitch between -89 and 89 degrees

			if (pitch > 89.0f)
				pitch = 89.0f;
			if (pitch < -89.0f)
				pitch = -89.0f;

			//Remember previous mouse position
			controls->prevMouseX = mouseX;
			controls->prevMouseY = mouseY;
			//Construct forward vector using yaw and pitch. Don't forget to convert to radians!
			float rYaw = ew::Radians(controls->yaw);
			float rPitch = ew::Radians(controls->pitch);
			ew::Vec3 forward = ew::Vec3(cos(rYaw)*cos(rPitch), sin(rPitch), sin(rYaw)*cos(rPitch));
			//By setting target to a point in front of the camera along its forward direction, our LookAt will be updated accordingly when rendering.
			camera->target = camera->position + forward;
			//TODO: Using camera forward and world up (0,1,0), construct camera right and up vectors. Graham-schmidt process!
			ew::Vec3 worldUp = ew::Vec3(0.0f, 1.0f, 0.0f);
			ew::Vec3 up;
			ew::Vec3 right;


			right = ew::Normalize(ew::Cross(forward, worldUp));
			up = ew::Normalize(ew::Cross(right, forward));
				//TODO: Keyboard controls for moving along forward, back, right, left, up, and down. See Requirements for key mappings.
				//EXAMPLE: Moving along forward axis if W is held.
				//Note that this is framerate dependent, and will be very fast until you scale by deltaTime. See the next section.
			if (glfwGetKey(window, GLFW_KEY_W)) { //forward
				camera->position += forward * controls->moveSpeed * time;
			}
			if (glfwGetKey(window, GLFW_KEY_D)) { //right
				camera->position += right * controls->moveSpeed*time;
			}
			if (glfwGetKey(window, GLFW_KEY_A)) { //left
				camera->position += -(right) * controls->moveSpeed*time;
			}
			if (glfwGetKey(window, GLFW_KEY_S)) { //backwards
				camera->position += -(forward)*controls->moveSpeed*time;
			}
			if (glfwGetKey(window, GLFW_KEY_Q)) { //up
				camera->position += up*controls->moveSpeed*time;
			}
			if (glfwGetKey(window, GLFW_KEY_E)) { //down
				camera->position += -(up)*controls->moveSpeed*time;
			}

			//Setting camera.target should be done after changing position. Otherwise, it will use camera.position from the previous frame and lag behind
			camera->target = camera->position + forward;




		};
	
	};
}
