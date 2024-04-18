#include <Novice.h>
#include "Vector3.h"
#include "Matrix4x4.h"
#include <assert.h>
#include <cmath>

const char kWindowTitle[] = "LC1B_13_コムロ_リュウヘイ";

static const int kRowHeight = 20;
static const int kColumnWidth = 60;

// 表示
void MatrixScreenPrintf(int x, int y, Matrix4x4 matrix) {
	for (int row = 0; row < 4; row++) {
		for (int column = 0; column < 4; column++) {
			Novice::ScreenPrintf(
				x + column * kColumnWidth, y + row * kRowHeight, "%.02f", matrix.m[row][column]);
		}
	}
}

// 積
Matrix4x4 Multiply(const Matrix4x4& m1, const Matrix4x4& m2) {
	Matrix4x4 result = {};

	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			for (int k = 0; k < 4; k++) {
				result.m[i][j] += m1.m[i][k] * m2.m[k][j];
			}
		}
	}
	return result;
}

// X回転行列
Matrix4x4 MakeRotateXMatrix(float radian) {
	Matrix4x4 rotationMatrix = {};

	rotationMatrix.m[0][0] = 1.0f;
	rotationMatrix.m[0][1] = 0.0f;
	rotationMatrix.m[0][2] = 0.0f;
	rotationMatrix.m[0][3] = 0.0f;

	rotationMatrix.m[1][0] = 0.0f;
	rotationMatrix.m[1][1] = std::cos(radian);
	rotationMatrix.m[1][2] = std::sin(radian);
	rotationMatrix.m[1][3] = 0.0f;

	rotationMatrix.m[2][0] = 0.0f;
	rotationMatrix.m[2][1] = -std::sin(radian);
	rotationMatrix.m[2][2] = std::cos(radian);
	rotationMatrix.m[2][3] = 0.0f;

	rotationMatrix.m[3][0] = 0.0f;
	rotationMatrix.m[3][1] = 0.0f;
	rotationMatrix.m[3][2] = 0.0f;
	rotationMatrix.m[3][3] = 1.0f;

	return rotationMatrix;
}

// Y回転行列
Matrix4x4 MakeRotateYMatrix(float radian) {
	Matrix4x4 rotationMatrix = {};

	rotationMatrix.m[0][0] = std::cos(radian);
	rotationMatrix.m[0][1] = 0.0f;
	rotationMatrix.m[0][2] = -std::sin(radian);
	rotationMatrix.m[0][3] = 0.0f;

	rotationMatrix.m[1][0] = 0.0f;
	rotationMatrix.m[1][1] = 1.0f;
	rotationMatrix.m[1][2] = 0.0f;
	rotationMatrix.m[1][3] = 0.0f;

	rotationMatrix.m[2][0] = std::sin(radian);
	rotationMatrix.m[2][1] = 0.0f;
	rotationMatrix.m[2][2] = std::cos(radian);
	rotationMatrix.m[2][3] = 0.0f;

	rotationMatrix.m[3][0] = 0.0f;
	rotationMatrix.m[3][1] = 0.0f;
	rotationMatrix.m[3][2] = 0.0f;
	rotationMatrix.m[3][3] = 1.0f;

	return rotationMatrix;
}

// Z回転行列
Matrix4x4 MakeRotateZMatrix(float radian) {
	Matrix4x4 rotationMatrix = {};

	rotationMatrix.m[0][0] = std::cos(radian);
	rotationMatrix.m[0][1] = std::sin(radian);
	rotationMatrix.m[0][2] = 0.0f;
	rotationMatrix.m[0][3] = 0.0f;

	rotationMatrix.m[1][0] = -std::sin(radian);
	rotationMatrix.m[1][1] = std::cos(radian);
	rotationMatrix.m[1][2] = 0.0f;
	rotationMatrix.m[1][3] = 0.0f;

	rotationMatrix.m[2][0] = 0.0f;
	rotationMatrix.m[2][1] = 0.0f;
	rotationMatrix.m[2][2] = 1.0f;
	rotationMatrix.m[2][3] = 0.0f;

	rotationMatrix.m[3][0] = 0.0f;
	rotationMatrix.m[3][1] = 0.0f;
	rotationMatrix.m[3][2] = 0.0f;
	rotationMatrix.m[3][3] = 1.0f;

	return rotationMatrix;
}

// 平行移動行列
Matrix4x4 MakeTranslateMatrix(const Vector3& translate) {
	Matrix4x4 translateMatrix;

	translateMatrix.m[0][0] = 1.0f;
	translateMatrix.m[0][1] = 0.0f;
	translateMatrix.m[0][2] = 0.0f;
	translateMatrix.m[0][3] = 0.0f;

	translateMatrix.m[1][0] = 0.0f;
	translateMatrix.m[1][1] = 1.0f;
	translateMatrix.m[1][2] = 0.0f;
	translateMatrix.m[1][3] = 0.0f;

	translateMatrix.m[2][0] = 0.0f;
	translateMatrix.m[2][1] = 0.0f;
	translateMatrix.m[2][2] = 1.0f;
	translateMatrix.m[2][3] = 0.0f;

	translateMatrix.m[3][0] = translate.x;
	translateMatrix.m[3][1] = translate.y;
	translateMatrix.m[3][2] = translate.z;
	translateMatrix.m[3][3] = 1.0f;

	return translateMatrix;
}

// 拡大縮小行列
Matrix4x4 MakeScaleMatrix(const Vector3& scale) {
	Matrix4x4 scaleMatrix;

	scaleMatrix.m[0][0] = scale.x;
	scaleMatrix.m[0][1] = 0.0f;
	scaleMatrix.m[0][2] = 0.0f;
	scaleMatrix.m[0][3] = 0.0f;

	scaleMatrix.m[1][0] = 0.0f;
	scaleMatrix.m[1][1] = scale.y;
	scaleMatrix.m[1][2] = 0.0f;
	scaleMatrix.m[1][3] = 0.0f;

	scaleMatrix.m[2][0] = 0.0f;
	scaleMatrix.m[2][1] = 0.0f;
	scaleMatrix.m[2][2] = scale.z;
	scaleMatrix.m[2][3] = 0.0f;

	scaleMatrix.m[3][0] = 0.0f;
	scaleMatrix.m[3][1] = 0.0f;
	scaleMatrix.m[3][2] = 0.0f;
	scaleMatrix.m[3][3] = 1.0f;

	return scaleMatrix;
}

// 座標変換
Vector3 Transform(const Vector3& vector, const Matrix4x4& matrix) {
	Vector3 result;

	result.x = vector.x * matrix.m[0][0] + vector.y * matrix.m[1][0] + vector.z * matrix.m[2][0] + 1.0f * matrix.m[3][0];
	result.y = vector.x * matrix.m[0][1] + vector.y * matrix.m[1][1] + vector.z * matrix.m[2][1] + 1.0f * matrix.m[3][1];
	result.z = vector.x * matrix.m[0][2] + vector.y * matrix.m[1][2] + vector.z * matrix.m[2][2] + 1.0f * matrix.m[3][2];
	float w = vector.x * matrix.m[0][3] + vector.y * matrix.m[1][3] + vector.z * matrix.m[2][3] + 1.0f * matrix.m[3][3];
	assert(w != 0.0f);
	result.x /= w;
	result.y /= w;
	result.z /= w;

	return result;
}

// 3次元アフィン変換行列
Matrix4x4 MakeAffineMatrix(Vector3 scale, Vector3 rotate, Vector3 translate) {
	Matrix4x4 affineMatrix;

	// 各変換行列を作成
	Matrix4x4 scaleMatrix = MakeScaleMatrix(scale);

	Matrix4x4 rotateXMatrix = MakeRotateXMatrix(rotate.x);
	Matrix4x4 rotateYMatrix = MakeRotateYMatrix(rotate.y);
	Matrix4x4 rotateZMatrix = MakeRotateZMatrix(rotate.z);
	Matrix4x4 rotateXYZMatrix = Multiply(rotateXMatrix, Multiply(rotateYMatrix, rotateZMatrix));

	Matrix4x4 translateMatrix = MakeTranslateMatrix(translate);

	// 各変換行列を合成してアフィン変換行列を作成
	affineMatrix = Multiply(scaleMatrix, Multiply(rotateXYZMatrix, translateMatrix));

	return affineMatrix;
}

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, 1280, 720);

	// キー入力結果を受け取る箱
	char keys[256] = {0};
	char preKeys[256] = {0};

	Vector3 scale{ 1.2f,0.79f,-2.1f };
	Vector3 rotate{ 0.4f,1.43f,-0.8f };
	Vector3 translate{ 2.7f,-4.15f,1.57f };

	Matrix4x4 worldMatrix = MakeAffineMatrix(scale, rotate, translate);

	// ウィンドウの×ボタンが押されるまでループ
	while (Novice::ProcessMessage() == 0) {
		// フレームの開始
		Novice::BeginFrame();

		// キー入力を受け取る
		memcpy(preKeys, keys, 256);
		Novice::GetHitKeyStateAll(keys);

		///
		/// ↓更新処理ここから
		///

		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///

		MatrixScreenPrintf(0, 0, worldMatrix);

		///
		/// ↑描画処理ここまで
		///

		// フレームの終了
		Novice::EndFrame();

		// ESCキーが押されたらループを抜ける
		if (preKeys[DIK_ESCAPE] == 0 && keys[DIK_ESCAPE] != 0) {
			break;
		}
	}

	// ライブラリの終了
	Novice::Finalize();
	return 0;
}
