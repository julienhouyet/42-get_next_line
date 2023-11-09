#include "get_next_line.h"
#include <stdio.h>

int main(void)
{
  int  	fd;
  char  *line;
  int  	count;
  int	test;

  count = 0;
  test = 0;
  fd = open("./files/43_with_nl", O_RDONLY);
  if (fd == -1)
  {
	printf("Error with file.");
	return (0);
  }
  while (1)
  {
	line = get_next_line(fd);
	if (line == NULL) 
		break;
	count++;
	printf("[%d]:%s\n", count, line);
	free(line);
	line = NULL;
	test++;
  }
  close(fd);
  system("leaks a.out");
  return (0);
}