#include <QtTest>
#include "vector2.h"

// add necessary includes here

class Vector2_Tests : public QObject
{
    Q_OBJECT

public:
    Vector2_Tests();
    ~Vector2_Tests();

private slots:
    void Magnitude_WithNormalizedVector_Returns1();
    void Magnitude_WithNonNormalizedVector_ReturnsLength();
    void Distance_WithDifferentPoints_ReturnsDistance();
    void Distance_WithSamePoints_Returns0();
    void Normalized_WithNonNormalizedVector_ReturnsNormalizedVector();
    void Normalized_WithNormalizedVector_ReturnsSame();
    void OperatorPlus_AddsToVector();
    void OperatorMinus_SubtractsFromVector();
    void OperatorPlusEquals_AddsToVector();
    void OperatorMinusEquals_SubtractsFromVector();
    void OperatorMultiply_WithFloatAfter_ScalesVector();
    void OperatorMultiply_WithFloatBefore_ScalesVector();
    void OperatorMultiplyEquals_WithFloat_ScalesVector();
};

Vector2_Tests::Vector2_Tests() {}

Vector2_Tests::~Vector2_Tests() {}

void Vector2_Tests::Magnitude_WithNormalizedVector_Returns1() {
    // Arrange
    Vector2 vec = Vector2(1.f, 0.f);
    float expected = 1.f;

    // Act
    float actual = vec.Magnitude();

    // Assert
    QCOMPARE(expected, actual);
}

void Vector2_Tests::Magnitude_WithNonNormalizedVector_ReturnsLength() {
    // Arrange
    Vector2 vec = Vector2(0.f, 6.f);
    float expected = 6.f;

    // Act
    float actual = vec.Magnitude();

    // Assert
    QCOMPARE(expected, actual);
}

void Vector2_Tests::Distance_WithDifferentPoints_ReturnsDistance() {
    // Arrange
    Vector2 start = Vector2(1.f, 1.f);
    Vector2 end = Vector2(4.f, 5.f);
    float expected = 5.f;

    // Act
    float actual = start.Distance(end);

    // Assert
    QCOMPARE(expected, actual);
}

void Vector2_Tests::Distance_WithSamePoints_Returns0() {
    // Arrange
    Vector2 start = Vector2(3.f, 3.f);
    Vector2 end = Vector2(3.f, 3.f);
    float expected = 0.f;

    // Act
    float actual = start.Distance(end);

    // Assert
    QCOMPARE(expected, actual);
}

void Vector2_Tests::Normalized_WithNonNormalizedVector_ReturnsNormalizedVector() {
    // Arrange
    Vector2 vec = Vector2(3.f, 4.f);
    Vector2 expected = Vector2(0.6, 0.8);

    // Act
    Vector2 actual = vec.Normalized();

    // Assert
    QCOMPARE(expected, actual);
}

void Vector2_Tests::Normalized_WithNormalizedVector_ReturnsSame() {
    // Arrange
    Vector2 vec = Vector2(1.f, 0.f);
    Vector2 expected = Vector2(1.f, 0.f);

    // Act
    Vector2 actual = vec.Normalized();

    // Assert
    QCOMPARE(expected, actual);
}

void Vector2_Tests::OperatorPlus_AddsToVector() {
    // Arrange
    Vector2 vec = Vector2(1.f, 0.f);
    Vector2 add = Vector2(3.f, 2.f);
    Vector2 expected = Vector2(4.f, 2.f);

    // Act
    Vector2 actual = vec + add;

    // Assert
    QCOMPARE(expected, actual);
}

void Vector2_Tests::OperatorMinus_SubtractsFromVector() {
    // Arrange
    Vector2 vec = Vector2(5.f, 7.f);
    Vector2 sub = Vector2(3.f, 4.f);
    Vector2 expected = Vector2(2.f, 3.f);

    // Act
    Vector2 actual = vec - sub;

    // Assert
    QCOMPARE(expected, actual);
}

void Vector2_Tests::OperatorPlusEquals_AddsToVector() {
    // Arrange
    Vector2 vec = Vector2(1.f, 0.f);
    Vector2 add = Vector2(3.f, 2.f);
    Vector2 expected = Vector2(4.f, 2.f);

    // Act
    vec += add;

    // Assert
    QCOMPARE(expected, vec);
}

void Vector2_Tests::OperatorMinusEquals_SubtractsFromVector() {
    // Arrange
    Vector2 vec = Vector2(5.f, 7.f);
    Vector2 sub = Vector2(3.f, 4.f);
    Vector2 expected = Vector2(2.f, 3.f);

    // Act
    vec -= sub;

    // Assert
    QCOMPARE(expected, vec);
}

void Vector2_Tests::OperatorMultiply_WithFloatAfter_ScalesVector() {
    // Arrange
    Vector2 vec = Vector2(5.f, 7.f);
    float scale = 4.f;
    Vector2 expected = Vector2(20.f, 28.f);

    // Act
    Vector2 actual = vec * scale;

    // Assert
    QCOMPARE(expected, actual);
}

void Vector2_Tests::OperatorMultiply_WithFloatBefore_ScalesVector() {
    // Arrange
    Vector2 vec = Vector2(5.f, 7.f);
    float scale = 4.f;
    Vector2 expected = Vector2(20.f, 28.f);

    // Act
    Vector2 actual = scale * vec;

    // Assert
    QCOMPARE(expected, actual);
}

void Vector2_Tests::OperatorMultiplyEquals_WithFloat_ScalesVector() {
    // Arrange
    Vector2 vec = Vector2(5.f, 7.f);
    float scale = 4.f;
    Vector2 expected = Vector2(20.f, 28.f);

    // Act
    vec *= scale;

    // Assert
    QCOMPARE(expected, vec);
}

QTEST_APPLESS_MAIN(Vector2_Tests)

#include "tst_vector2_tests.moc"
