#include "stdafx.h"
#include "XD3D11Ball.h"
#include <cstdlib>
#include <ctime>

using namespace std;

XD3D11Ball::XD3D11Ball(XVirtualD3D11Drawer * parent)
	: XVirtualD3D11Shape(parent)
{
	solid = false;
}

XD3D11Ball::~XD3D11Ball()
{
	indexBuffer->Release();
	vertexBuffer->Release();
}

void XD3D11Ball::create(int countCirclePoints)
{
	srand(time(nullptr));

	int cntCP = countCirclePoints;
	cntBallPoints = (2 * cntCP + 1) * cntCP;
	float seed = 1.0f / (float)(cntCP);
	XVirtualD3D11Drawer::Vertex *vecBall = new XVirtualD3D11Drawer::Vertex[cntBallPoints];
	for (int i = 0; i < cntCP * 2 + 1; i++) 
	{
		for (int j = 0; j < cntCP; j++)
		{
			float z = 1.0f - i * seed;
			float r = sqrt(1.0f - z * z);
			float x = r * cos(2 * PI * (j / (float)cntCP));
			float y = r * sin(2 * PI * (j / (float)cntCP));
			static int times = 0;
			times++;
			times = rand() % 4;

			if (times == 3) 
			{
				times = 0;
			}

			float red, g, b;
			if (times == 0) 
			{
				red = 1.0f;
				g = 0.0f;
				b = 0.0f;
			}
			else if (times == 1) 
			{
				red = 0.0f;
				g = 1.0f;
				b = 0.0f;
			}
			else
			{
				red = 0.0f;
				g = 0.0f;
				b = 1.0f;
			}

			vecBall[i * cntCP + j].set(x, y, z, red, g, b, 1.0f);
		}
	}
	parent->XCreateSimpleBuffer(D3D11_BIND_VERTEX_BUFFER, vecBall, sizeof(XVirtualD3D11Drawer::Vertex) * cntBallPoints, &vertexBuffer);
	delete[] vecBall;

	cntBallIndices = 0;
	DWORD *indexBall = new DWORD[cntCP * 2 * cntCP * 6];
	for (int i = 0; i < cntCP * 2; i++)
	{
		for (int j = 0; j < cntCP; j++)
		{
			indexBall[cntBallIndices++] = i * cntCP + j;
			indexBall[cntBallIndices++] = (i + 1) * cntCP + j;
			indexBall[cntBallIndices++] = (i + 1) * cntCP + ((j + 1) % cntCP);

			indexBall[cntBallIndices++] = i * cntCP + (j + 1) % cntCP;
			indexBall[cntBallIndices++] = i * cntCP + j;
			indexBall[cntBallIndices++] = (i + 1) * cntCP + ((j + 1) % cntCP);

		}
	}
	parent->XCreateSimpleBuffer(D3D11_BIND_INDEX_BUFFER, indexBall, sizeof(DWORD) * cntBallIndices, &indexBuffer);
	delete[] indexBall;

}

void XD3D11Ball::draw()
{
	UINT stride = sizeof(XVirtualD3D11Drawer::Vertex);
	UINT offset = 0;
	context->IASetVertexBuffers(0, 1, &vertexBuffer, &stride, &offset);
	context->IASetIndexBuffer(indexBuffer, DXGI_FORMAT_R32_UINT, 0);
	if (solid)
	{
		context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	}
	else
	{
		context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_LINESTRIP);
	}
	//	context->Draw(cntBallPoints, 0);
	context->DrawIndexed(cntBallIndices, 0, 0);
}

void XD3D11Ball::setSolid(bool solid)
{
	this->solid = solid;
}

void XD3D11Ball::onPaint()
{
    draw();
}
