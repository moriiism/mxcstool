#include "arg_gti_andor2.h"

// public

void ArgValAndOr2::Init(int argc, char* argv[])
{
    progname_ = "gti_andor2";

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
    int narg = 6;
    if (argc - optind != narg){
        printf("# of arguments must be %d.\n", narg);
        Usage(stdout);
    }
    int iarg = optind;
    andor_         = argv[iarg];       iarg++; // "and" or "or"
    gti1_          = argv[iarg];       iarg++;
    gti2_          = argv[iarg];       iarg++;
    outdir_        = argv[iarg];       iarg++;
    outfile_head_  = argv[iarg];       iarg++;
    offset_tag_    = argv[iarg];       iarg++;
}

void ArgValAndOr2::Print(FILE* fp) const
{
    fprintf(fp, "%s: g_flag_debug   : %d\n", __func__, g_flag_debug);
    fprintf(fp, "%s: g_flag_help    : %d\n", __func__, g_flag_help);
    fprintf(fp, "%s: g_flag_verbose : %d\n", __func__, g_flag_verbose);

    fprintf(fp, "%s: progname_     : %s\n", __func__, progname_.c_str());
    fprintf(fp, "%s: andor_        : %s\n", __func__, andor_.c_str());
    fprintf(fp, "%s: gti1_         : %s\n", __func__, gti1_.c_str());
    fprintf(fp, "%s: gti2_         : %s\n", __func__, gti2_.c_str());
    fprintf(fp, "%s: outdir_       : %s\n", __func__, outdir_.c_str());
    fprintf(fp, "%s: outfile_head_ : %s\n", __func__, outfile_head_.c_str());
    fprintf(fp, "%s: offset_tag_   : %s\n", __func__, offset_tag_.c_str());
}

// private

void ArgValAndOr2::Null()
{
    progname_      = "";
    andor_         = "";
    gti1_          = "";
    gti2_          = "";
    outdir_        = "";
    outfile_head_  = "";
    offset_tag_    = "";
}


void ArgValAndOr2::SetOption(int argc, char* argv[], option* long_options)
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

void ArgValAndOr2::Usage(FILE* fp) const
{
    fprintf(fp,
            "usage: %s [--help (0)] [--verbose (0)] [--debug (0)] "
            "andor  gti1  gti2  "
            "outdir  outfile_head  offset_tag\n",
            progname_.c_str());
    abort();
}
