#ifndef H_FS_KERNEL_
#define H_FS_KERNEL_

int get_stat(char *filename, struct stat_st *stat);
int read_file(char *filename, unsigned char *buf);
int remove_file(char *filename);

#endif
