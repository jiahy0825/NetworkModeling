#include <iomanip>
#include <sstream>
#include <random>
#include <chrono>

using namespace std;

int main(){
	unsigned seed = 1222;
  
	default_random_engine generator(seed);
	// ��һ������Ϊ��˹�ֲ���ƽ��ֵ���ڶ�������Ϊ��׼��
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
		fflush(fp);						//����д����������Ҫ��������������������ݽ�������д��ʱ
	}
	
	fclose(fp);
	return 0;
}