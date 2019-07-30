#include"stdafx.h"
#include"declarations.h"
unsigned int floor(int val){
	unsigned int temp = (val*1.0) / (BLOCK_SIZE);
	if (temp * BLOCK_SIZE == val)
		return temp;
	return temp + 1;
}
int isEqual(char *inp1, char *inp2){
	int i;
	for (i = 0; inp1[i] != '\0'&&inp1[i] != ' '; i++){
		if (inp1[i] != inp2[i])
			return 0;
	}
	if (inp2[i] == '\0')
		return 1;
	return 0;

}
struct metadata* createEntry(char *file_name){
	struct metadata *newentry = (struct metadata*)malloc(sizeof(struct metadata));
	strcpy(newentry->filename, file_name);
	return newentry;


}
char *get_filename(char *options){
	int i = 0, ptr = 0;
	while (options[i] != '\0'&&options[i] != ' ')
		i++;
	char *file_name = (char*)malloc(20 * sizeof(char));
	i++;
	while (options[i] != '\0')
		file_name[ptr++] = options[i++];
	file_name[ptr] = '\0';
	return file_name;

}
