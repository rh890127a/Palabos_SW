/* This file is part of the Palabos library.
 *
 * Copyright (C) 2011-2015 FlowKit Sarl
 * Route d'Oron 2
 * 1010 Lausanne, Switzerland
 * E-mail contact: contact@flowkit.com
 *
 * The most recent release of Palabos can be downloaded at 
 * <http://www.palabos.org/>
 *
 * The library Palabos is free software: you can redistribute it and/or
 * modify it under the terms of the GNU Affero General Public License as
 * published by the Free Software Foundation, either version 3 of the
 * License, or (at your option) any later version.
 *
 * The library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Affero General Public License for more details.
 *
 * You should have received a copy of the GNU Affero General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

/** \file
 * Parallel dynamics object -- template instantiation.
 */

#include "parallelism/mpiManager.h"
#include "parallelism/parallelDynamics.h"
#include "parallelism/parallelDynamics.hh"
#include "latticeBoltzmann/nearestNeighborLattices2D.h"
#include "latticeBoltzmann/nearestNeighborLattices2D.hh"
#include "latticeBoltzmann/nearestNeighborLattices3D.h"
#include "latticeBoltzmann/nearestNeighborLattices3D.hh"

namespace plb {

#ifdef PLB_MPI_PARALLEL

#ifdef COMPILE_2D
    template class ParallelDynamics<FLOAT_T, descriptors::DESCRIPTOR_2D>;
    template class ConstParallelDynamics<FLOAT_T, descriptors::DESCRIPTOR_2D>;
#endif  // COMPILE_2D

#ifdef COMPILE_3D
    template class ParallelDynamics<FLOAT_T, descriptors::DESCRIPTOR_3D>;
    template class ConstParallelDynamics<FLOAT_T, descriptors::DESCRIPTOR_3D>;
#endif  // COMPILE_3D

#endif  // PLB_MPI_PARALLEL

}
