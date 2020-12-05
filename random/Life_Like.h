
#include "Seed.h"
#include <bitset>

class Life_Like : public Seed
{
public:
	void initialize(int w, int h, std::string data);
	cv::Mat getStep();
private:
	bool b[9];
	bool s[9];
};
