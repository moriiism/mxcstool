#include "arg_plot_lc_hd1d.h"

// public

void ArgValPlotLcHd1d::Init(int argc, char* argv[])
{
    progname_ = "plot_lc_hd1d";
    
    option long_options[] = {
        {"debug",      required_argument, NULL, 'd'},
        {"help",       required_argument, NULL, 'h'},
        {"verbose",    required_argument, NULL, 'v'},
        {"format",     required_argument, NULL, 0},        
        {0, 0, 0, 0}
    };

    // long option default
    format_ = "x,xe,y,ye";
    SetOption(argc, argv, long_options);

    if(0 < g_flag_verbose){
        printf("ArgVal::Init: # of arg = %d\n", argc - optind);
    }
    int narg = 3;
    if (argc - optind != narg){
        printf("# of arguments must be %d.\n", narg);
        Usage(stdout);
    }
    int iarg = optind;
    file_in_        = argv[iarg];       iarg++;
    file_out_       = argv[iarg];       iarg++;
    plot_conf_file_ = argv[iarg];       iarg++;
}

void ArgValPlotLcHd1d::Print(FILE* fp) const
{
    fprintf(fp, "%s: g_flag_debug    : %d\n", __func__, g_flag_debug);
    fprintf(fp, "%s: g_flag_help     : %d\n", __func__, g_flag_help);
    fprintf(fp, "%s: g_flag_verbose  : %d\n", __func__, g_flag_verbose);
    
    fprintf(fp, "%s: file_in_        : %s\n", __func__, file_in_.c_str());
    fprintf(fp, "%s: file_out_       : %s\n", __func__, file_out_.c_str());
    fprintf(fp, "%s: plot_conf_file_ : %s\n", __func__, plot_conf_file_.c_str());

    fprintf(fp, "%s: format_         : %s\n", __func__, format_.c_str());
}

// private

void ArgValPlotLcHd1d::Null()
{
    progname_       = "";
    file_in_        = "";
    file_out_       = "";
    plot_conf_file_ = "";
    format_         = "";
}

void ArgValPlotLcHd1d::SetOption(int argc, char* argv[], option* long_options)
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
            if("format" == long_options[option_index].name){
                format_  = optarg;
            }
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

void ArgValPlotLcHd1d::Usage(FILE* fp) const
{
    fprintf(fp,
            "usage: %s [--help (0)] [--verbose (0)] [--debug (0)] "
            "[--format (x,xe,y,ye)] "
            "file_in  file_out  plot_conf_file",
            progname_.c_str());
    abort();
}
