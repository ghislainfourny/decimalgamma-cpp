#import <string>

class BitSequenceTest {
public:
	BitSequenceTest() {}
  void run();
private:
  static bool assertEqual(bool, bool);
  static bool assertEqual(std::string, std::string);
  static bool assertIntEqual(int, int);
};
