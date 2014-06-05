/********************* particle filter library ***************************/
/*                          daniel ford                                  */
/*                            may 2011                                   */
/*************************************************************************/

#include <iostream>
#include "../matrix/libdfr-matrix.h"
#include "libdfr-rv.h"
#include "libdfr-pfilt.h"

// constructor
ParticleFilter::ParticleFilter(const int& samples, const double& PDFscale):
	particles(1,samples), weights(1,samples), N(samples), scale(PDFscale)
{
	// seed random number generators
	rvSeed();
	
	// create initial uniform particle distribution
	// [-1,1] to handle all PDFs
	for(int i=0;i<N;i++)
		particles[0][i] = rvStdUniform(-1,1)*PDFscale;	
	
}

// update and normalize weights given target distribution or other weight update rule
void ParticleFilter::updateWeights()
{
	
	// sample from q(x) and calculate weights based on target distribution
	for(int i=0;i<N;i++)
		weights[0][i] = p_x(particles[0][i])/scale;	
		
	// normalize weights
	weights = weights/weights.sum();

}

// resample input array of particles w/ updated normalized weights
void ParticleFilter::resample()
{

	int k=0, m=0;
	
	Matrix wCDF(1,N);
	Matrix rand(1,N);
	Matrix x(1,N);
	
	// create random array for comparison 
	for(int i=0;i<N;i++)
		rand[0][i] = rvStdUniform(0,1);
	
	// create CDF of weights
	wCDF[0][0] = weights[0][0];
	for(int j=1;j<N;j++)
		wCDF[0][j] = wCDF[0][j-1] + weights[0][j];
	
	//make copies as many times as numbers occur in CDF
	for(k = 0; k < N; ++k)
	{
		m = 0;
		while(wCDF[0][m] < rand[0][k])
		{
			++m;
		}
		x[0][k] = particles[0][m];
	}
	
	// reset weights to uniform values
	double wUniform = 1./N;
	weights.fill(wUniform);
	
	// replace old particles with newly resampled ones
	particles = x;

}