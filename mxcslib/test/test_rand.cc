#include "mxcs_base.h"
#include "mxcs_rand.h"

// global variable 
int g_flag_debug = 0;
int g_flag_help = 0;
int g_flag_verbose = 0;

int main(int argc, char* argv[])
{
    int status_prog = kRetNormal;
    
    // double Uniform(void);
    {
        int ndat = 100;
        MxcsRand* mrand = new MxcsRand;
        mrand->Init(0);
        FILE* fp = fopen("/home/morii/temp/rand_unif_out.dat", "w");
        for(int idat = 0; idat < ndat; idat ++){
            double rand = mrand->Uniform();
            // printf("%e\n", rand);
            fprintf(fp, "%e\n", rand);
        }
        fclose(fp);
    }

    // double Normal(double mu, double sigma);
    {
        double mu = 10.0;
        double sigma = 2.0;
        int ndat = 100;
        MxcsRand* mrand = new MxcsRand;
        mrand->Init(2);
        FILE* fp = fopen("/home/morii/temp/rand_norm_out.dat", "w");
        for(int idat = 0; idat < ndat; idat ++){
            double rand = mrand->Normal(mu, sigma);
            fprintf(fp, "%e\n", rand);
        }
        fclose(fp);
    }

    // int Poisson(double mean);
    {
        double mean = 5.4;
        int ndat = 1000;
        MxcsRand* mrand = new MxcsRand;
        mrand->Init(2);
        FILE* fp = fopen("/home/morii/temp/rand_poisson_out.dat", "w");
        for(int idat = 0; idat < ndat; idat ++){
            double rand = mrand->Poisson(mean);
            fprintf(fp, "%e\n", rand);
        }
        fclose(fp);
    }
    
    return status_prog;
}
