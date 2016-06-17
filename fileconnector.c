
/****************************************************************
 * filename: fileconnector.c
 * author  : bryan
 * date    : 2016-06-17 
 * function: connect diffrent file into one
 * **************************************************************/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>
#include <sys/stat.h>
#include <sys/types.h>

#define  bool short
#define  true  (short)1
#define  false (short)0
int main(int argc, char* argv[])
{
	int c = -1;//return value of getopt()
	int appendtime = 0;//number of motiple connect onefile
	FILE * srcfile = NULL;
	FILE * dstfile = NULL;
	int ch = EOF;
	bool  multipleonefile = false;

	while((c = getopt(argc, argv,"hn:")) != -1)
	{
		switch(c)
		{
			case 'h':
				printf("usage1:	fileconnector dstfile, srcfile1, srcfile2,...srcfilen\n");
				printf("usage2:	fileconnector dstfile, srcfile, -n num\n");
				printf("num is the times to append srcfile to dstfile.\n");
				return 2;
				break;
			case 'n':
				appendtime = atoi(optarg);
				if((appendtime <= 0)||(appendtime >10000))
				{
					printf("error: value of num should be in 0 to 10000\n");
					return 1;
				}
				if(argc > 5 )
				{
					printf("error: illegle parameter input! \n ");
					return 1;
				}
				multipleonefile = true;
				break;
		}
	}
/*
	printf("index = %d \n", optind);
	printf("arg count = %d \n", argc);
	printf("src file = %s \n", argv[optind]);
	printf("index = %d \n", optind);
	printf("arg count = %d \n", argc);
	printf("arg0 = %s \n", argv[0]);
*/
	
	//open dst  file
	dstfile = fopen(argv[optind++],"w");
	if(NULL == dstfile)
	{
		printf("error: destination file open failed! \n");
		return 1;
	}


	if(true == multipleonefile)
	{//append one file for multiple times
		srcfile = fopen(argv[optind], "r");
		if(NULL == srcfile)
		{
			printf("error: source file open failed! \n");
			return 1;
			
		}
		int i = 0;
		while(i<appendtime)
		{
			while((ch = fgetc(srcfile)) != EOF)
			{
				fputc(ch, dstfile);
			}

			fseek(srcfile, 0, SEEK_SET);
			i++;
			printf("dstfile has been appended for  %d times.\n", i);
		}
		fclose(srcfile);

	}
	else
	{//connect sevral file into one	

		while(optind < argc)
		{
			srcfile = fopen(argv[optind++], "r");
			if(NULL == srcfile)
			{
				printf("error: source file open failed! \n");
				fclose(dstfile);
				return 1;
			}
			
			//append srcfile to dstfile
			while((ch = fgetc(srcfile)) != EOF)
			{
				fputc(ch, dstfile);
			}

			fclose(srcfile);

		}
	}

	fclose(dstfile);
	printf("connect job completed! \n");
	return 0;


}
