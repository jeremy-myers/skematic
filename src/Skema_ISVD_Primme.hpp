#pragma once
#ifndef SKEMA_ISVD_PRIMME_HPP
#define SKEMA_ISVD_PRIMME_HPP
#include <cstddef>
#include "Skema_AlgParams.hpp"
#include "Skema_EIGSVD.hpp"
#include "Skema_Sampler.hpp"
#include "Skema_Utils.hpp"

namespace Skema {
template <typename MatrixType>
class ISVD_SVDS : public PRIMME_SVDS<MatrixType> {
 public:
  ISVD_SVDS(const AlgParams& algParams_)
      : PRIMME_SVDS<MatrixType>(algParams_), algParams(algParams_) {
    using primme_svds = PRIMME_SVDS<MatrixType>;

    // History & logging
    std::string outputfilename = algParams.outputfilename;
    outputfile = fopen(outputfilename.c_str(), "w");
    if (outputfile == NULL)
      perror("PRIMME output file failed to open: ");
  };

  ~ISVD_SVDS() {
    if (outputfile != NULL)
      fclose(outputfile);
  };

  void compute(const MatrixType&,
               const size_type,
               const size_type,
               const size_type,
               matrix_type&,
               vector_type&,
               matrix_type&) override;

  void compute(const MatrixType&,
               const size_type,
               const size_type,
               const size_type,
               matrix_type&,
               vector_type&,
               matrix_type&,
               const ReservoirSampler<MatrixType>&);

  void set_u0(const MatrixType&,
              const size_type,
              const size_type,
              const size_type,
              matrix_type&,
              vector_type&,
              matrix_type&);

 protected:
  AlgParams algParams;
  FILE* outputfile;
};

template class ISVD_SVDS<matrix_type>;
template class ISVD_SVDS<crs_matrix_type>;

extern "C" {
void isvd_sparse_convTestFun(double* sval,
                             void* leftsvec,
                             void* rightvec,
                             double* rnorm,
                             int* method,
                             int* isconv,
                             primme_svds_params* primme_svds,
                             int* ierr);

void isvd_sparse_monitorFun(void* basisSvals,
                            int* basisSize,
                            int* basisFlags,
                            int* iblock,
                            int* blockSize,
                            void* basisNorms,
                            int* numConverged,
                            void* lockedSvals,
                            int* numLocked,
                            int* lockedFlags,
                            void* lockedNorms,
                            int* inner_its,
                            void* LSRes,
                            const char* msg,
                            double* time,
                            primme_event* event,
                            int* stage,
                            primme_svds_params* primme_svds,
                            int* ierr);
}
}  // namespace Skema

#endif /* SKEMA_ISVD_PRIMME_HPP */