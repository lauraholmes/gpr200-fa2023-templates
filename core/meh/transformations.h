#pragma once
#include "../ew/ewMath/mat4.h"
#include "../ew/ewMath/vec3.h"
#include "../ew/ewMath/ewMath.h"

namespace myLib {
	//Identity matrix
	inline ew::Mat4 Identity() {
		return ew::Mat4(
			1, 0, 0, 0,
			0, 1, 0, 0,
			0, 0, 1, 0,
			0, 0, 0, 1
		);
	};
	//Scale on x,y,z axes
	inline ew::Mat4 Scale(ew::Vec3 s) {
		return ew::Mat4(
			s.x, 0, 0, 0,
			0, s.y, 0, 0,
			0, 0, s.z, 0,
			0, 0, 0, 1
		);
	};
	//Rotation around X axis (pitch) in radians
	inline ew::Mat4 RotateX(float rad) {
		return ew::Mat4(
			1, 0, 0, 0,
			0, cos(rad), -sin(rad), 0,
			0, sin(rad), cos(rad), 0,
			0, 0, 0, 1
		);
	};
	//Rotation around Y axis (yaw) in radians
	inline ew::Mat4 RotateY(float rad) {
		return ew::Mat4(
			cos(rad), 0, sin(rad), 0,
			0, 1, 0, 0,
			-sin(rad), 0, cos(rad), 0,
			0, 0, 0, 1
		);
	};
	//Rotation around Z axis (roll) in radians
	inline ew::Mat4 RotateZ(float rad) {
		return ew::Mat4(
			cos(rad), -sin(rad), 0, 0,
			sin(rad), cos(rad), 0, 0,
			0, 0, 1, 0,
			0, 0, 0, 1
		);
	};
	//Translate x,y,z
	inline ew::Mat4 Translate(ew::Vec3 t) {
		return ew::Mat4(
			1, 0, 0, t.x,
			0, 1, 0, t.y,
			0, 0, 1, t.z,
			0, 0, 0, 1
		);
	};	
	inline ew::Mat4 LookAt(ew::Vec3 eye, ew::Vec3 target, ew::Vec3 up){
	//use ew::Cross for cross product	
		ew::Vec3 camDirection = ew::Normalize(eye - target);
		ew::Vec3 right = ew::Normalize(ew::Cross(up, camDirection));
		ew::Vec3 camUp = ew::Cross(camDirection, right);

		ew::Mat4 m1;
		m1 = ew::Mat4(
		right.x, right.y, right.z, 0,
		camUp.x, camUp.y, camUp.z, 0,
		camDirection.x, camDirection.y, camDirection.z, 0,
		0, 0, 0, 1
		);
		ew::Mat4 m2;
		m2 = ew::Mat4(
		1, 0, 0, -eye.x,
		0, 1, 0, -eye.y,
		0, 0, 1, -eye.z,
		0, 0, 0, 1
		);
		return m1 * m2;
	};

	inline ew::Mat4 Orthographic(float height, float aspect, float near, float far){
		float width = aspect * height;
		float right = width / 2;
		float top = height / 2;
		float left = -1*right;
		float bottom = -1*top;

		return ew::Mat4(
			2/(right-left), 0, 0, -((right+left)/(right-left)),
			0, 2/(top-bottom), 0, -((top+bottom)/(top-bottom)),
			0, 0, -(2/(far - near)), -((far+near)/(far-near)),
			0, 0, 0, 1
		);
	
	};
	inline ew::Mat4 Perspective(float fov, float aspect, float near, float far) {
		float x = ew::Radians(fov);
		return ew::Mat4(
	    1/(tan(x/2)*aspect), 0, 0, 0,
		0, 1/(tan(x/2)), 0, 0,
		0, 0, (far+near)/(near-far), (2*far*near)/(near-far),
		0, 0, -1, 0
		);
	};

	struct Transform {
		ew::Vec3 position = ew::Vec3(0.0f, 0.0f, 0.0f);
		ew::Vec3 rotation = ew::Vec3(0.0f, 0.0f, 0.0f); //Euler angles (degrees)
		ew::Vec3 scale = ew::Vec3(1.0f, 1.0f, 1.0f);
		ew::Mat4 getModelMatrix() const {
			float x = ew::Radians(rotation.x);
			float y = ew::Radians(rotation.y);
			float z = ew::Radians(rotation.z);
			return Translate(position) * RotateY(y) * RotateX(x) * RotateZ(z) * Scale(scale);
		}
	};
}
