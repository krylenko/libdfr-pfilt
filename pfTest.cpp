#include "libdfr-pfilt.h"
#include "../libdfr-rv/libdfr-rv.h"
#include "../libdfr-matrix/libdfr-matrix.h"

int main()
{

	int samples = 1000;
	int bins = 15;

	ParticleFilter tracker(samples, 8);
	
	// note - repeated resampling on a static target distribution
	// will cause the particles to converge on the expectation
    for(int t=0;t<15;t++)
	{
		tracker.updateWeights();
		tracker.resample();
	}
	
	// generate Pr histogram and print to file
	Matrix hist = rvBin(tracker.particles, -4, 4, bins);

	// plot desired density for comparison
	Matrix targets(hist);
	
	// calc desired function
	double tSum=0;
	for(int j=0;j<targets.rows();j++)
	{
		targets[j][1] = p_x(targets[j][0]);
		tSum += targets[j][1];
	}
	// normalize to make probabilities
	for(int j=0;j<targets.rows();j++)
		targets[j][1] /= tSum;
	
	// print sampled and desired densities to file	
	hist.printFile("dist-p.dat");
	targets.printFile("real.dat");
	hist.print();
	
}
