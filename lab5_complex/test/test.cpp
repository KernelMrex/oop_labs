#define CATCH_CONFIG_MAIN
#include "../../catch.hpp"
#include "../src/Complex/Complex.h"

TEST_CASE("complex numbers can be constructed", "[complex_class]")
{
	SECTION("constructing and getting mixed values")
	{
		Complex complex(12, -23);
		REQUIRE(complex.Re() == 12.0);
		REQUIRE(complex.Im() == -23.0);

		REQUIRE(complex.GetArgument() == 23.0);
		REQUIRE(complex.GetMagnitude() == 12.0);
	}

	SECTION("constructing and getting positive values")
	{
		Complex complex(12, 23);
		REQUIRE(complex.Re() == 12.0);
		REQUIRE(complex.Im() == 23.0);
		REQUIRE(complex.GetArgument() == 23.0);
		REQUIRE(complex.GetMagnitude() == 12.0);
	}

	SECTION("constructing and getting negative values")
	{
		Complex complex(-12, -23);
		REQUIRE(complex.Re() == -12.0);
		REQUIRE(complex.Im() == -23.0);
		REQUIRE(complex.GetArgument() == 23.0);
		REQUIRE(complex.GetMagnitude() == 12.0);
	}
}

TEST_CASE("sum up two complex numbers", "[complex_sum_up]")
{
	SECTION("constructing and summing up two mixed values")
	{
		Complex complex1(12, -34);
		Complex complex2(-56, 78);

		auto complexResult = complex1 + complex2;

		REQUIRE(complexResult.Re() == -44.0);
		REQUIRE(complexResult.Im() == 44.0);
	}

	SECTION("constructing and summing up two positive values")
	{
		Complex complex1(12, 34);
		Complex complex2(56, 78);

		auto complexResult = complex1 + complex2;

		REQUIRE(complexResult.Re() == 68.0);
		REQUIRE(complexResult.Im() == 112.0);
	}

	SECTION("constructing and summing up two negative values")
	{
		Complex complex1(-12, -34);
		Complex complex2(-56, -78);

		auto complexResult = complex1 + complex2;

		REQUIRE(complexResult.Re() == -68.0);
		REQUIRE(complexResult.Im() == -112.0);
	}

	SECTION("constructing and summing up two values and check addresses")
	{
		Complex complex1(-12, -34);
		Complex complex2(-56, -78);

		auto complexResult = complex1 + complex2;

		REQUIRE(std::addressof(complex1) != std::addressof(complex2));
		REQUIRE(std::addressof(complex1) != std::addressof(complexResult));
		REQUIRE(std::addressof(complex2) != std::addressof(complexResult));
	}
}

TEST_CASE("sum up complex and real number", "[complex_and_real_sum_up]")
{
	SECTION("constructing and summing up mixed complex and positive real")
	{
		Complex complex(12, -34);
		double real = 56.0;

		auto complexResult = complex + real;

		REQUIRE(complexResult.Re() == 68.0);
		REQUIRE(complexResult.Im() == -34.0);
	}

	SECTION("constructing and summing up mixed complex and negative real")
	{
		Complex complex(12, -34);
		double real = -56.0;

		auto complexResult = complex + real;

		REQUIRE(complexResult.Re() == -44.0);
		REQUIRE(complexResult.Im() == -34.0);
	}

	SECTION("constructing and summing up mixed complex and positive real")
	{
		Complex complex(12, -34);
		double real = 56.0;

		auto complexResult = real + complex;

		REQUIRE(complexResult.Re() == 68.0);
		REQUIRE(complexResult.Im() == -34.0);
	}

	SECTION("inverse constructing and summing up mixed complex and negative real")
	{
		Complex complex(12, -34);
		double real = -56.0;

		auto complexResult = real + complex;

		REQUIRE(complexResult.Re() == -44.0);
		REQUIRE(complexResult.Im() == -34.0);
	}
}

TEST_CASE("subtract two complex numbers", "[complex_subtract]")
{
	SECTION("constructing and subtracting two mixed values")
	{
		Complex complex1(12, -34);
		Complex complex2(-56, 78);

		auto complexResult = complex1 - complex2;

		REQUIRE(complexResult.Re() == 68.0);
		REQUIRE(complexResult.Im() == -112.0);
	}

	SECTION("constructing and subtracting two positive values")
	{
		Complex complex1(12, 34);
		Complex complex2(56, 78);

		auto complexResult = complex1 - complex2;

		REQUIRE(complexResult.Re() == -44.0);
		REQUIRE(complexResult.Im() == -44.0);
	}

	SECTION("constructing and subtracting two negative values")
	{
		Complex complex1(-12, -34);
		Complex complex2(-56, -78);

		auto complexResult = complex1 - complex2;

		REQUIRE(complexResult.Re() == 44.0);
		REQUIRE(complexResult.Im() == 44.0);
	}

	SECTION("constructing and subtracting two values and check addresses")
	{
		Complex complex1(-12, -34);
		Complex complex2(-56, -78);

		auto complexResult = complex1 - complex2;

		REQUIRE(std::addressof(complex1) != std::addressof(complex2));
		REQUIRE(std::addressof(complex1) != std::addressof(complexResult));
		REQUIRE(std::addressof(complex2) != std::addressof(complexResult));
	}
}

TEST_CASE("subtract complex and real number", "[complex_and_real_subtract]")
{
	SECTION("constructing and subtracting mixed complex and positive real")
	{
		Complex complex(12, -34);
		double real = 56.0;

		auto complexResult = complex - real;

		REQUIRE(complexResult.Re() == -44.0);
		REQUIRE(complexResult.Im() == -34.0);
	}

	SECTION("constructing and subtracting mixed complex and negative real")
	{
		Complex complex(12, -34);
		double real = -56.0;

		auto complexResult = complex - real;

		REQUIRE(complexResult.Re() == 68.0);
		REQUIRE(complexResult.Im() == -34.0);
	}

	SECTION("constructing and subtracting mixed complex and positive real")
	{
		double real = 56.0;
		Complex complex(12, -34);

		auto complexResult = real - complex;

		REQUIRE(complexResult.Re() == 44.0);
		REQUIRE(complexResult.Im() == 34.0);
	}

	SECTION("inverse constructing and subtracting mixed complex and negative real")
	{
		double real = -56.0;
		Complex complex(12, -34);

		auto complexResult = real - complex;

		REQUIRE(complexResult.Re() == -68.0);
		REQUIRE(complexResult.Im() == 34.0);
	}
}

TEST_CASE("multiply two complex numbers", "[complex_multiplication]")
{
	SECTION("constructing and multiplying two mixed values")
	{
		Complex complex1(1, -2);
		Complex complex2(-3, 4);

		auto complexResult = complex1 * complex2;

		REQUIRE(complexResult.Re() == 5.0);
		REQUIRE(complexResult.Im() == 10.0);
	}

	SECTION("constructing and multiplying two positive values")
	{
		Complex complex1(1, 2);
		Complex complex2(3, 4);

		auto complexResult = complex1 * complex2;

		REQUIRE(complexResult.Re() == -5.0);
		REQUIRE(complexResult.Im() == 10.0);
	}

	SECTION("constructing and multiplying two negative values")
	{
		Complex complex1(-1, -2);
		Complex complex2(-3, -4);

		auto complexResult = complex1 * complex2;

		REQUIRE(complexResult.Re() == -5.0);
		REQUIRE(complexResult.Im() == 10.0);
	}

	SECTION("constructing and multiplying two values and check addresses")
	{
		Complex complex1(1, 2);
		Complex complex2(3, 4);

		auto complexResult = complex1 * complex2;

		REQUIRE(std::addressof(complex1) != std::addressof(complex2));
		REQUIRE(std::addressof(complex1) != std::addressof(complexResult));
		REQUIRE(std::addressof(complex2) != std::addressof(complexResult));
	}
}

TEST_CASE("multiply complex and real number", "[complex_and_real_multiplication]")
{
	SECTION("constructing and multiplying mixed complex and positive real")
	{
		Complex complex(1, -2);
		double real = 3.0;

		auto complexResult = complex * real;

		REQUIRE(complexResult.Re() == 3.0);
		REQUIRE(complexResult.Im() == -6.0);
	}

	SECTION("constructing and multiplying mixed complex and negative real")
	{
		Complex complex(1, -2);
		double real = -3.0;

		auto complexResult = complex * real;

		REQUIRE(complexResult.Re() == -3.0);
		REQUIRE(complexResult.Im() == 6.0);
	}

	SECTION("constructing and multiplying mixed complex and positive real")
	{
		double real = 3.0;
		Complex complex(1, -2);

		auto complexResult = real * complex;

		REQUIRE(complexResult.Re() == 3.0);
		REQUIRE(complexResult.Im() == -6.0);
	}

	SECTION("inverse constructing and multiplying mixed complex and negative real")
	{
		double real = -3.0;
		Complex complex(1, -2);

		auto complexResult = real * complex;

		REQUIRE(complexResult.Re() == -3.0);
		REQUIRE(complexResult.Im() == 6.0);
	}
}

TEST_CASE("divide two complex numbers", "[complex_division]")
{
	SECTION("constructing and dividing two mixed values")
	{
		Complex complex1(2, -4);
		Complex complex2(-8, 24);

		auto complexResult = complex1 / complex2;

		REQUIRE(complexResult.Re() == -0.175);
		REQUIRE(complexResult.Im() == -0.025);
	}

	SECTION("constructing and dividing two positive values")
	{
		Complex complex1(2, 4);
		Complex complex2(8, 24);

		auto complexResult = complex1 / complex2;

		REQUIRE(complexResult.Re() == 0.175);
		REQUIRE(complexResult.Im() == -0.025);
	}

	SECTION("constructing and dividing two negative values")
	{
		Complex complex1(-2, -4);
		Complex complex2(-8, -24);

		auto complexResult = complex1 / complex2;

		REQUIRE(complexResult.Re() == 0.175);
		REQUIRE(complexResult.Im() == -0.025);
	}

	SECTION("constructing and dividing two values and check addresses")
	{
		Complex complex1(2, 4);
		Complex complex2(8, 24);

		auto complexResult = complex1 / complex2;

		REQUIRE(std::addressof(complex1) != std::addressof(complex2));
		REQUIRE(std::addressof(complex1) != std::addressof(complexResult));
		REQUIRE(std::addressof(complex2) != std::addressof(complexResult));
	}
}

TEST_CASE("divide complex and real number", "[complex_and_real_division]")
{
	SECTION("constructing and dividing mixed complex and positive real")
	{
		Complex complex(12, -6);
		double real = 4.0;

		auto complexResult = complex / real;

		REQUIRE(complexResult.Re() == 3.0);
		REQUIRE(complexResult.Im() == -1.5);
	}

	SECTION("constructing and dividing mixed complex and negative real")
	{
		Complex complex(12, -6);
		double real = -4.0;

		auto complexResult = complex / real;

		REQUIRE(complexResult.Re() == -3.0);
		REQUIRE(complexResult.Im() == 1.5);
	}

	SECTION("constructing and dividing mixed complex and positive real")
	{
		double real = 4.0;
		Complex complex(8, -4);

		auto complexResult = real / complex;

		REQUIRE(complexResult.Re() == 0.4);
		REQUIRE(complexResult.Im() == 0.2);

	}

	SECTION("inverse constructing and dividing mixed complex and negative real")
	{
		double real = -4.0;
		Complex complex(8, -4);

		auto complexResult = real / complex;

		REQUIRE(complexResult.Re() == -0.4);
		REQUIRE(complexResult.Im() == -0.2);
	}
}

TEST_CASE("sum up and overwrite", "[sum_up_and_overwrite]")
{
	SECTION("sum up two complex numbers")
	{
		Complex complex1(12, -34);
		Complex complex2(-56, 78);

		Complex& complexRef = complex1;
		complex1 += complex2;

		REQUIRE(complex1.Re() == -44.0);
		REQUIRE(complex1.Im() == 44.0);
		REQUIRE(std::addressof(complexRef) == std::addressof(complex1));
	}

	SECTION("sum up complex and real numbers")
	{
		Complex complex(12, -34);
		double real = 56.0;

		Complex& complexRef = complex;
		complex += real;

		REQUIRE(complex.Re() == 68.0);
		REQUIRE(complex.Im() == -34.0);
		REQUIRE(std::addressof(complexRef) == std::addressof(complex));
	}
}

TEST_CASE("subtract and overwrite", "[subtract_and_overwrite]")
{
	SECTION("subtract two complex numbers")
	{
		Complex complex1(12, -34);
		Complex complex2(-56, 78);

		Complex& complexRef = complex1;
		complex1 -= complex2;

		REQUIRE(complex1.Re() == 68.0);
		REQUIRE(complex1.Im() == -112.0);
		REQUIRE(std::addressof(complexRef) == std::addressof(complex1));
	}

	SECTION("subtract complex and real numbers")
	{
		Complex complex(12, -34);
		double real = 56.0;

		Complex& complexRef = complex;
		complex -= real;

		REQUIRE(complex.Re() == -44.0);
		REQUIRE(complex.Im() == -34.0);
		REQUIRE(std::addressof(complexRef) == std::addressof(complex));
	}
}

TEST_CASE("multiply and overwrite", "[multiply_and_overwrite]")
{
	SECTION("multiply two complex numbers")
	{
		Complex complex1(1, -2);
		Complex complex2(-3, 4);

		Complex& complexRef = complex1;
		complex1 *= complex2;

		REQUIRE(complex1.Re() == 5.0);
		REQUIRE(complex1.Im() == 10.0);
		REQUIRE(std::addressof(complexRef) == std::addressof(complex1));
	}

	SECTION("multiply complex and real numbers")
	{
		Complex complex(1, -2);
		double real = 3;

		Complex& complexRef = complex;
		complex *= real;

		REQUIRE(complex.Re() == 3.0);
		REQUIRE(complex.Im() == -6.0);
		REQUIRE(std::addressof(complexRef) == std::addressof(complex));
	}
}

TEST_CASE("divide and overwrite", "[divide_and_overwrite]")
{
	SECTION("divide two complex numbers")
	{
		Complex complex1(2, -4);
		Complex complex2(-8, 24);

		Complex& complexRef = complex1;
		complex1 /= complex2;

		REQUIRE(complex1.Re() == -0.175);
		REQUIRE(complex1.Im() == -0.025);
		REQUIRE(std::addressof(complexRef) == std::addressof(complex1));
	}

	SECTION("divide complex and real numbers")
	{
		Complex complex(12, -6);
		double real = 4.0;

		Complex& complexRef = complex;
		complex /= real;

		REQUIRE(complex.Re() == 3.0);
		REQUIRE(complex.Im() == -1.5);
		REQUIRE(std::addressof(complexRef) == std::addressof(complex));
	}
}
