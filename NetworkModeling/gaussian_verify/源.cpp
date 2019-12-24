#include <iomanip>
#include <sstream>
#include <random>
#include <chrono>

using namespace std;

int main(){
	unsigned seed = 1222;
  
	default_random_engine generator(seed);
	// 第一个参数为高斯分布的平均值，第二个参数为标准差
	std::normal_distribution<double> distribution(0.0, 0.4);

	vector<double> res;
	for (int i = 0; i < 100;i++){
		res.push_back(distribution(generator));
	}
	
	char strPath[] = "data.txt";

	FILE *fp = NULL;
	fopen_s(&fp, strPath, "w");
	if (NULL == fp)
	{
		return 0;
	}
	for (int i = 0;i < res.size();i++){
		fprintf(fp, "%lf\n", res[i]);
		fflush(fp);						//除读写缓冲区，需要立即把输出缓冲区的数据进行物理写入时
	}
	
	fclose(fp);
	return 0;
}