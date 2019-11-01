#include <inttypes.h>
#include<sys/time.h>

struct timeval millis_st, millis_et;

uint64_t millis()
{

    if (millis_st.tv_sec ==0 && millis_st.tv_usec ==0)
    {
        gettimeofday(&millis_st,NULL);
    }

    gettimeofday(&millis_et,NULL);

    uint64_t elapsed = ((millis_et.tv_sec - millis_st.tv_sec) * 1000) + (millis_et.tv_usec - millis_st.tv_usec)/1000;
    return elapsed;
}
