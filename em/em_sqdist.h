#ifndef EM_SQDIST_H
#define EM_SQDIST_H

#include <stdint.h>
#include <vector>

class EMSqdist
{
	public:
		EMSqdist(int cluster_count_);

		void train();
		void add_time(uint32_t time);

		void save(FILE* file, bool lossy = false);
		void load(FILE* file);
		void exportToArray(double* array, int maxLen, int& pos);
		void importFromArray(double* array, int len, int& pos);

		void print();

		double get_density_at(uint32_t time);

	private:
		void expectation();
		double maximisation();

		int cluster_count;
		static double time_to_phase(uint32_t time);

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

		class Timestamp {
			public:
				Timestamp(uint32_t time, int cluster_count);
				double phase;
				std::vector<double> alpha;
		};

		std::vector<Cluster> clusters;
		std::vector<Timestamp> timestamps;
};

#endif // EM_SQDIST_H