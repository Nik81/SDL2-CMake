#pragma once
#include <vector>
#include <fstream>
#include <string>
#include <strstream>

// Created a 2D structure to hold texture coordinates
class vec2d
{
public:
	vec2d(){}
	vec2d(float u, float v) { this->u = u; this->v = v; }

	float u = 0;
	float v = 0;
	float w = 1;
};

class vec3d
{
public:
	vec3d(){}
	vec3d(float x, float y, float z) { this->x = x; this->y = y; this->z = z;	}

	float x = 0;
	float y = 0;
	float z = 0;
	float w = 1; // Need a 4th term to perform sensible matrix vector multiplication
};

class triangle
{
public:
	triangle() {}

	vec3d p[3];
	vec2d t[3]; // added a texture coordinates per vertex
	wchar_t sym;
	short col;
};

class mesh
{
public:
	mesh() {}

	std::vector<triangle> tris;

	bool LoadFromObjectFile(std::string filename, bool hasTexture = false)
	{
		std::ifstream f(filename);
		if (!f.is_open())
			return false;

		// Local cache of verts
		std::vector<vec3d> verts;
		std::vector<vec2d> texs;

		while (!f.eof())
		{
			char line[128];
			f.getline(line, 128);

			std::strstream s;
			s << line;

			char junk;

			if (line[0] == 'v')
			{
				if (line[1] == 't')
				{
					vec2d v;
					s >> junk >> junk >> v.u >> v.v;
					// A little hack for the spyro texture
					//v.u = 1.0f - v.u;
					//v.v = 1.0f - v.v;
					texs.push_back(v);
				}
				else
				{
					vec3d v;
					s >> junk >> v.x >> v.y >> v.z;
					verts.push_back(v);
				}
			}

			if (!hasTexture)
			{
				if (line[0] == 'f')
				{
					int f[3];
					s >> junk >> f[0] >> f[1] >> f[2];
					tris.push_back({ verts[f[0] - 1], verts[f[1] - 1], verts[f[2] - 1] });
				}
			}
			else
			{
				if (line[0] == 'f')
				{
					s >> junk;

					std::string tokens[6];
					int nTokenCount = -1;


					while (!s.eof())
					{
						char c = s.get();
						if (c == ' ' || c == '/')
							nTokenCount++;
						else
							tokens[nTokenCount].append(1, c);
					}

					tokens[nTokenCount].pop_back();


					tris.push_back({ verts[stoi(tokens[0]) - 1], verts[stoi(tokens[2]) - 1], verts[stoi(tokens[4]) - 1],
						texs[stoi(tokens[1]) - 1], texs[stoi(tokens[3]) - 1], texs[stoi(tokens[5]) - 1] });
				}
			}
		}
		return true;
	}
};

class mat4x4
{
public:

	float m[4][4] = { 0 };
};

class Math3D
{
public:

	// Mat4x4
	static vec3d Matrix_MultiplyVector(mat4x4 &m, vec3d &i)
	{
		vec3d v;
		v.x = i.x * m.m[0][0] + i.y * m.m[1][0] + i.z * m.m[2][0] + i.w * m.m[3][0];
		v.y = i.x * m.m[0][1] + i.y * m.m[1][1] + i.z * m.m[2][1] + i.w * m.m[3][1];
		v.z = i.x * m.m[0][2] + i.y * m.m[1][2] + i.z * m.m[2][2] + i.w * m.m[3][2];
		v.w = i.x * m.m[0][3] + i.y * m.m[1][3] + i.z * m.m[2][3] + i.w * m.m[3][3];
		return v;
	}

	static mat4x4 Matrix_MakeIdentity()
	{
		mat4x4 matrix;
		matrix.m[0][0] = 1.0f;
		matrix.m[1][1] = 1.0f;
		matrix.m[2][2] = 1.0f;
		matrix.m[3][3] = 1.0f;
		return matrix;
	}

	static mat4x4 Matrix_MakeRotationX(float fAngleRad)
	{
		mat4x4 matrix;
		matrix.m[0][0] = 1.0f;
		matrix.m[1][1] = cosf(fAngleRad);
		matrix.m[1][2] = sinf(fAngleRad);
		matrix.m[2][1] = -sinf(fAngleRad);
		matrix.m[2][2] = cosf(fAngleRad);
		matrix.m[3][3] = 1.0f;
		return matrix;
	}

	static mat4x4 Matrix_MakeRotationY(float fAngleRad)
	{
		mat4x4 matrix;
		matrix.m[0][0] = cosf(fAngleRad);
		matrix.m[0][2] = sinf(fAngleRad);
		matrix.m[2][0] = -sinf(fAngleRad);
		matrix.m[1][1] = 1.0f;
		matrix.m[2][2] = cosf(fAngleRad);
		matrix.m[3][3] = 1.0f;
		return matrix;
	}

	static mat4x4 Matrix_MakeRotationZ(float fAngleRad)
	{
		mat4x4 matrix;
		matrix.m[0][0] = cosf(fAngleRad);
		matrix.m[0][1] = sinf(fAngleRad);
		matrix.m[1][0] = -sinf(fAngleRad);
		matrix.m[1][1] = cosf(fAngleRad);
		matrix.m[2][2] = 1.0f;
		matrix.m[3][3] = 1.0f;
		return matrix;
	}

	static mat4x4 Matrix_MakeTranslation(float x, float y, float z)
	{
		mat4x4 matrix;
		matrix.m[0][0] = 1.0f;
		matrix.m[1][1] = 1.0f;
		matrix.m[2][2] = 1.0f;
		matrix.m[3][3] = 1.0f;
		matrix.m[3][0] = x;
		matrix.m[3][1] = y;
		matrix.m[3][2] = z;
		return matrix;
	}

	static mat4x4 Matrix_MakeProjection(float fFovDegrees, float fAspectRatio, float fNear, float fFar)
	{
		float fFovRad = 1.0f / tanf(fFovDegrees * 0.5f / 180.0f * 3.14159f);
		mat4x4 matrix;
		matrix.m[0][0] = fAspectRatio * fFovRad;
		matrix.m[1][1] = fFovRad;
		matrix.m[2][2] = fFar / (fFar - fNear);
		matrix.m[3][2] = (-fFar * fNear) / (fFar - fNear);
		matrix.m[2][3] = 1.0f;
		matrix.m[3][3] = 0.0f;
		return matrix;
	}

	static mat4x4 Matrix_MultiplyMatrix(mat4x4 &m1, mat4x4 &m2)
	{
		mat4x4 matrix;
		for (int c = 0; c < 4; c++)
			for (int r = 0; r < 4; r++)
				matrix.m[r][c] = m1.m[r][0] * m2.m[0][c] + m1.m[r][1] * m2.m[1][c] + m1.m[r][2] * m2.m[2][c] + m1.m[r][3] * m2.m[3][c];
		return matrix;
	}

	static mat4x4 Matrix_PointAt(vec3d &pos, vec3d &target, vec3d &up)
	{
		// Calculate new forward direction
		vec3d newForward = Vector_Sub(target, pos);
		newForward = Vector_Normalise(newForward);

		// Calculate new Up direction
		vec3d a = Vector_Mul(newForward, Vector_DotProduct(up, newForward));
		vec3d newUp = Vector_Sub(up, a);
		newUp = Vector_Normalise(newUp);

		// New Right direction is easy, its just cross product
		vec3d newRight = Vector_CrossProduct(newUp, newForward);

		// Construct Dimensioning and Translation Matrix	
		mat4x4 matrix;
		matrix.m[0][0] = newRight.x;	matrix.m[0][1] = newRight.y;	matrix.m[0][2] = newRight.z;	matrix.m[0][3] = 0.0f;
		matrix.m[1][0] = newUp.x;		matrix.m[1][1] = newUp.y;		matrix.m[1][2] = newUp.z;		matrix.m[1][3] = 0.0f;
		matrix.m[2][0] = newForward.x;	matrix.m[2][1] = newForward.y;	matrix.m[2][2] = newForward.z;	matrix.m[2][3] = 0.0f;
		matrix.m[3][0] = pos.x;			matrix.m[3][1] = pos.y;			matrix.m[3][2] = pos.z;			matrix.m[3][3] = 1.0f;
		return matrix;

	}

	static mat4x4 Matrix_QuickInverse(mat4x4 &m) // Only for Rotation/Translation Matrices
	{
		mat4x4 matrix;
		matrix.m[0][0] = m.m[0][0]; matrix.m[0][1] = m.m[1][0]; matrix.m[0][2] = m.m[2][0]; matrix.m[0][3] = 0.0f;
		matrix.m[1][0] = m.m[0][1]; matrix.m[1][1] = m.m[1][1]; matrix.m[1][2] = m.m[2][1]; matrix.m[1][3] = 0.0f;
		matrix.m[2][0] = m.m[0][2]; matrix.m[2][1] = m.m[1][2]; matrix.m[2][2] = m.m[2][2]; matrix.m[2][3] = 0.0f;
		matrix.m[3][0] = -(m.m[3][0] * matrix.m[0][0] + m.m[3][1] * matrix.m[1][0] + m.m[3][2] * matrix.m[2][0]);
		matrix.m[3][1] = -(m.m[3][0] * matrix.m[0][1] + m.m[3][1] * matrix.m[1][1] + m.m[3][2] * matrix.m[2][1]);
		matrix.m[3][2] = -(m.m[3][0] * matrix.m[0][2] + m.m[3][1] * matrix.m[1][2] + m.m[3][2] * matrix.m[2][2]);
		matrix.m[3][3] = 1.0f;
		return matrix;
	}

	// Vector
	static vec3d Vector_Add(vec3d &v1, vec3d &v2)
	{
		return{ v1.x + v2.x, v1.y + v2.y, v1.z + v2.z };
	}

	static vec3d Vector_Sub(vec3d &v1, vec3d &v2)
	{
		return{ v1.x - v2.x, v1.y - v2.y, v1.z - v2.z };
	}

	static vec3d Vector_Mul(vec3d &v1, float k)
	{
		return{ v1.x * k, v1.y * k, v1.z * k };
	}

	static vec3d Vector_Div(vec3d &v1, float k)
	{
		return{ v1.x / k, v1.y / k, v1.z / k };
	}

	static float Vector_DotProduct(vec3d &v1, vec3d &v2)
	{
		return v1.x*v2.x + v1.y*v2.y + v1.z * v2.z;
	}

	static float Vector_Magnitude(vec3d &v1)
	{
		return std::sqrt(v1.x * v1.x + v1.y * v1.y + v1.z * v1.z);
	}

	static float Vector_Norm2(vec3d &v1)
	{
		return v1.x * v1.x + v1.y * v1.y + v1.z * v1.z;
	}

	static float Vector_Norm(vec3d &v1)
	{
		return sqrt(Vector_Norm2(v1));
	}

	static float Vector_Length(vec3d &v)
	{
		return sqrtf(Vector_DotProduct(v, v));
	}

	static vec3d Vector_Normalise(vec3d &v)
	{
		float l = Vector_Length(v);
		return{ v.x / l, v.y / l, v.z / l };
	}

	static vec3d Vector_CrossProduct(vec3d &v1, vec3d &v2)
	{
		vec3d v;
		v.x = v1.y * v2.z - v1.z * v2.y;
		v.y = v1.z * v2.x - v1.x * v2.z;
		v.z = v1.x * v2.y - v1.y * v2.x;
		return v;
	}

	static vec3d Vector_IntersectPlane(vec3d &plane_p, vec3d &plane_n, vec3d &lineStart, vec3d &lineEnd, float &t)
	{
		plane_n = Vector_Normalise(plane_n);
		float plane_d = -Vector_DotProduct(plane_n, plane_p);
		float ad = Vector_DotProduct(lineStart, plane_n);
		float bd = Vector_DotProduct(lineEnd, plane_n);
		t = (-plane_d - ad) / (bd - ad);
		vec3d lineStartToEnd = Vector_Sub(lineEnd, lineStart);
		vec3d lineToIntersect = Vector_Mul(lineStartToEnd, t);
		return Vector_Add(lineStart, lineToIntersect);
	}

	// Triangle
	static int Triangle_ClipAgainstPlane(vec3d plane_p, vec3d plane_n, triangle &in_tri, triangle &out_tri1, triangle &out_tri2)
	{
		// Make sure plane normal is indeed normal
		plane_n = Vector_Normalise(plane_n);

		// Return signed shortest distance from point to plane, plane normal must be normalized
		auto dist = [&](vec3d &p)
		{
			vec3d n = Vector_Normalise(p);
			return (plane_n.x * p.x + plane_n.y * p.y + plane_n.z * p.z - Vector_DotProduct(plane_n, plane_p));
		};

		// Create two temporary storage arrays to classify points either side of plane
		// If distance sign is positive, point lies on "inside" of plane
		vec3d* inside_points[3];  int nInsidePointCount = 0;
		vec3d* outside_points[3]; int nOutsidePointCount = 0;
		vec2d* inside_tex[3]; int nInsideTexCount = 0;
		vec2d* outside_tex[3]; int nOutsideTexCount = 0;
		
		// Get signed distance of each point in triangle to plane
		float d0 = dist(in_tri.p[0]);
		float d1 = dist(in_tri.p[1]);
		float d2 = dist(in_tri.p[2]);

		if (d0 >= 0) { inside_points[nInsidePointCount++] = &in_tri.p[0]; inside_tex[nInsideTexCount++] = &in_tri.t[0]; }
		else {
			outside_points[nOutsidePointCount++] = &in_tri.p[0]; outside_tex[nOutsideTexCount++] = &in_tri.t[0];
		}
		if (d1 >= 0) {
			inside_points[nInsidePointCount++] = &in_tri.p[1]; inside_tex[nInsideTexCount++] = &in_tri.t[1];
		}
		else {
			outside_points[nOutsidePointCount++] = &in_tri.p[1];  outside_tex[nOutsideTexCount++] = &in_tri.t[1];
		}
		if (d2 >= 0) {
			inside_points[nInsidePointCount++] = &in_tri.p[2]; inside_tex[nInsideTexCount++] = &in_tri.t[2];
		}
		else {
			outside_points[nOutsidePointCount++] = &in_tri.p[2];  outside_tex[nOutsideTexCount++] = &in_tri.t[2];
		}

		// Now classify triangle points, and break the input triangle into 
		// smaller output triangles if required. There are four possible
		// outcomes...

		if (nInsidePointCount == 0)
		{
			// All points lie on the outside of plane, so clip whole triangle
			// It ceases to exist

			return 0; // No returned triangles are valid
		}

		if (nInsidePointCount == 3)
		{
			// All points lie on the inside of plane, so do nothing
			// and allow the triangle to simply pass through
			out_tri1 = in_tri;

			return 1; // Just the one returned original triangle is valid
		}

		if (nInsidePointCount == 1 && nOutsidePointCount == 2)
		{
			// Triangle should be clipped. As two points lie outside
			// the plane, the triangle simply becomes a smaller triangle

			// Copy appearance info to new triangle
			out_tri1.col = in_tri.col;
			out_tri1.sym = in_tri.sym;

			// The inside point is valid, so keep that...
			out_tri1.p[0] = *inside_points[0];
			out_tri1.t[0] = *inside_tex[0];

			// but the two new points are at the locations where the 
			// original sides of the triangle (lines) intersect with the plane
			float t;
			out_tri1.p[1] = Vector_IntersectPlane(plane_p, plane_n, *inside_points[0], *outside_points[0], t);
			out_tri1.t[1].u = t * (outside_tex[0]->u - inside_tex[0]->u) + inside_tex[0]->u;
			out_tri1.t[1].v = t * (outside_tex[0]->v - inside_tex[0]->v) + inside_tex[0]->v;
			out_tri1.t[1].w = t * (outside_tex[0]->w - inside_tex[0]->w) + inside_tex[0]->w;

			out_tri1.p[2] = Vector_IntersectPlane(plane_p, plane_n, *inside_points[0], *outside_points[1], t);
			out_tri1.t[2].u = t * (outside_tex[1]->u - inside_tex[0]->u) + inside_tex[0]->u;
			out_tri1.t[2].v = t * (outside_tex[1]->v - inside_tex[0]->v) + inside_tex[0]->v;
			out_tri1.t[2].w = t * (outside_tex[1]->w - inside_tex[0]->w) + inside_tex[0]->w;

			return 1; // Return the newly formed single triangle
		}

		if (nInsidePointCount == 2 && nOutsidePointCount == 1)
		{
			// Triangle should be clipped. As two points lie inside the plane,
			// the clipped triangle becomes a "quad". Fortunately, we can
			// represent a quad with two new triangles

			// Copy appearance info to new triangles
			out_tri1.col = in_tri.col;
			out_tri1.sym = in_tri.sym;

			out_tri2.col = in_tri.col;
			out_tri2.sym = in_tri.sym;

			// The first triangle consists of the two inside points and a new
			// point determined by the location where one side of the triangle
			// intersects with the plane
			out_tri1.p[0] = *inside_points[0];
			out_tri1.p[1] = *inside_points[1];
			out_tri1.t[0] = *inside_tex[0];
			out_tri1.t[1] = *inside_tex[1];

			float t;
			out_tri1.p[2] = Vector_IntersectPlane(plane_p, plane_n, *inside_points[0], *outside_points[0], t);
			out_tri1.t[2].u = t * (outside_tex[0]->u - inside_tex[0]->u) + inside_tex[0]->u;
			out_tri1.t[2].v = t * (outside_tex[0]->v - inside_tex[0]->v) + inside_tex[0]->v;
			out_tri1.t[2].w = t * (outside_tex[0]->w - inside_tex[0]->w) + inside_tex[0]->w;

			// The second triangle is composed of one of he inside points, a
			// new point determined by the intersection of the other side of the 
			// triangle and the plane, and the newly created point above
			out_tri2.p[0] = *inside_points[1];
			out_tri2.t[0] = *inside_tex[1];
			out_tri2.p[1] = out_tri1.p[2];
			out_tri2.t[1] = out_tri1.t[2];
			out_tri2.p[2] = Vector_IntersectPlane(plane_p, plane_n, *inside_points[1], *outside_points[0], t);
			out_tri2.t[2].u = t * (outside_tex[0]->u - inside_tex[1]->u) + inside_tex[1]->u;
			out_tri2.t[2].v = t * (outside_tex[0]->v - inside_tex[1]->v) + inside_tex[1]->v;
			out_tri2.t[2].w = t * (outside_tex[0]->w - inside_tex[1]->w) + inside_tex[1]->w;
			return 2; // Return two newly formed triangles which form a quad
		}
	}
};

enum { X, Y, Z, };

class MathPoint3D
{
	//---------------------------------------------------------------------------
	static double Dot(double *point1, double *point2)
	{
		return point1[X] * point2[X] + point1[Y] * point2[Y] + point1[Z] * point2[Z];
	}
	//---------------------------------------------------------------------------
	static double Mag(double *point1)
	{
		return std::sqrt(point1[X] * point1[X] + point1[Y] * point1[Y] + point1[Z] * point1[Z]);
	}
	//---------------------------------------------------------------------------
	static float Norm2(double *point1)
	{
		return point1[X] * point1[X] + point1[Y] * point1[Y] + point1[Z] * point1[Z];
	}
	//---------------------------------------------------------------------------
	static double Vector_Norm(double *point1)
	{
		return sqrt(Norm2(point1));
	}
	//---------------------------------------------------------------------------
	static void Cross(double(&point)[3], double *point1, double *point2)
	{
		point[X] = point1[Y] * point2[Z] - point1[Z] * point2[Y];
		point[Y] = point1[Z] * point2[X] - point1[X] * point2[Z];
		point[Z] = point1[X] * point2[Y] - point1[Y] * point2[X];
	}
	//---------------------------------------------------------------------------
	static double* Cross(double *point1, double *point2)
	{
		double point[3];
		point[X] = point1[Y] * point2[Z] - point1[Z] * point2[Y];
		point[Y] = point1[Z] * point2[X] - point1[X] * point2[Z];
		point[Z] = point1[X] * point2[Y] - point1[Y] * point2[X];

		return point;
	}

	//---------------------------------------------------------------------------
	bool Equal(double *point1, double *point2)
	{
		return point1[X] == point2[X] && point1[Y] == point2[Y] && point1[Z] == point2[Z];
	}
	//----------------------------------------------------------------------------
	double DistanceBetweenPoints(double *point1, double *point2)
	{
		return sqrt(pow(point1[X] - point2[X], 2) + pow(point1[Y] - point2[Y], 2) + pow(point1[Z] - point2[Z], 2));
	}
	//---------------------------------------------------------------------------
	double * GetMidPoint(double *point1, double *point2)
	{
		double midPoint[3];
		midPoint[X] = (point1[X] + point2[X]) / 2;
		midPoint[Y] = (point1[Y] + point2[Y]) / 2;
		midPoint[Z] = (point1[Z] + point2[Z]) / 2;

		return midPoint;
	}
	//----------------------------------------------------------------------------
	double GetAngle(double point1[3], double point2[3])
	{
		return std::acos(Dot(point1, point2) / (Mag(point1)*Mag(point2)));
	}
	//----------------------------------------------------------------------------
	double GetAngle(double* point1, double* point2, double* origin)
	{
		double ab[3] = { origin[X] - point1[X], origin[Y] - point1[Y], origin[Z] - point1[Z] };
		double bc[3] = { point2[X] - origin[X], point2[Y] - origin[Y], point2[Z] - origin[Z] };

		double abVec = sqrt(ab[X] * ab[X] + ab[Y] * ab[Y] + ab[Z] * ab[Z]);
		double bcVec = sqrt(bc[X] * bc[X] + bc[Y] * bc[Y] + bc[Z] * bc[Z]);

		double abNorm[3] = { ab[X] / abVec, ab[Y] / abVec, ab[Z] / abVec };
		double bcNorm[3] = { bc[X] / bcVec, bc[Y] / bcVec, bc[Z] / bcVec };

		double res = abNorm[X] * bcNorm[X] + abNorm[Y] * bcNorm[Y] + abNorm[Z] * bcNorm[Z];

		return acos(res)*180.0 / 3.141592653589793;
	}
	//----------------------------------------------------------------------------
	bool GetIntersection(double(&point)[3], double *line1Point1, double *line1Point2, double *line2Point1, double *line2Point2)
	{
		double da[3] = { line1Point2[X] - line1Point1[X], line1Point2[Y] - line1Point1[Y], line1Point2[Z] - line1Point1[Z] };
		double db[3] = { line2Point2[X] - line2Point1[X], line2Point2[Y] - line2Point1[Y], line2Point2[Z] - line2Point1[Z] };
		double dc[3] = { line2Point1[X] - line1Point1[X], line2Point1[Y] - line1Point1[Y], line2Point1[Z] - line1Point1[Z] };

		if (Dot(dc, Cross(da, db)) != 0.0) // Lines are not coplanar
			return false;

		double cross_dc_db[3];
		Cross(cross_dc_db, da, db);

		double s = Dot(Cross(dc, db), Cross(da, db)) / Norm2(Cross(da, db));
		if (s >= 0.0 && s <= 1.0)
		{
			point[X] = line1Point1[X] + da[X] * s;
			point[Y] = line1Point1[Y] + da[Y] * s;
			point[Z] = line1Point1[Z] + da[Z] * s;
			return true;
		}

		return false;
	}
	//----------------------------------------------------------------------------
	double GetDistancePointToLine(double * point, double * lineP1, double * lineP2)
	{
		double ab[3] = { lineP2[X] - lineP1[X], lineP2[Y] - lineP1[Y], lineP2[Z] - lineP1[Z] };
		double ac[3] = { point[X] - lineP1[X], point[Y] - lineP1[Y], point[Z] - lineP1[Z] };

		double area = Mag(Cross(ab, ac));
		double cd = area / Mag(ab);

		return cd;
	}

};