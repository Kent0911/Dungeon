#include "Camera.h"

Camera::Camera() {
	mc_state.mvec_position = kit::vec3(g_windowSize.x / 2, g_windowSize.y / 2, -200.0f);
	mc_state.mvec_target = kit::vec3(0, 0, 0);
	mc_state.mvec_upperVec = kit::vec3(0, 1, 0);
}

Camera::~Camera() {

}

void Camera::Tutorial() {

}

void Camera::GameMain() {

}

void Camera::MovePosition(kit::vec3* _movePos, int _count) {
	static int moveCount;
	if (moveCount < _count) {
		mc_state.mvec_position = ( *_movePos / _count );
		moveCount++;
	}
	else {
		moveCount = 0;
	}
}

void Camera::Update() {
	kit::Engine::g_mWorld = DirectX::XMMatrixIdentity();

	kit::Engine::g_mView = kit::Engine::LookVector( &mc_state );
	kit::Engine::g_uptrBasicEffect->SetView( kit::Engine::g_mView );
}
