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
 * Functionals for domain initialization -- header file.
 */
#ifndef DATA_INITIALIZER_FUNCTIONAL_3D_H
#define DATA_INITIALIZER_FUNCTIONAL_3D_H

#include "core/globalDefs.h"
#include "atomicBlock/dataProcessingFunctional3D.h"
#include "core/dynamics.h"

namespace plb {

/* *************** PART I ******************************************** */
/* *************** Initialization of the block-lattice *************** */
/* ******************************************************************* */

template<typename T, template<class U> class Descriptor>
struct OneCellFunctional3D {
    virtual ~OneCellFunctional3D();
    virtual OneCellFunctional3D<T,Descriptor>* clone() const =0;
    virtual void execute(Cell<T,Descriptor>& cell) const =0;
    virtual BlockDomain::DomainT appliesTo() const;
    virtual void getTypeOfModification(std::vector<modif::ModifT>& modified) const;
    virtual void setscale(int dxScale, int dtScale);
};

template<typename T, template<class U> class Descriptor>
struct OneCellIndexedFunctional3D {
    virtual ~OneCellIndexedFunctional3D();
    virtual OneCellIndexedFunctional3D<T,Descriptor>* clone() const =0;
    virtual void execute(plint iX, plint iY, plint iZ, Cell<T,Descriptor>& cell) const =0;
    virtual BlockDomain::DomainT appliesTo() const;
    virtual void getTypeOfModification(std::vector<modif::ModifT>& modified) const;
    virtual void setscale(int dxScale, int dtScale);
};

struct DomainFunctional3D {
    virtual ~DomainFunctional3D() { }
    virtual bool operator() (plint iX, plint iY, plint iZ) const =0;
    virtual DomainFunctional3D* clone() const =0;
};

template<typename T, template<class U> class Descriptor>
class GenericLatticeFunctional3D : public BoxProcessingFunctional3D_L<T,Descriptor>
{
public:
    GenericLatticeFunctional3D(OneCellFunctional3D<T,Descriptor>* f_);
    GenericLatticeFunctional3D(GenericLatticeFunctional3D<T,Descriptor> const& rhs);
    virtual ~GenericLatticeFunctional3D();
    GenericLatticeFunctional3D<T,Descriptor>& operator=(GenericLatticeFunctional3D<T,Descriptor> const& rhs);
    virtual void process(Box3D domain, BlockLattice3D<T,Descriptor>& lattice);
    virtual GenericLatticeFunctional3D<T,Descriptor>* clone() const;
    virtual void getTypeOfModification(std::vector<modif::ModifT>& modified) const;
    virtual BlockDomain::DomainT appliesTo() const;
    virtual void setscale(int dxScale, int dtScale);
private:
    OneCellFunctional3D<T,Descriptor>* f;
};

template<typename T, template<class U> class Descriptor>
class GenericIndexedLatticeFunctional3D : public BoxProcessingFunctional3D_L<T,Descriptor>
{
public:
    GenericIndexedLatticeFunctional3D(OneCellIndexedFunctional3D<T,Descriptor>* f_);
    GenericIndexedLatticeFunctional3D(GenericIndexedLatticeFunctional3D<T,Descriptor> const& rhs);
    virtual ~GenericIndexedLatticeFunctional3D();
    GenericIndexedLatticeFunctional3D<T,Descriptor>& operator=(GenericIndexedLatticeFunctional3D<T,Descriptor> const& rhs);
    virtual void process(Box3D domain, BlockLattice3D<T,Descriptor>& lattice);
    virtual GenericIndexedLatticeFunctional3D<T,Descriptor>* clone() const;
    virtual void getTypeOfModification(std::vector<modif::ModifT>& modified) const;
    virtual BlockDomain::DomainT appliesTo() const;
    virtual void setscale(int dxScale, int dtScale);
private:
    OneCellIndexedFunctional3D<T,Descriptor>* f;
};


/* *************** Class InstantiateDynamicsFunctional3D ************* */

template<typename T, template<typename U> class Descriptor>
class InstantiateDynamicsFunctional3D : public BoxProcessingFunctional3D_L<T,Descriptor> {
public:
    InstantiateDynamicsFunctional3D(Dynamics<T,Descriptor>* dynamics_);
    InstantiateDynamicsFunctional3D(InstantiateDynamicsFunctional3D<T,Descriptor> const& rhs);
    InstantiateDynamicsFunctional3D<T,Descriptor>& operator= (
            InstantiateDynamicsFunctional3D<T,Descriptor> const& rhs );
    virtual ~InstantiateDynamicsFunctional3D();
    virtual void process(Box3D domain, BlockLattice3D<T,Descriptor>& lattice);
    virtual BlockDomain::DomainT appliesTo() const;
    virtual void getTypeOfModification(std::vector<modif::ModifT>& modified) const;
    virtual InstantiateDynamicsFunctional3D<T,Descriptor>* clone() const ;
private:
    Dynamics<T,Descriptor>* dynamics;
};

/* ************* Class InstantiateComplexDomainDynamicsFunctional3D ** */

template<typename T, template<typename U> class Descriptor>
class InstantiateComplexDomainDynamicsFunctional3D
    : public BoxProcessingFunctional3D_L<T,Descriptor>
{
public:
    InstantiateComplexDomainDynamicsFunctional3D( Dynamics<T,Descriptor>* dynamics_,
                                                  DomainFunctional3D* domain_ );
    InstantiateComplexDomainDynamicsFunctional3D (
            InstantiateComplexDomainDynamicsFunctional3D<T,Descriptor> const& rhs );
    InstantiateComplexDomainDynamicsFunctional3D<T,Descriptor>& operator= (
            InstantiateComplexDomainDynamicsFunctional3D<T,Descriptor> const& rhs );
    virtual ~InstantiateComplexDomainDynamicsFunctional3D();
    virtual void process(Box3D boundingBox, BlockLattice3D<T,Descriptor>& lattice);
    virtual BlockDomain::DomainT appliesTo() const;
    virtual void getTypeOfModification(std::vector<modif::ModifT>& modified) const;
    virtual InstantiateComplexDomainDynamicsFunctional3D<T,Descriptor>* clone() const;
private:
    Dynamics<T,Descriptor>* dynamics;
    DomainFunctional3D* domain;
};


/* ************* Class InstantiateDotDynamicsFunctional3D ******************* */

template<typename T, template<typename U> class Descriptor>
class InstantiateDotDynamicsFunctional3D : public DotProcessingFunctional3D_L<T,Descriptor> {
public:
    InstantiateDotDynamicsFunctional3D(Dynamics<T,Descriptor>* dynamics_);
    InstantiateDotDynamicsFunctional3D(InstantiateDotDynamicsFunctional3D<T,Descriptor> const& rhs);
    InstantiateDotDynamicsFunctional3D<T,Descriptor>& operator= (
            InstantiateDotDynamicsFunctional3D<T,Descriptor> const& rhs );
    virtual ~InstantiateDotDynamicsFunctional3D();
    virtual void process(DotList3D const& dotList, BlockLattice3D<T,Descriptor>& lattice);
    virtual BlockDomain::DomainT appliesTo() const;
    virtual void getTypeOfModification(std::vector<modif::ModifT>& modified) const;
    virtual InstantiateDotDynamicsFunctional3D<T,Descriptor>* clone() const;
private:
    Dynamics<T,Descriptor>* dynamics;
};


/* ************* Class DynamicsFromMaskFunctional3D ************************ */

/// Assign dynamics to nodes specified by a boolean mask.
template<typename T, template<typename U> class Descriptor>
class DynamicsFromMaskFunctional3D : public BoxProcessingFunctional3D_LS<T,Descriptor,bool> {
public:
    DynamicsFromMaskFunctional3D(Dynamics<T,Descriptor>* dynamics_, bool whichFlag_);
    DynamicsFromMaskFunctional3D(DynamicsFromMaskFunctional3D<T,Descriptor> const& rhs);
    DynamicsFromMaskFunctional3D<T,Descriptor>& operator= (
            DynamicsFromMaskFunctional3D<T,Descriptor> const& rhs );
    virtual ~DynamicsFromMaskFunctional3D();
    virtual void process (
            Box3D domain, BlockLattice3D<T,Descriptor>& lattice,
                          ScalarField3D<bool>& mask );
    virtual BlockDomain::DomainT appliesTo() const;
    virtual void getTypeOfModification(std::vector<modif::ModifT>& modified) const;
    virtual DynamicsFromMaskFunctional3D<T,Descriptor>* clone() const;
private:
    Dynamics<T,Descriptor>* dynamics;
    bool whichFlag;
};


/* ************* Class DynamicsFromIntMaskFunctional3D ************************ */

/// Assign dynamics to nodes specified by a boolean mask.
template<typename T, template<typename U> class Descriptor>
class DynamicsFromIntMaskFunctional3D : public BoxProcessingFunctional3D_LS<T,Descriptor,int> {
public:
    DynamicsFromIntMaskFunctional3D(Dynamics<T,Descriptor>* dynamics_, int whichFlag_);
    DynamicsFromIntMaskFunctional3D(DynamicsFromIntMaskFunctional3D<T,Descriptor> const& rhs);
    DynamicsFromIntMaskFunctional3D<T,Descriptor>& operator= (
            DynamicsFromIntMaskFunctional3D<T,Descriptor> const& rhs );
    virtual ~DynamicsFromIntMaskFunctional3D();
    virtual void process (
            Box3D domain, BlockLattice3D<T,Descriptor>& lattice,
                          ScalarField3D<int>& mask );
    virtual BlockDomain::DomainT appliesTo() const;
    virtual void getTypeOfModification(std::vector<modif::ModifT>& modified) const;
    virtual DynamicsFromIntMaskFunctional3D<T,Descriptor>* clone() const;
private:
    Dynamics<T,Descriptor>* dynamics;
    int whichFlag;
};

/* *************** Class RecomposeFromOrderZeroVariablesFunctional3D ******************* */

template<typename T, template<typename U> class Descriptor>
class RecomposeFromOrderZeroVariablesFunctional3D : public BoxProcessingFunctional3D
{
public:
    virtual void processGenericBlocks(Box3D domain,
                                      std::vector<AtomicBlock3D*> atomicBlocks);
    virtual RecomposeFromOrderZeroVariablesFunctional3D<T,Descriptor>* clone() const;
    virtual BlockDomain::DomainT appliesTo() const;
    virtual void getTypeOfModification(std::vector<modif::ModifT>& modified) const;
};

/* *************** Class RecomposeFromFlowVariablesFunctional3D ******************* */

template<typename T, template<typename U> class Descriptor>
class RecomposeFromFlowVariablesFunctional3D : public BoxProcessingFunctional3D
{
public:
    virtual void processGenericBlocks(Box3D domain,
                                      std::vector<AtomicBlock3D*> atomicBlocks);
    virtual RecomposeFromFlowVariablesFunctional3D<T,Descriptor>* clone() const;
    virtual BlockDomain::DomainT appliesTo() const;
    virtual void getTypeOfModification(std::vector<modif::ModifT>& modified) const;
};


/* ************* Class AssignOmegaFunctional3D ******************* */

template<typename T, template<typename U> class Descriptor>
class AssignOmegaFunctional3D : public BoxProcessingFunctional3D_L<T,Descriptor>
{
public:
    AssignOmegaFunctional3D(T omega);
    virtual void process(Box3D domain, BlockLattice3D<T,Descriptor>& lattice);
    virtual AssignOmegaFunctional3D<T,Descriptor>* clone() const;
    virtual BlockDomain::DomainT appliesTo() const;
    virtual void getTypeOfModification(std::vector<modif::ModifT>& modified) const;
private:
    T omega;
};

/* ************* Class AssignScalarFieldOmegaFunctional3D ******************* */

template<typename T, template<typename U> class Descriptor>
class AssignScalarFieldOmegaFunctional3D : public BoxProcessingFunctional3D_LS<T,Descriptor,T>
{
public:
    AssignScalarFieldOmegaFunctional3D();
    virtual void process(Box3D domain, BlockLattice3D<T,Descriptor>& lattice, ScalarField3D<T> &omega);
    virtual AssignScalarFieldOmegaFunctional3D<T,Descriptor>* clone() const;
    virtual BlockDomain::DomainT appliesTo() const;
    virtual void getTypeOfModification(std::vector<modif::ModifT>& modified) const;
};

/* ************* Class SetConstBoundaryVelocityFunctional3D ******************* */

template<typename T, template<typename U> class Descriptor>
class SetConstBoundaryVelocityFunctional3D : public BoxProcessingFunctional3D_L<T,Descriptor>
{
public:
    SetConstBoundaryVelocityFunctional3D(Array<T,Descriptor<T>::d> velocity);
    virtual void process(Box3D domain, BlockLattice3D<T,Descriptor>& lattice);
    virtual SetConstBoundaryVelocityFunctional3D<T,Descriptor>* clone() const;
    virtual BlockDomain::DomainT appliesTo() const;
    virtual void getTypeOfModification(std::vector<modif::ModifT>& modified) const;
private:
    Array<T,Descriptor<T>::d> u;
};


/* ************* Class SetCustomBoundaryVelocityFunctional3D ******************* */

template<typename T, template<typename U> class Descriptor, class VelocityFunction>
class SetCustomBoundaryVelocityFunctional3D : public OneCellIndexedFunctional3D<T,Descriptor>
{
public:
    SetCustomBoundaryVelocityFunctional3D(VelocityFunction f_);
    virtual SetCustomBoundaryVelocityFunctional3D<T,Descriptor,VelocityFunction>* clone() const;
    virtual void execute(plint iX, plint iY, plint iZ, Cell<T,Descriptor>& cell) const;
    virtual void setscale(int dxScale, int dtScale);
private:
    VelocityFunction f;
    T velocityScale;
};


/* ************* Class SetConstBoundaryDensityFunctional3D ******************* */

template<typename T, template<typename U> class Descriptor>
class SetConstBoundaryDensityFunctional3D : public BoxProcessingFunctional3D_L<T,Descriptor>
{
public:
    SetConstBoundaryDensityFunctional3D(T rho_);
    virtual void process(Box3D domain, BlockLattice3D<T,Descriptor>& lattice);
    virtual SetConstBoundaryDensityFunctional3D<T,Descriptor>* clone() const;
    virtual BlockDomain::DomainT appliesTo() const;
    virtual void getTypeOfModification(std::vector<modif::ModifT>& modified) const;
private:
    T rho;
};


/* ************* Class SetCustomBoundaryDensityFunctional3D ******************* */

template<typename T, template<typename U> class Descriptor, class DensityFunction>
class SetCustomBoundaryDensityFunctional3D : public OneCellIndexedFunctional3D<T,Descriptor>
{
public:
    SetCustomBoundaryDensityFunctional3D(DensityFunction f_);
    virtual void execute(plint iX, plint iY, plint iZ, Cell<T,Descriptor>& cell) const;
    virtual SetCustomBoundaryDensityFunctional3D<T,Descriptor,DensityFunction>* clone() const;
private:
    DensityFunction f;
};


/* ************* Class IniConstEquilibriumFunctional3D ******************* */

template<typename T, template<typename U> class Descriptor>
class IniConstEquilibriumFunctional3D : public BoxProcessingFunctional3D_L<T,Descriptor>
{
public:
    IniConstEquilibriumFunctional3D(T density_, Array<T,Descriptor<T>::d> velocity, T temperature);
    virtual void process(Box3D domain, BlockLattice3D<T,Descriptor>& lattice);
    virtual IniConstEquilibriumFunctional3D<T,Descriptor>* clone() const;
    virtual BlockDomain::DomainT appliesTo() const;
    virtual void getTypeOfModification(std::vector<modif::ModifT>& modified) const;
private:
    T rhoBar;
    Array<T,Descriptor<T>::d> j;
    T jSqr;
    T thetaBar;
};

/* ************* Class IniConstEquilibriumOnDomainFunctional3D ******************* */

template<typename T, template<typename U> class Descriptor, class DomainFunctional>
class IniConstEquilibriumOnDomainFunctional3D : public BoxProcessingFunctional3D_L<T,Descriptor>
{
public:
    IniConstEquilibriumOnDomainFunctional3D (
            T density_, Array<T,Descriptor<T>::d> velocity, T temperature,
            DomainFunctional const& domain_ );
    virtual void process(Box3D domain, BlockLattice3D<T,Descriptor>& lattice);
    virtual IniConstEquilibriumOnDomainFunctional3D<T,Descriptor,DomainFunctional>* clone() const;
    virtual void getTypeOfModification(std::vector<modif::ModifT>& modified) const;
private:
    T rhoBar;
    Array<T,Descriptor<T>::d> j;
    T jSqr;
    T thetaBar;
    DomainFunctional domain;
};


/* ************* Class IniCustomEquilibriumFunctional3D ******************* */

template<typename T, template<typename U> class Descriptor, class RhoUFunction>
class IniCustomEquilibriumFunctional3D : public OneCellIndexedFunctional3D<T,Descriptor>
{
public:
    IniCustomEquilibriumFunctional3D(RhoUFunction f_);
    virtual void execute(plint iX, plint iY, plint iZ, Cell<T,Descriptor>& cell) const;
    virtual IniCustomEquilibriumFunctional3D<T,Descriptor,RhoUFunction>* clone() const;
    virtual void setscale(int dxScale, int dtScale);
private:
    RhoUFunction f;
    T velocityScale;
};

/* ************* Class IniCustomThermalEquilibriumFunctional3D ******************* */

template<typename T, template<typename U> class Descriptor, class RhoVelTempFunction>
class IniCustomThermalEquilibriumFunctional3D : public OneCellIndexedFunctional3D<T,Descriptor>
{
public:
    IniCustomThermalEquilibriumFunctional3D(RhoVelTempFunction f_);
    virtual void execute(plint iX, plint iY, plint iZ, Cell<T,Descriptor>& cell) const;
    virtual IniCustomThermalEquilibriumFunctional3D<T,Descriptor,RhoVelTempFunction>* clone() const;
    virtual void setscale(int dxScale, int dtScale);
private:
    RhoVelTempFunction f;
    T velocityScale;
};


/* ************* Class StripeOffDensityOffsetFunctional3D ******************* */

template<typename T, template<typename U> class Descriptor>
class StripeOffDensityOffsetFunctional3D : public BoxProcessingFunctional3D_L<T,Descriptor>
{
public:
    StripeOffDensityOffsetFunctional3D(T deltaRho_);
    virtual void process(Box3D domain, BlockLattice3D<T,Descriptor>& lattice);
    virtual StripeOffDensityOffsetFunctional3D<T,Descriptor>* clone() const;
    virtual BlockDomain::DomainT appliesTo() const;
    virtual void getTypeOfModification(std::vector<modif::ModifT>& modified) const;
private:
    T deltaRho;
};

/* ************* Class InstantiateCompositeDynamicsFunctional3D ******************* */

template<typename T, template<typename U> class Descriptor>
class InstantiateCompositeDynamicsFunctional3D : public BoxProcessingFunctional3D_L<T,Descriptor> {
public:
    InstantiateCompositeDynamicsFunctional3D(CompositeDynamics<T,Descriptor>* compositeDynamics_);
    InstantiateCompositeDynamicsFunctional3D(InstantiateCompositeDynamicsFunctional3D<T,Descriptor> const& rhs);
    InstantiateCompositeDynamicsFunctional3D<T,Descriptor>& operator= (
            InstantiateCompositeDynamicsFunctional3D<T,Descriptor> const& rhs );
    virtual ~InstantiateCompositeDynamicsFunctional3D();
    virtual void process(Box3D domain, BlockLattice3D<T,Descriptor>& lattice);
    virtual void getTypeOfModification(std::vector<modif::ModifT>& modified) const;
    virtual InstantiateCompositeDynamicsFunctional3D<T,Descriptor>* clone() const;
private:
    CompositeDynamics<T,Descriptor>* compositeDynamics;
};


/* ************* Class SetExternalScalarFunctional3D ******************* */

template<typename T, template<typename U> class Descriptor>
class SetExternalScalarFunctional3D : public BoxProcessingFunctional3D_L<T,Descriptor> {
public:
    SetExternalScalarFunctional3D(int whichScalar_, T externalScalar_);
    virtual void process(Box3D domain, BlockLattice3D<T,Descriptor>& lattice);
    virtual BlockDomain::DomainT appliesTo() const;
    virtual void getTypeOfModification(std::vector<modif::ModifT>& modified) const;
    virtual SetExternalScalarFunctional3D<T,Descriptor>* clone() const;
private:
    int whichScalar;
    T externalScalar;
};

/* ************* Class SetExternalScalarFromScalarFieldFunctional3D ******************* */

template<typename T, template<typename U> class Descriptor>
class SetExternalScalarFromScalarFieldFunctional3D : public BoxProcessingFunctional3D_LS<T,Descriptor,T> {
public:
    SetExternalScalarFromScalarFieldFunctional3D(int whichScalar_);
    virtual void process(Box3D domain, BlockLattice3D<T,Descriptor>& lattice, ScalarField3D<T> &scalar);
    virtual BlockDomain::DomainT appliesTo() const;
    virtual void getTypeOfModification(std::vector<modif::ModifT>& modified) const;
    virtual SetExternalScalarFromScalarFieldFunctional3D<T,Descriptor>* clone() const;
private:
    int whichScalar;
};


/* ************* Class MaskedSetExternalScalarFunctional3D ******************* */

template<typename T, template<typename U> class Descriptor>
class MaskedSetExternalScalarFunctional3D : public BoxProcessingFunctional3D_LS<T,Descriptor,int> {
public:
    MaskedSetExternalScalarFunctional3D(int flag_, int whichScalar_, T externalScalar_);
    virtual void process(Box3D domain, BlockLattice3D<T,Descriptor>& lattice, ScalarField3D<int>& mask);
    virtual BlockDomain::DomainT appliesTo() const;
    virtual void getTypeOfModification(std::vector<modif::ModifT>& modified) const;
    virtual MaskedSetExternalScalarFunctional3D<T,Descriptor>* clone() const;
private:
    int flag;
    int whichScalar;
    T externalScalar;
};


/* ************* Class SetGenericExternalScalarFunctional3D ******************* */

template<typename T, template<typename U> class Descriptor, class Functional>
class SetGenericExternalScalarFunctional3D : public BoxProcessingFunctional3D_L<T,Descriptor> {
public:
    SetGenericExternalScalarFunctional3D(int whichScalar_, Functional const& functional_);
    virtual void process(Box3D domain, BlockLattice3D<T,Descriptor>& lattice);
    virtual void getTypeOfModification(std::vector<modif::ModifT>& modified) const;
    virtual SetGenericExternalScalarFunctional3D<T,Descriptor,Functional>* clone() const;
private:
    int whichScalar;
    Functional functional;
};


/* ************* Class MaskedSetGenericExternalScalarFunctional3D ******************* */

template<typename T, template<typename U> class Descriptor, class Functional>
class MaskedSetGenericExternalScalarFunctional3D : public BoxProcessingFunctional3D_LS<T,Descriptor,int> {
public:
    MaskedSetGenericExternalScalarFunctional3D(int flag_, int whichScalar_, Functional const& functional_);
    virtual void process(Box3D domain, BlockLattice3D<T,Descriptor>& lattice, ScalarField3D<int>& mask);
    virtual void getTypeOfModification(std::vector<modif::ModifT>& modified) const;
    virtual MaskedSetGenericExternalScalarFunctional3D<T,Descriptor,Functional>* clone() const;
private:
    int flag;
    int whichScalar;
    Functional functional;
};

/* ************* Class AddToExternalScalarFunctional3D ******************* */

template<typename T, template<typename U> class Descriptor>
class AddToExternalScalarFunctional3D : public BoxProcessingFunctional3D_L<T,Descriptor> {
public:
    AddToExternalScalarFunctional3D(int whichScalar_, T externalScalar_);
    virtual void process(Box3D domain, BlockLattice3D<T,Descriptor>& lattice);
    virtual BlockDomain::DomainT appliesTo() const;
    virtual void getTypeOfModification(std::vector<modif::ModifT>& modified) const;
    virtual AddToExternalScalarFunctional3D<T,Descriptor>* clone() const;
private:
    int whichScalar;
    T externalScalar;
};


/* ************* Class SetExternalVectorFunctional3D ******************* */

template<typename T, template<typename U> class Descriptor>
class SetExternalVectorFunctional3D : public BoxProcessingFunctional3D_L<T,Descriptor> {
public:
    SetExternalVectorFunctional3D (
            int vectorStartsAt_, Array<T,Descriptor<T>::d> & externalVector_ );
    virtual void process(Box3D domain, BlockLattice3D<T,Descriptor>& lattice);
    virtual BlockDomain::DomainT appliesTo() const;
    virtual void getTypeOfModification(std::vector<modif::ModifT>& modified) const;
    virtual SetExternalVectorFunctional3D<T,Descriptor>* clone() const;
private:
    int vectorStartsAt;
    Array<T,Descriptor<T>::d> externalVector;
};


/* ************* Class MaskedSetExternalVectorFunctional3D ******************* */

template<typename T, template<typename U> class Descriptor>
class MaskedSetExternalVectorFunctional3D : public BoxProcessingFunctional3D_LS<T,Descriptor,int> {
public:
    MaskedSetExternalVectorFunctional3D (
            int flag_, int vectorStartsAt_, Array<T,Descriptor<T>::d> & externalVector_ );
    virtual void process(Box3D domain, BlockLattice3D<T,Descriptor>& lattice, ScalarField3D<int>& mask);
    virtual void getTypeOfModification(std::vector<modif::ModifT>& modified) const;
    virtual MaskedSetExternalVectorFunctional3D<T,Descriptor>* clone() const;
private:
    int flag;
    int vectorStartsAt;
    Array<T,Descriptor<T>::d> externalVector;
};


/* ************* Class SetGenericExternalVectorFunctional3D ******************* */

template<typename T, template<typename U> class Descriptor, class Functional>
class SetGenericExternalVectorFunctional3D : public BoxProcessingFunctional3D_L<T,Descriptor> {
public:
    SetGenericExternalVectorFunctional3D(int vectorBeginsAt_, Functional const& functional_);
    virtual void process(Box3D domain, BlockLattice3D<T,Descriptor>& lattice);
    virtual void getTypeOfModification(std::vector<modif::ModifT>& modified) const;
    virtual SetGenericExternalVectorFunctional3D<T,Descriptor,Functional>* clone() const;
private:
    int vectorBeginsAt;
    Functional functional;
};


/* ************* Class MaskedSetGenericExternalVectorFunctional3D ******************* */

template<typename T, template<typename U> class Descriptor, class Functional>
class MaskedSetGenericExternalVectorFunctional3D : public BoxProcessingFunctional3D_LS<T,Descriptor,int> {
public:
    MaskedSetGenericExternalVectorFunctional3D(int flag_, int vectorBeginsAt_, Functional const& functional_);
    virtual void process(Box3D domain, BlockLattice3D<T,Descriptor>& lattice, ScalarField3D<int>& mask);
    virtual void getTypeOfModification(std::vector<modif::ModifT>& modified) const;
    virtual MaskedSetGenericExternalVectorFunctional3D<T,Descriptor,Functional>* clone() const;
private:
    int flag;
    int vectorBeginsAt;
    Functional functional;
};


/* ************* Class SetExternalVectorFromTensorFieldFunctional3D ******************* */

template<typename T, template<typename U> class Descriptor, int nDim>
class SetExternalVectorFromTensorFieldFunctional3D : public BoxProcessingFunctional3D_LT<T,Descriptor, T, nDim> {
public:
    SetExternalVectorFromTensorFieldFunctional3D (
            int vectorStartsAt_ );
    virtual void process(Box3D domain, BlockLattice3D<T,Descriptor>& lattice, TensorField3D<T,nDim>& tensor);
    virtual BlockDomain::DomainT appliesTo() const;
    virtual void getTypeOfModification(std::vector<modif::ModifT>& modified) const;
    virtual SetExternalVectorFromTensorFieldFunctional3D<T,Descriptor,nDim>* clone() const;
private:
    int vectorStartsAt;
};


/* ************* Class InterpolatePopulationsFunctional3D ******************* */

template<typename T, template<typename U> class Descriptor>
class InterpolatePopulationsFunctional3D : public BoxProcessingFunctional3D_LL<T,Descriptor, T,Descriptor>
{
public:
    InterpolatePopulationsFunctional3D(plint minIter_, plint maxIter_);
    virtual void process( Box3D domain, BlockLattice3D<T,Descriptor>& lattice1,
                                        BlockLattice3D<T,Descriptor>& lattice2 );
    virtual BlockDomain::DomainT appliesTo() const;
    virtual void getTypeOfModification(std::vector<modif::ModifT>& modified) const;
    virtual InterpolatePopulationsFunctional3D<T,Descriptor>* clone() const;
private:
    plint minIter, maxIter;
};


/* *************** PART II ******************************************* */
/* *************** Initialization of scalar- and tensor-fields ******* */
/* ******************************************************************* */

template<typename T>
class IniConstScalarFunctional3D : public BoxProcessingFunctional3D_S<T>
{
public:
    IniConstScalarFunctional3D(T value_);
    virtual void process(Box3D domain, ScalarField3D<T>& field);
    virtual IniConstScalarFunctional3D<T>* clone() const;
    virtual BlockDomain::DomainT appliesTo() const;
    virtual void getTypeOfModification(std::vector<modif::ModifT>& modified) const;
private:
    T value;
};

template<typename T>
class MaskedIniConstScalarFunctional3D : public BoxProcessingFunctional3D_SS<T,int>
{
public:
    MaskedIniConstScalarFunctional3D(int flag_, T value_);
    virtual void process( Box3D domain,
                          ScalarField3D<T>& field, ScalarField3D<int>& mask);
    virtual MaskedIniConstScalarFunctional3D<T>* clone() const;
    virtual BlockDomain::DomainT appliesTo() const;
    virtual void getTypeOfModification(std::vector<modif::ModifT>& modified) const;
private:
    int flag;
    T value;
};

template<typename T, class Function>
class SetToScalarFunctionFunctional3D : public BoxProcessingFunctional3D_S<T>
{
public:
    SetToScalarFunctionFunctional3D(Function f_);
    virtual void process(Box3D domain, ScalarField3D<T>& field);
    virtual SetToScalarFunctionFunctional3D<T,Function>* clone() const;
    virtual BlockDomain::DomainT appliesTo() const;
    virtual void getTypeOfModification(std::vector<modif::ModifT>& modified) const;
private:
    Function f;
};

template<typename T, class Function> 
class AnalyticalSetRhoBarJFunctional3D : public BoxProcessingFunctional3D_N<T>
{
public:
    AnalyticalSetRhoBarJFunctional3D(Function const& function_);
    virtual void process(Box3D domain, NTensorField3D<T>& rhoBarJ);
    virtual AnalyticalSetRhoBarJFunctional3D<T, Function>* clone() const;
    virtual void getTypeOfModification(std::vector<modif::ModifT>& modified) const;
private:
    Function function;
};

template<typename T, int nDim>
class IniConstTensorFunctional3D : public BoxProcessingFunctional3D_T<T,nDim>
{
public:
    IniConstTensorFunctional3D(Array<T,nDim> const& value_);
    virtual void process(Box3D domain, TensorField3D<T,nDim>& field);
    virtual IniConstTensorFunctional3D<T,nDim>* clone() const;
    virtual BlockDomain::DomainT appliesTo() const;
    virtual void getTypeOfModification(std::vector<modif::ModifT>& modified) const;
private:
    Array<T,nDim> value;
};

template<typename T, int nDim>
class MaskedIniConstTensorFunctional3D : public BoxProcessingFunctional3D_ST<int,T,nDim>
{
public:
    MaskedIniConstTensorFunctional3D(int flag_, Array<T,nDim> const& value_);
    virtual void process( Box3D domain,
                          ScalarField3D<int>& mask, TensorField3D<T,nDim>& field );
    virtual MaskedIniConstTensorFunctional3D<T,nDim>* clone() const;
    virtual BlockDomain::DomainT appliesTo() const;
    virtual void getTypeOfModification(std::vector<modif::ModifT>& modified) const;
private:
    int flag;
    Array<T,nDim> value;
};

template<typename T, int nDim, class Function>
class SetToTensorFunctionFunctional3D : public BoxProcessingFunctional3D_T<T,nDim>
{
public:
    SetToTensorFunctionFunctional3D(Function f_);
    virtual void process(Box3D domain, TensorField3D<T,nDim>& field);
    virtual SetToTensorFunctionFunctional3D<T,nDim,Function>* clone() const;
    virtual BlockDomain::DomainT appliesTo() const;
    virtual void getTypeOfModification(std::vector<modif::ModifT>& modified) const;
private:
    Function f;
};


template<typename T>
class SetToCoordinateFunctional3D : public BoxProcessingFunctional3D_S<T>
{
public:
    SetToCoordinateFunctional3D(plint index_);
    virtual void process(Box3D domain, ScalarField3D<T>& field);
    virtual SetToCoordinateFunctional3D<T>* clone() const;
    virtual BlockDomain::DomainT appliesTo() const;
    virtual void getTypeOfModification(std::vector<modif::ModifT>& modified) const;
private:
    plint index;
};

template<typename T>
class SetToCoordinatesFunctional3D : public BoxProcessingFunctional3D_T<T,3>
{
public:
    SetToCoordinatesFunctional3D();
    virtual void process(Box3D domain, TensorField3D<T,3>& field);
    virtual SetToCoordinatesFunctional3D<T>* clone() const;
    virtual BlockDomain::DomainT appliesTo() const;
    virtual void getTypeOfModification(std::vector<modif::ModifT>& modified) const;
};

template<typename T, int nDim>
class SetTensorComponentFunctional3D : public BoxProcessingFunctional3D_ST<T,T,nDim>
{
public:
    SetTensorComponentFunctional3D(int whichDim_);
    virtual void process(Box3D domain, ScalarField3D<T>& scalarField,
                                       TensorField3D<T,nDim>& tensorField);
    virtual SetTensorComponentFunctional3D<T,nDim>* clone() const;
    virtual BlockDomain::DomainT appliesTo() const;
    virtual void getTypeOfModification(std::vector<modif::ModifT>& modified) const;
private:
    int whichDim;
};

}  // namespace plb

#endif  // DATA_INITIALIZER_FUNCTIONAL_3D_H

// Explicitly include generic algorithms which are never precompiled (not even in precompiled version)
#include "dataProcessors/dataInitializerGenerics3D.h"
