#include "../meh/procGen.h"
#include "../ew/mesh.h"
#include "../ew/ewMath/ewMath.h"
#include <stdlib.h>

namespace yourLib {
	ew::MeshData createSphere(float radius, int numSegments)
	{
		ew::MeshData mesh;
		ew::Vertex vertex;
		float thetaStep = (2 * ew::PI) / numSegments;
		float phiStep = ew::PI / numSegments;

		for (int row = 0; row <= numSegments; row++) {
			float phi = row * phiStep;
			for (int column = 0; column <= numSegments; column++) {
				float theta = column * thetaStep;
				float x = radius * cos(theta) * sin(phi);
				float y = radius * cos(phi);
				float z = radius * sin(theta) * sin(phi);

				vertex.pos = ew::Vec3(x, y, z);
				mesh.vertices.push_back(vertex);
			}
		}
		float poleStart = 0;
		float sideStart = numSegments + 1;
		for (int i = 0; i < numSegments; i++) {
			mesh.indices.push_back(sideStart + i);
			mesh.indices.push_back(poleStart + i);
			mesh.indices.push_back(sideStart + i + 1);
		}
		float columns = numSegments + 1;
		for (int row = 1; row < numSegments - 1; row++) {
			for (int column = 0; column < numSegments; column++) {
				float start = row * columns + column;
				mesh.indices.push_back(start);
				mesh.indices.push_back(start + 1);
				mesh.indices.push_back(start + columns);
			}
		}
		return mesh;
	}
	ew::MeshData createCylinder(float height, float radius, int numSegments)
	{
		ew::MeshData mesh;
		ew::Vertex topRing, botRing, topVert, botVert;
		float topY = height / 2;
		float botY = -topY;
		float thetaStep = (2 * ew::PI) / numSegments;

		topVert.pos = ew::Vec3(0, topY, 0);
		mesh.vertices.push_back(topVert);
		for (int i = 0; i <= numSegments; i++) {
			float theta = i * thetaStep;
			float x = cos(theta) * radius;
			float z = sin(theta) * radius;
			float y = topY;

			topRing.pos = ew::Vec3(x, y, z);
			mesh.vertices.push_back(topRing);
		}
		for (int i = 0; i <= numSegments; i++) {
			float theta = i * thetaStep;
			float x = cos(theta) * radius;
			float z = sin(theta) * radius;
			float y = botY;

			botRing.pos = ew::Vec3(x, y, z);
			mesh.vertices.push_back(botRing);
		}
		botVert.pos = ew::Vec3(0, botY, 0);
		mesh.vertices.push_back(botVert);

		float start = 0;
		float center = numSegments;

		for (int i = 0; i <= numSegments; i++) {
			mesh.indices.push_back(start + i);
			mesh.indices.push_back(center);
			mesh.indices.push_back(start + i + 1);
		}

		float sideStart = 0;
		float columns = numSegments + 1;
		for (int i = 0; i < columns; i++) {
			float start = sideStart + i;
			mesh.indices.push_back(start);
			mesh.indices.push_back(start + 1);
			mesh.indices.push_back(start + columns);

			mesh.indices.push_back(start + 1);
			mesh.indices.push_back(start + columns + 1);
			mesh.indices.push_back(start + columns);
		}
		return mesh;
	}
	ew::MeshData createPlane(float width, float height, int subdivisions)
	{
		ew::MeshData mesh;
		ew::Vertex vertex;

		for (float row = 0; row <= subdivisions; row++) {
			for (float column = 0; column <= subdivisions; column++) {
				float x = width * (column / subdivisions);
				float z = -height * (row / subdivisions);

				vertex.pos = ew::Vec3(x, 0, z);
				mesh.vertices.push_back(vertex);
			}
		}


		float columns = subdivisions + 1;
		for (float row = 0; row < subdivisions; row++) {
			for (float column = 0; column < subdivisions; column++) {
				float start = row * columns + column;
				
				mesh.indices.push_back(start);
				mesh.indices.push_back(start + 1);
				mesh.indices.push_back(start + columns + 1);

				mesh.indices.push_back(start);
				mesh.indices.push_back(start + columns);
				mesh.indices.push_back(start + columns + 1);
			}
		}
		return mesh;
	}
}
