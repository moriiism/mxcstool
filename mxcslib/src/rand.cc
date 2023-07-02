#include "mxcs_rand.h"

void MxcsRand::Init(int seed)
{
    if(0 == seed){
        srand((unsigned)time(NULL));
        // init_genrand64(rand());
        seed_random(rand());
    } else {
        // init_genrand64(seed);
        seed_random(seed);
    }
}

double MxcsRand::Uniform( void )
{
    //double val = genrand64_real1();
    double val = get_random();
    return val;
}

double MxcsRand::Normal(double mu, double sigma)
{
    double z=sqrt( -2.0*log(Uniform()) ) * sin( 2.0*M_PI*Uniform() );
    double val = mu + sigma*z;
    return val;
}

