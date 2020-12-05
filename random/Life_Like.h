
#include "Seed.h"
#include <bitset>

class Life_Like : public Seed
{
public:
	void initialize(int w, int h, std::string data);
	cv::Mat getStep();
private:
	std::bitset<9> b;
	std::bitset<9> s;
};
