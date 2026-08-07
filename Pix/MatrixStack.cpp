#include "MatrixStack.h"
MatrixStack* MatrixStack::Get(){
	static MatrixStack sInstance;
	return &sInstance;
}
void MatrixStack::OnNewFrame() {
	mCombinedTransform = Matrix4::Identity();
	mMatrices.clear();
}
void MatrixStack::PushTranslation(const Vector3& d) {
	Matrix4 translationMatrix = Matrix4::Translation(d);
	mCombinedTransform = translationMatrix * mCombinedTransform;
	mMatrices.push_back(translationMatrix);
}
void MatrixStack::PushRotationX(float radians) {
	Matrix4 rotationMatrix = Matrix4::RotationX(radians);
	mCombinedTransform = rotationMatrix * mCombinedTransform;
	mMatrices.push_back(rotationMatrix);
}
void MatrixStack::PushRotationY(float radians) {
	Matrix4 rotationMatrix = Matrix4::RotationY(radians);
	mCombinedTransform = rotationMatrix * mCombinedTransform;
	mMatrices.push_back(rotationMatrix);
}
void MatrixStack::PushRotationZ(float radians) {
	Matrix4 rotationMatrix = Matrix4::RotationZ(radians);
	mCombinedTransform = rotationMatrix * mCombinedTransform;
	mMatrices.push_back(rotationMatrix);
}
void MatrixStack::PushScaling(const Vector3& s) {
	Matrix4 scaleMatrix = Matrix4::Scale(s);
	mCombinedTransform = scaleMatrix * mCombinedTransform;
	mMatrices.push_back(scaleMatrix);
}
void MatrixStack::PopMatrix() {
	if (!mMatrices.empty())
	{
		Matrix4 matrix = mMatrices.back();
		mMatrices.pop_back();
		mCombinedTransform = MathHelper::Inverse(matrix) * mCombinedTransform;
	}
}

const Matrix4& MatrixStack::GetTransform() const {
	return mCombinedTransform;
}