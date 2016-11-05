#include <lug\Maths\Quaternion.hpp>


lug::Maths::Quaternion::Quaternion(double x, double y, double z, double w) : _X(x), _Y(y), _Z(z), _W(w) {
    _Axis = lug::Maths::Vec3d{y,z,w};
}

lug::Maths::Quaternion::Quaternion(lug::Maths::Vec3d v) : _X(0), _Y(v.x), _Z(v.y), _W(v.z), _Axis(v) {}

lug::Maths::Quaternion::Quaternion(const Quaternion & otherQuaternion) : _X(otherQuaternion.getX()), _Y(otherQuaternion.getY()), _Z(otherQuaternion.getZ()), _W(otherQuaternion.getW()) {}

lug::Maths::Quaternion & lug::Maths::Quaternion::operator=(const lug::Maths::Quaternion & leftOperand) {
    
    _X = leftOperand.getX();
    _Y = leftOperand.getY();
    _Z = leftOperand.getZ();
    _Z = leftOperand.getW();
    return *(this);
}

lug::Maths::Quaternion::~Quaternion() {}

lug::Maths::Quaternion lug::Maths::Quaternion::conjugate() {
    lug::Maths::Quaternion conjugateQuaternion(_X, -_Y, -_Z, -_W);
    return std::move(conjugateQuaternion);
}

lug::Maths::Quaternion lug::Maths::Quaternion::invert() {
    double numerator = std::pow(_X, 2) + std::pow(_Y, 2) + std::pow(_Z, 2) + std::pow(_W, 2);

    lug::Maths::Quaternion inverseQuaternion(_X / numerator, _Y / numerator, _Z / numerator, _W / numerator);
    
    return std::move(inverseQuaternion);
}

lug::Maths::Quaternion lug::Maths::Quaternion::normalize() {
    double numerator = std::sqrt(std::pow(_X, 2) + std::pow(_Y, 2) + std::pow(_Z, 2) + std::pow(_W, 2));

    lug::Maths::Quaternion normalizeQuaternion(_X / numerator, _Y / numerator, _Z / numerator, _W / numerator);

    return std::move(normalizeQuaternion);
}

const double lug::Maths::Quaternion::angleWith(const Quaternion & otherQuaternion) {
    lug::Maths::Quaternion resQuaternion = otherQuaternion * invert();


    return std::move(std::acos(resQuaternion._W) * 2.0);
}

lug::Maths::Quaternion lug::Maths::Quaternion::slerp(const Quaternion &otherQuaternion, double t) {
    
    double angle = angleWith(otherQuaternion) / 2;
    lug::Maths::Quaternion qm = ((*this) * std::sin(1.0 - t) * angle + otherQuaternion * std::sin(t * angle)) / std::sin(angle);
}

const double & lug::Maths::Quaternion::getAngle() const {
    return _angle;
}

void lug::Maths::Quaternion::setAngle(const double &angle) {
    _angle = angle;
}

const double & lug::Maths::Quaternion::getX() const {
    return _X;
}

void lug::Maths::Quaternion::setX(const double & X) {
    _X = X;
}

const double & lug::Maths::Quaternion::getY() const {
    return _Y;
}

void lug::Maths::Quaternion::setY(const double & Y) {
    _Y = Y;
}

const double & lug::Maths::Quaternion::getZ() const {
    return _Z;
}

void lug::Maths::Quaternion::setZ(const double & Z) {
    _Z = Z;
}

const double & lug::Maths::Quaternion::getW() const {
    return _W;
}

void lug::Maths::Quaternion::setW(const double &W) {
    _W = W;
}

const lug::Maths::Vec3d & lug::Maths::Quaternion::getAxis() const {
    return _Axis;
}

void lug::Maths::Quaternion::setAxis(const lug::Maths::Vec3d &axis) {
    _Axis = axis;
    _Y = axis.x;
    _Z = axis.y;
    _W = axis.z;
}

lug::Maths::Quaternion lug::Maths::operator+(const lug::Maths::Quaternion & leftOperand, const lug::Maths::Quaternion & rightOperand) {
    return std::move(lug::Maths::Quaternion(leftOperand.getX() + rightOperand.getX(), leftOperand.getY() + rightOperand.getY(), leftOperand.getZ() + rightOperand.getZ(), leftOperand.getW() + rightOperand.getW()));
}

lug::Maths::Quaternion lug::Maths::operator-(const lug::Maths::Quaternion & leftOperand, const lug::Maths::Quaternion & rightOperand) {
    return std::move(lug::Maths::Quaternion(leftOperand.getX() - rightOperand.getX(), leftOperand.getY() - rightOperand.getY(), leftOperand.getZ() - rightOperand.getZ(), leftOperand.getW() - rightOperand.getW()));
}

lug::Maths::Quaternion lug::Maths::operator*(const lug::Maths::Quaternion & leftOperand, const lug::Maths::Quaternion & rightOperand) {
    return std::move(lug::Maths::Quaternion(leftOperand.getX() * rightOperand.getX() - leftOperand.getY() * rightOperand.getY() - leftOperand.getZ() * rightOperand.getZ() - leftOperand.getW() * rightOperand.getW(),
                                            leftOperand.getX() * rightOperand.getX() + leftOperand.getY() * rightOperand.getY() + leftOperand.getZ() * rightOperand.getZ() - leftOperand.getW() * rightOperand.getW(),
                                            leftOperand.getX() * rightOperand.getX() - leftOperand.getY() * rightOperand.getY() + leftOperand.getZ() * rightOperand.getZ() + leftOperand.getW() * rightOperand.getW(),
                                            leftOperand.getX() * rightOperand.getX() + leftOperand.getY() * rightOperand.getY() - leftOperand.getZ() * rightOperand.getZ() + leftOperand.getW() * rightOperand.getW()));
}

lug::Maths::Quaternion operator/(const lug::Maths::Quaternion &leftOperand, const lug::Maths::Quaternion &rightOperand) {
    return std::move(leftOperand * rightOperand.conjugate);
}


const bool lug::Maths::operator==(const lug::Maths::Quaternion & leftOperand, const lug::Maths::Quaternion & rightOperand) {
    if (leftOperand.getX() == rightOperand.getX()) && 
        (leftOperand.getY() == rightOperand.getY()) 
        && (leftOperand.getZ() == rightOperand.getZ()) 
        && (leftOperand.getW() == rightOperand.getW()) {
        return true;
    } else { return false; }
}

lug::Maths::Quaternion lug::Maths::operator*(const lug::Maths::Quaternion & leftOperand, const double scalar) {
    lug::Maths::Quaternion result(leftOperand);
    result.setX(result.getX() * scalar);
    return (std::move(result));
}

lug::Maths::Quaternion lug::Maths::operator+(const lug::Maths::Quaternion & leftOperand, const double scalar) {
    lug::Maths::Quaternion result(leftOperand);
    result.setX(result.getX() + scalar);
    return (std::move(result));
}

lug::Maths::Quaternion lug::Maths::operator-(const lug::Maths::Quaternion & leftOperand, const double scalar) {
    lug::Maths::Quaternion result(leftOperand);
    result.setX(result.getX() - scalar);
    return (std::move(result));
}

lug::Maths::Quaternion lug::Maths::operator/(const lug::Maths::Quaternion & leftOperand, const double scalar) {
    lug::Maths::Quaternion result(leftOperand);
    result.setX(result.getX() / scalar);
    return (std::move(result));
}

lug::Maths::Quaternion lug::Maths::reflection(const lug::Maths::Quaternion & inputePoint, const Vec3d & rotationAxis) {
    lug::Maths::Quaternion in(0, inputePoint.getX(), inputePoint.getY(), inputePoint.getZ());
    lug::Maths::Quaternion q(rotationAxis);

    return std::move(q * in * q);
}

lug::Maths::Quaternion lug::Maths::reflection(const lug::Maths::Quaternion & inputePoint, const lug::Maths::Quaternion & reflectionPlan) {
    lug::Maths::Quaternion in(0, inputePoint.getX(), inputePoint.getY(), inputePoint.getZ());
    
    lug::Maths::Quaternion q(reflectionPlan);
    q.normalize();
    q.setX(0.0);
    return std::move(q * in * q);
}

lug::Maths::Quaternion lug::Maths::rotation(const Quaternion & inputePoint, const double & angle, const Vec3d & rotationAxis) {
    double halfAngle = angle / 2.0;
    double sinHalfAngle = std::sin(halfAngle);
    lug::Maths::Quaternion q(std::cos(halfAngle), sinHalfAngle * rotationAxis.x, sinHalfAngle * rotationAxis.y, sinHalfAngle * rotationAxis.z);
    
    return std::move(q * inputePoint * q.conjugate());
}

lug::Maths::Quaternion lug::Maths::rotation(const lug::Maths::Quaternion & inputePoint, const lug::Maths::Quaternion & q) {
    return std::move(q * inputePoint * q.conjugate());
}
