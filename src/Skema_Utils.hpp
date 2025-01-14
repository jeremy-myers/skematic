#pragma once
#include <KokkosSparse.hpp>
#include <Kokkos_Core.hpp>
#include <cfloat>
#include <cstddef>
#include <cstdlib>

/* Typedefs */
using scalar_type = double;
using ordinal_type = int;
using size_type = std::size_t;
using layout_type = Kokkos::LayoutLeft;
using device_type = typename Kokkos::Device<
    Kokkos::DefaultExecutionSpace,
    typename Kokkos::DefaultExecutionSpace::memory_space>;
using execution_space = typename device_type::execution_space;
using memory_space = typename device_type::memory_space;
using matrix_type = typename Kokkos::View<scalar_type**, layout_type>;
using unmanaged_matrix_type =
    typename Kokkos::View<scalar_type**,
                          Kokkos::LayoutLeft,
                          Kokkos::HostSpace,
                          Kokkos::MemoryTraits<Kokkos::Unmanaged>>;
using crs_matrix_type = typename KokkosSparse::
    CrsMatrix<scalar_type, ordinal_type, device_type, void, size_type>;
using vector_type = typename Kokkos::View<scalar_type*, layout_type>;
using unmanaged_vector_type =
    typename Kokkos::View<scalar_type*,
                          Kokkos::LayoutLeft,
                          Kokkos::HostSpace,
                          Kokkos::MemoryTraits<Kokkos::Unmanaged>>;
using index_type = typename Kokkos::View<ordinal_type*, layout_type>;
using range_type = typename Kokkos::pair<size_type, size_type>;

/* Enums */
namespace Skema {

struct Matrix_Type {
  enum type { DENSE, SPARSE };
  static constexpr unsigned num_types = 2;
  static constexpr type types[] = {DENSE, SPARSE};
  static constexpr const char* names[] = {"dense", "sparse"};
  static constexpr type default_type = DENSE;
};

struct Solver_Method {
  enum type { ISVD, SKETCH, PRIMME };
  static constexpr unsigned num_types = 3;
  static constexpr type types[] = {ISVD, SKETCH, PRIMME};
  static constexpr const char* names[] = {"isvd", "sketch", "primme"};
  static constexpr type default_type = ISVD;
};
struct Decomposition_Type {
  enum type { EIG, EIGS, SVD, SVDS };
  static constexpr unsigned num_types = 4;
  static constexpr type types[] = {EIG, EIGS, SVD, SVDS};
  static constexpr const char* names[] = {"eig", "eigs", "svd", "svds"};
  static constexpr type default_type = SVDS;
};
struct Kernel_Map {
  enum type { NONE, GAUSSRBF };
  static constexpr unsigned num_types = 2;
  static constexpr type types[] = {NONE, GAUSSRBF};
  static constexpr const char* names[] = {"none", "gaussrbf"};
  static constexpr type default_type = NONE;
};
struct Sampler_Type {
  enum type { RESERVOIR };
  static constexpr unsigned num_types = 1;
  static constexpr type types[] = {RESERVOIR};
  static constexpr const char* names[] = {"reservoir"};
  static constexpr type default_type = RESERVOIR;
};
struct DimRedux_Map {
  enum type { GAUSS, SPARSE_SIGN };
  static constexpr unsigned num_types = 2;
  static constexpr type types[] = {GAUSS, SPARSE_SIGN};
  static constexpr const char* names[] = {"gauss", "sparse-sign"};
  static constexpr type default_type = GAUSS;
};

constexpr const Skema::Matrix_Type::type Skema::Matrix_Type::types[];
constexpr const char* Skema::Matrix_Type::names[];

constexpr const Skema::Solver_Method::type Skema::Solver_Method::types[];
constexpr const char* Skema::Solver_Method::names[];

constexpr const Skema::Decomposition_Type::type
    Skema::Decomposition_Type::types[];
constexpr const char* Skema::Decomposition_Type::names[];

constexpr const Skema::Sampler_Type::type Skema::Sampler_Type::types[];
constexpr const char* Skema::Sampler_Type::names[];

constexpr const Skema::Kernel_Map::type Skema::Kernel_Map::types[];
constexpr const char* Skema::Kernel_Map::names[];

constexpr const Skema::DimRedux_Map::type Skema::DimRedux_Map::types[];
constexpr const char* Skema::DimRedux_Map::names[];
}  // namespace Skema