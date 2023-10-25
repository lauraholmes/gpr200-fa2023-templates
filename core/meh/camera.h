#pragma once
#include "../ew/ewMath/mat4.h"
#include "../ew/ewMath/vec3.h"
#include "../ew/ewMath/ewMath.h"
#include "../meh/transformations.h"

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
	};
}
