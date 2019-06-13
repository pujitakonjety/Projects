#include"stdafx.h"
void writeOutput(FILE *fp, bool *numbers,int init){
	for (unsigned int i = 0; i < 1000000; i++){
		if (numbers[i])
			fprintf(fp, "%d\n", i+init);
		numbers[i] = 0;
	}
}
int main(int argc, _TCHAR* argv[]){
	
	bool numbers[1000000];

	FILE *fq = fopen("output.txt", "w");
	unsigned int val = 0, init = 0, final = 1000000;
	for (int i = 0; i < 10; i++){
		FILE *fp = fopen("OneMillion.txt", "r");
		while (fscanf(fp, "%u", &val) != EOF){
			unsigned int x = 1;
			if (val>=init&&val<final)
				numbers[val]= x;
		}
		fclose(fp);
		writeOutput(fq, numbers,init);
		init = final;
		final = final + 1000000;
	}
	//fclose(fp);
	fclose(fq);

}