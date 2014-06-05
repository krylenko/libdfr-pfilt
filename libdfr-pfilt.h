/********************* particle filter library ***************************/
/*                          daniel ford                                  */
/*                            may 2011                                   */
/*************************************************************************/

#ifndef LIBDFR_PFILT_H
#define LIBDFR_PFILT_H

#include <iostream>
#include "libdfr-matrix.h"
#include "libdfr-rv.h"

using namespace std;

class ParticleFilter
{
	public:
	
		Matrix particles;
		Matrix weights;

		ParticleFilter(const int& samples, const double& PDFscale=4.);
		
		void updateWeights();
		void resample();
		
	private:
	
		int N;			// number of samples
		double scale;	// scaling constant to expand uniform to envelop target dist
		
};
				
#endif