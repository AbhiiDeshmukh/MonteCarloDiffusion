#include <bits/stdc++.h>
#include <mkl.h>
#include "distribution.h"
using namespace std;

//vectorize this function based on instruction on the lab page
int diffusion(const int n_particles,
                const int n_steps,
                const float x_threshold,
                const float alpha,
                VSLStreamStatePtr rnStream) {
        int n_escaped=0;
/*#pragma omp simd
        for (int i = 0; i < n_particles; i++) {
                float x = 0.0f;
                for (int j = 0; j < n_steps; j++) {
                        float rn;

                        //Intel MKL function to generate random numbers
                        vsRngUniform(VSL_RNG_METHOD_UNIFORM_STD, rnStream, 1, &rn, -1.0, 1.0);

                        x += dist_func(alpha, rn);
                }
                if (x > x_threshold) n_escaped++;
        }
*/
        float x[n_particles];
        for (int i = 0; i < n_particles; i++)
                x[i]=0.0f;

        //float rn[n_particles];
        //vsRngUniform(VSL_RNG_METHOD_UNIFORM_STD, rnStream, n_particles, rn, -1.0, 1.0);
        for(int j=0;j<n_steps;j++){
                //float x[n_particles]={0.0f};
                float rn[n_particles];
                vsRngUniform(VSL_RNG_METHOD_UNIFORM_STD, rnStream, n_particles, rn, -1.0, 1.0);
                for(int i=0;i<n_particles;i++){
                        x[i] += dist_func(alpha, rn[i]);
                        //cout<<x[i]<<" ";
                }
                //if (x[j] > x_threshold) n_escaped++;
        }

        for(int i=0;i<n_particles;i++){
                if (x[i] > x_threshold) n_escaped++;
        }


        return n_escaped;
}
