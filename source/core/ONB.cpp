#include "ONB.h"

using namespace Solstice;

void OrthonormalBasis::InitFromWV(const Vector3& w, const Vector3& v) {

		W = Vector3::UnitVector(w);
		U = Vector3::UnitVector(Vector3::CrossProduct(v, w));
		V = Vector3::CrossProduct(W, U);

}