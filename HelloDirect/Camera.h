//#ifndef CAMERA_H
//#define CAMERA_H
//
//#include <DirectXMath.h>
//#include "Megaman.h"
//
//class GraphicsDevice;
//
//class Camera
//{
//public:
//	//Constructors and Destructor
//	Camera(float width, float height, float angle, DirectX::XMFLOAT3 scaleFactors);
//	~Camera();
//
//	//Game Functions
//	void Update();
//	void Follow(CGameObject *following);
//	void Unfollow();
//	bool IsFollowing() const;
//	void SetTransform(LPDIRECT3DDEVICE9 d3ddev) const;
//
//private:
//	float angle;
//	DirectX::XMFLOAT3 scaleFactors;
//	D3DXMATRIX orthographicMatrix;
//	D3DXMATRIX identityMatrix;
//	D3DXMATRIX viewMatrix;
//
//	CGameObject *following;
//
//	float width;
//	float height;
//};
//
//#endif /* CAMERA_H */
