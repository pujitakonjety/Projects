#include"stdafx.h"
#include"Declarations.h"
unsigned int floor(unsigned int val){
	unsigned int temp = val / (BLOCK_SIZE);
	if (temp * BLOCK_SIZE == val)
		return temp;
	return temp + 1;
}
void copyToFs(char *source_file, char*dest_file,struct metadataTable *head){
	FILE *fq = fopen(dest_file, "rb+");
	fseek(fq, 0, SEEK_END);
	unsigned int file_size = ftell(fq);
	rewind(fq);
	unsigned int number_of_blocks = floor(file_size);
	unsigned int i;
	for ( i = FILE_BLOCKS; i < TOTAL_BLOCKS; i++){
		if (head->blocks[i] == '0')
			break;
	}
	if (i >= TOTAL_BLOCKS){
		printf("NO Space to Copy");
		return;
	}
	printf("initial file size %d\n", file_size);
	unsigned int start_ind = i;
	strcpy(head->files[head->no_of_files].filename, source_file);
	head->files[head->no_of_files].start_block = start_ind;
	head->files[head->no_of_files].blocks_count = number_of_blocks;
	head->files[head->no_of_files].length = file_size;
	head->no_of_files++;
	char *buffer = (char*)malloc(BLOCK_SIZE*sizeof(char));
	int size_read;
	if (file_size<BLOCK_SIZE)
		size_read = fread(buffer, 1, file_size, fq);
	else
		size_read = fread(buffer, 1, BLOCK_SIZE, fq);
	buffer[size_read] = '\0';
	head->blocks[start_ind] = '1';

	printf("blocks ids %d\n", start_ind);
	if (number_of_blocks == 1){
		buffer[size_read] = '\0';
		writeToDisk((void*)buffer, start_ind);
		fclose(fq);
		return;
	}
	unsigned int *buf = (unsigned int*)malloc(sizeof(unsigned int)*(BLOCK_SIZE / 4));
	unsigned int ind = 0;
	unsigned int size = BLOCK_SIZE;
	for (; i < TOTAL_BLOCKS&&number_of_blocks>0; i++){
		if (head->blocks[i] == '0'){
			buffer[size_read] = '\0';
			writeToDisk((void*)buffer, i);
			file_size -= BLOCK_SIZE;
			buf[ind++] = i;
			number_of_blocks--;
			head->blocks[i] = '1';
			if (number_of_blocks == 0)
				break;
			if (file_size < BLOCK_SIZE){
				size_read = fread(buffer, 1, file_size, fq);
				size = size + file_size;
			}
				
			else{
				size_read = fread(buffer, 1, BLOCK_SIZE, fq);
				size = size + BLOCK_SIZE;
			}
			buffer[size_read] = '\0';
		}
	}
	printf("found file size%d\n", size);
	buffer[size_read] = '\0';
	writeToDisk((void*)buf, start_ind);
	fclose(fq);

}

void copyFromFs(char *sourcefile, char *destfile, struct metadataTable *head){
	unsigned int i = 0;
	FILE *fq = fopen(destfile, "wb");
	if (fq == NULL){
		printf("file Not existed\n");
			return;
	}
	for (; i < head->no_of_files; i++){
		if (strcmp(head->files[i].filename, sourcefile) == 0){
			break;
		}
	}
	if (i >= head->no_of_files){
		printf("file not found");
		return;
	}
	unsigned int start_ind = head->files[i].start_block,blocks_count = head->files[i].blocks_count,file_size = head->files[i].length;
	char *buffer = (char*)malloc(sizeof(char)*BLOCK_SIZE);
	if (blocks_count == 1){
		readFromDisk((void*)buffer, start_ind);
		fwrite(buffer, 1, head->files[i].length, fq);
		fclose(fq);
		return;
	}

	unsigned int *buf = (unsigned int*)malloc(sizeof(unsigned int)*(BLOCK_SIZE / 4));
	readFromDisk((void*)buf, start_ind);
	printf("block id %d\n", start_ind);
	for (int i = 0; i < blocks_count; i++)
		printf("ind %d\n", buf[i]);
	for (unsigned int k = 0; k < blocks_count; k++){
		
		readFromDisk((void*)buffer, buf[k]);
		if (file_size<BLOCK_SIZE)
			fwrite(buffer, 1, file_size, fq);
		else
			fwrite(buffer, 1, BLOCK_SIZE, fq);
		file_size -= BLOCK_SIZE;
	}
	fclose(fq);


}
void update_meta_data(struct metadataTable *head, int file_id){
	if (head->no_of_files == 1){
		head->no_of_files--;
		return;
	}
	strcpy(head->files[file_id].filename, head->files[(head->no_of_files) - 1].filename);
	head->files[file_id].blocks_count = head->files[(head)->no_of_files - 1].blocks_count;
	head->files[file_id].length = head->files[(head)->no_of_files - 1].length;
	head->files[file_id].start_block = head->files[(head)->no_of_files - 1].start_block;
	head->no_of_files--;
	printf("hdfjkgdk\n");
}

void DeleteFile(struct metadataTable *head,char *name){
	unsigned int i;
	for (i = 0; i < head->no_of_files; i++){
		if (strcmp(head->files[i].filename, name) == 0)
			break;
	}
	unsigned int file_id = i;
	if (i == head->no_of_files){
		printf("File Not Existed\n");
		return;
	}
	unsigned int start_blockind = head->files[i].start_block;
	if (head->files[i].blocks_count == 1){
		head->blocks[start_blockind] = '0';
		update_meta_data(head, file_id);
		return;
	}
	unsigned int totalblocks = head->files[i].blocks_count;
	unsigned int *buff = (unsigned int*)malloc(sizeof(unsigned int)*(BLOCK_SIZE / 4));
	readFromDisk(buff, start_blockind);
	for (unsigned int i = 0; totalblocks--; i++){
		head->blocks[buff[i]] = '0';
	}
	update_meta_data(head, file_id);
	printf("file deleted sucessfully but meta data not updated");

}

void MetaDataInfo(struct metadataTable *head){
	printf("Total Number of files in Disk %d\n", head->no_of_files);
	printf("Details of Files Stored in Disk\n");
	for (int i = 0; i < head->no_of_files; i++){
		printf("File name %s\n", head->files[i].filename);
		printf("File size %d\n", head->files[i].length);
		printf("File size in blocks %d\n", head->files[i].blocks_count);
		int *buffer = (int *)malloc(sizeof(int)*BLOCK_SIZE);
		readFromDisk(buffer, head->files[i].start_block);
		int count = head->files[i].blocks_count;
		if (count == 1){
			printf("Block 0 is stored at %d index in Disk\n",head->files[i].start_block);
			continue;
		}
		for (int j = 0;count--; j++){
			printf("Block %d is stored at %d index in Disk\n", j, buffer[j]);
		}

	}

}
