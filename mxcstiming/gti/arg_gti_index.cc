#include "arg_gti_index.h"

// public

void ArgValGtiIndex::Init(int argc, char* argv[])
{
    progname_ = "gti_index";

    option long_options[] = {
        {"debug",      required_argument, NULL, 'd'},
        {"help",       required_argument, NULL, 'h'},
        {"verbose",    required_argument, NULL, 'v'},
        {0, 0, 0, 0}
    };

    // long option default
    SetOption(argc, argv, long_options);

    if(0 < g_flag_verbose){
        printf("ArgVal::Init: # of arg = %d\n", argc - optind);
    }
    int narg = 2;
    if (argc - optind != narg){
        printf("# of arguments must be %d.\n", narg);
        Usage(stdout);
    }
    int iarg = optind;
    gti_      = argv[iarg];        iarg++;
    time_     = atof(argv[iarg]);  iarg++;
}


void ArgValGtiIndex::Print(FILE* fp) const
{
    fprintf(fp, "%s: g_flag_debug   : %d\n", __func__, g_flag_debug);
    fprintf(fp, "%s: g_flag_help    : %d\n", __func__, g_flag_help);
    fprintf(fp, "%s: g_flag_verbose : %d\n", __func__, g_flag_verbose);
    
    fprintf(fp, "%s: gti_           : %s\n", __func__, gti_.c_str());
    fprintf(fp, "%s: time_          : %e\n", __func__, time_);
}

// private

void ArgValGtiIndex::Null()
{
    progname_ = "";
    gti_      = "";
    time_     = 0.0;
}
    
void ArgValGtiIndex::SetOption(int argc, char* argv[], option* long_options)
{
    if(0 < g_flag_verbose){
        MxcsPrintInfo("start...");
    }
    // option default
    g_flag_debug   = 0;
    g_flag_help    = 0;
    g_flag_verbose = 0;
    while (1) {
        int option_index = 0;
        int retopt = getopt_long(argc, argv, "dhv",
                                 long_options, &option_index);
        
        if(-1 == retopt)
            break;
        switch (retopt) {
        case 0:
            // long option
            break;
        case 'd':
            g_flag_debug = atoi(optarg);
            printf("%s: g_flag_debug = %d\n", __func__, g_flag_debug);
            break;
        case 'h':
            g_flag_help = atoi(optarg);
            printf("%s: g_flag_help = %d\n", __func__, g_flag_help);
            if(0 != g_flag_help){
                Usage(stdout);
            }                                
            break;
        case 'v':
            g_flag_verbose = atoi(optarg);
            printf("%s: g_flag_verbose = %d\n", __func__, g_flag_verbose);
            break;
        case '?':
            printf("%s: retopt (= %c) is invalid flag.\n",
                   __func__, retopt);
            Usage(stdout);
            break;

        default:
            printf("%s: error: getopt returned character code 0%o ??\n",
                   __func__, retopt);
            abort();
        }
    }
    if(0 < g_flag_verbose){
        MxcsPrintInfo("done.");
    }
}

void ArgValGtiIndex::Usage(FILE* fp) const
{
    fprintf(fp,
            "usage: %s [--help (0)] [--verbose (0)] [--debug (0)] "
            "gti  time \n",
            progname_.c_str());
    abort();
}

