/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     | Website:  https://openfoam.org
    \\  /    A nd           | Copyright (C) 2011-2018 OpenFOAM Foundation
     \\/     M anipulation  |
-------------------------------------------------------------------------------
License
    This file is part of OpenFOAM.

    OpenFOAM is free software: you can redistribute it and/or modify it
    under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    OpenFOAM is distributed in the hope that it will be useful, but WITHOUT
    ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
    FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
    for more details.

    You should have received a copy of the GNU General Public License
    along with OpenFOAM.  If not, see <http://www.gnu.org/licenses/>.

Class
    Foam::EPUSLimiter

Description
    Class with limiter function which returns the limiter for the
    EPUS differencing scheme based on r obtained from the LimiterFunc
    class.

    Used in conjunction with the template class LimitedScheme.

SourceFiles
    EPUS.C

\*---------------------------------------------------------------------------*/

#ifndef EPUS_H
#define EPUS_H

#include "vector.H"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace Foam
{

/*---------------------------------------------------------------------------*\
                           Class EPUSLimiter Declaration
\*---------------------------------------------------------------------------*/

template<class LimiterFunc>
class EPUSLimiter
:
    public LimiterFunc
{

public:

    EPUSLimiter(Istream&)
    {}

    scalar limiter
    (
        const scalar cdWeight,
        const scalar faceFlux,
        const typename LimiterFunc::phiType& phiP,
        const typename LimiterFunc::phiType& phiN,
        const typename LimiterFunc::gradPhiType& gradcP,
        const typename LimiterFunc::gradPhiType& gradcN,
        const vector& d
    ) const
    {
        scalar r = LimiterFunc::r
        (
            faceFlux, phiP, phiN, gradcP, gradcN, d
        );

        double lambda = 95.0;
        
        double epus = (
                        ( (0.5*(mag(r)+r)) * 
                            ((2.0*lambda - 32.0)*r*r*r*r + (160.0 - 4.0*lambda)*r*r*r + 2*lambda*r*r)
                        )/
                        ( (1 + mag(r))*(1 + mag(r))*(1 + mag(r))*(1 + mag(r))*(1 + mag(r))*(1 + mag(r))*(1 + mag(r)) )
                    );
        
        return max(0.0, epus);
    }
};


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace Foam

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
