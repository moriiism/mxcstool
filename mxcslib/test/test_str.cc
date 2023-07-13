#include "mxcs_str.h"

// global variable 
int g_flag_debug = 0;
int g_flag_help = 0;
int g_flag_verbose = 0;

int main(int argc, char* argv[])
{
    int status_prog = kRetNormal;

//    int IsSpace(string buf);
    {
        string buf = " ";
        printf("%d\n", MxcsStr::IsSpace(buf));
    }
    
    {
        string buf = "";
        printf("%d\n", MxcsStr::IsSpace(buf));
    }
    
    {
        string buf = "9";
        printf("%d\n", MxcsStr::IsSpace(buf));
    }

    {
        string buf = "\t";
        printf("%d\n", MxcsStr::IsSpace(buf));
    }

    {
        string buf = "\n";
        printf("%d\n", MxcsStr::IsSpace(buf));
    }
    
//    int Chomp(char* const buf);
    {
        printf("--- Chomp(char* const buf)\n");
        char buf[7] = "12345\n";
        printf("%s\nA\n", buf);
        MxcsStr::Chomp(buf);
        printf("%s\nA\n", buf);
        MxcsStr::Chomp(buf);
        printf("%s\nA\n", buf);
        printf("=== \n");
    }
    
//    int Chomp(string* const buf_ptr);
    {
        printf("--- Chomp(string* const buf_ptr)\n");
        string buf = "12345\n";
        printf("%s\nA\n", buf.c_str());
        MxcsStr::Chomp(&buf);
        printf("%s\nA\n", buf.c_str());
        MxcsStr::Chomp(&buf);
        printf("%s\nA\n", buf.c_str());
        printf("=== \n");
    }

//    void RmStSpace(string* const buf_ptr);
    {
        printf("--- RmStSpace(string* const buf_ptr)\n");
        string buf = " kk ";
        printf("|%s|\n", buf.c_str());
        MxcsStr::RmStSpace(&buf);
        printf("|%s|\n", buf.c_str());
        printf("=== \n");
    }
    
//    void RmEdSpace(string* const buf_ptr);
    {
        printf("--- RmEdSpace(string* const buf_ptr)\n");
        string buf = " ssss";
        printf("|%s|\n", buf.c_str());
        MxcsStr::RmEdSpace(&buf);
        printf("|%s|\n", buf.c_str());
        printf("=== \n");
    }
    
//    void RmStEdSpace(string* const buf_ptr);
    {
        printf("--- RmStEdSpace(string* const buf_ptr)\n");
        string buf = "  ";
        printf("|%s|\n", buf.c_str());
        MxcsStr::RmStEdSpace(&buf);
        printf("|%s|\n", buf.c_str());
        printf("=== \n");
    }
    
//    void GenSplit(string str_in, int* nsplit_ptr, string** split_arr_ptr,
//                  const char* const delim = " \t");
//    void DelSplit(string* split_arr);
    {
        printf("--- GenSplit()\n");
        string str_in = "aaa bbbb cccccc    ddd eeee\n";
        int nsplit = 0;
        string* split_arr = NULL;
        MxcsStr::GenSplit(str_in, &nsplit, &split_arr, " ");
        printf("nsplit = %d\n", nsplit);
        for(int isplit = 0; isplit < nsplit; isplit ++){
            printf("%s|\n", split_arr[isplit].c_str());
        }
        printf("=== \n");
    }

    {
        printf("--- GenSplit()\n");
        string str_in = "aaa bbbb cccccc    ddd eeee\n";
        int nsplit = 0;
        string* split_arr = NULL;
        MxcsStr::GenSplit(str_in, &nsplit, &split_arr, " \n");
        printf("nsplit = %d\n", nsplit);
        for(int isplit = 0; isplit < nsplit; isplit ++){
            printf("%s|\n", split_arr[isplit].c_str());
        }
        printf("=== \n");
    }

    {
        printf("--- GenSplit()\n");
        string str_in = "aaa, bbbb ,cccccc  ,  ddd,eeee\n";
        int nsplit = 0;
        string* split_arr = NULL;
        MxcsStr::GenSplit(str_in, &nsplit, &split_arr, " \n");
        printf("nsplit = %d\n", nsplit);
        for(int isplit = 0; isplit < nsplit; isplit ++){
            printf("%s|\n", split_arr[isplit].c_str());
        }
        printf("=== \n");
    }

    {
        printf("--- GenSplit()\n");
        string str_in = "aaa, bbbb ,cccccc  ,  ddd,eeee\n";
        int nsplit = 0;
        string* split_arr = NULL;
        MxcsStr::GenSplit(str_in, &nsplit, &split_arr, ", \n");
        printf("nsplit = %d\n", nsplit);
        for(int isplit = 0; isplit < nsplit; isplit ++){
            printf("%s|\n", split_arr[isplit].c_str());
        }
        printf("=== \n");
    }

    
//    int GetNcolumn(string str_in, const char* const delim = " \t");
    {
        printf("--- GetNcolumn()\n");
        string str_in = "aaa, bbbb ,cccccc  ,  ddd,eeee\n";
        int nsplit = MxcsStr::GetNcolumn(str_in, ", \n");
        printf("nsplit = %d\n", nsplit);
        printf("=== \n");
    }


    
    return status_prog;
}
