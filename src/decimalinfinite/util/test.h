#include <string>

class Test {
public:
	static bool assertBoolEqual(bool, bool);
  static bool assertStringEqual(std::string, std::string);
  static bool assertIntEqual(int, int);
  static bool assertFloatEqual(float, float);
  static bool assertDoubleEqual(double, double);
};
