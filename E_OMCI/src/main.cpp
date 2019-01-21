#include <istream>
#include <string.h>
#include <common.hpp>
#include <me_c.hpp>
#include <omci_parser.hpp>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>



UI32_T get_uint_from_hex_string(char *string, UI8_T uint_bytes_count, void *uint_value)
{
	char temp_text[10]; // Up to UI32_T (4 bytes == 8 Hex bytes)

	memset(temp_text,0,sizeof(temp_text));
	switch (uint_bytes_count)
	{
	case 1:
		sscanf(string,"%2c",temp_text);
		*(UI8_T*)uint_value = (UI8_T)strtoul(temp_text, NULL, 16);
		break;
	case 2:
		sscanf(string,"%4c",temp_text);
		*(UI16_T*)uint_value = (UI16_T)strtoul(temp_text, NULL, 16);
		break;
	case 4:
		sscanf(string,"%8c",temp_text);
		*(UI32_T*)uint_value = (UI32_T)strtoul(temp_text, NULL, 16);
		break;
	default:
		break;
	}
	return (2 * uint_bytes_count);
}

char* get_text_line(FILE* input_fp)
{
    char *read_buf = 0;
    static UI32_T lineLen=0;
    static I32_T Len=0;
    OMCI_Parser omci_p;

    while ((Len = getline(&read_buf,(size_t *)&lineLen ,input_fp)) !=  -1)
    {
        UI8_T omci_raw[256]={0};
        UI8_T PC;
        int sizeofTest= strlen(read_buf)/2;

        printf("[%s]omci size is %d\r\n", __MY_FILE__, sizeofTest);

        char * OMCI_pkt_hex_string =read_buf;

        for(int i = 0; i < sizeofTest; i++)
        {
            OMCI_pkt_hex_string += get_uint_from_hex_string(OMCI_pkt_hex_string,1,(void*)&PC);
            printf("%02X", PC);
            omci_raw[i] = (UI8_T)PC;
        }
        printf("\r\n");
        omci_p.omci_pkt_parser(omci_raw);
        printf("\r\n");
    }    
    return read_buf;
}



void platform_arch_info()
{
    printf("UI32_T size is [%zu]\r\n", sizeof(UI32_T));
    printf("UI16_T size is [%zu]\r\n", sizeof(UI16_T));
    printf("UI8_T  size is [%zu]\r\n", sizeof(UI8_T));
    printf("BOOL_T size is [%zu]\r\n", sizeof(BOOL_T));
}

int main(int argc, char *argv[])
{
    //platform_arch_info();
    FILE *OMCI_cmds_fp;
    char OMCI_Cmds_filename[256];

    //OMCI_Parser omci_p;
    //return 1;

    if(argc == 2 && strlen(argv[1]) >  0)
    {
        printf("[%s]filename[%s]\r\n",__MY_FILE__, argv[1]);

        sprintf(OMCI_Cmds_filename,"%s",argv[1]);

        if ((OMCI_cmds_fp = fopen(OMCI_Cmds_filename, "r"))==NULL)
        {
            printf("[%s]Failed to open file: %s for reading..",__MY_FILE__,OMCI_Cmds_filename);
            return 0;
        }
        else
        {
            char *omci_TEST = get_text_line(OMCI_cmds_fp);
            free(omci_TEST);
            fclose(OMCI_cmds_fp);
        }
        return 1;
    }
    else
    {
        printf("[%s]Please provide RAW_DATA_FILE of OMCI !!!!! \r\n",__MY_FILE__);
        return 0;
    }
    return 1;
}
