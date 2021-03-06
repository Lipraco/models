#ifndef EM_SQDIST_H
#define EM_SQDIST_H

#include <stdint.h>
#include <vector>

#include "em_circular.h"

class EMSqdist : public EMCircular
{
	public:
		EMSqdist();
		EMSqdist(int cluster_count_);

		void train();
		void add_time(uint32_t time, double value);

		void save(FILE* file, bool lossy = false);
		void load(FILE* file);
		void exportToArray(double* array, int maxLen, int& pos);
		void importFromArray(double* array, int len, int& pos);

		void print();

		double get_density_at_d(double phase) const;

	private:
		void expectation();
		double maximisation();

		class Cluster {
			public:
				Cluster();
				Cluster(double xx_, double yy_, double weight_);
				double xx;
				double yy;
				double weight;

				void print();
				void save(FILE* file, bool lossy = false);
				void load(FILE* file);
				void exportToArray(double* array, int maxLen, int& pos);
				void importFromArray(double* array, int len, int& pos);

				double density_at(double phase) const;
		};

		std::vector<Cluster> clusters;
		double timestamps_weight;

		void U(double zr, double zi, double fr, double fi, double w, double& vr, double& vi);
		void mle(int c, double s, double& xhat, double& yhat);
};

#endif // EM_SQDIST_H
