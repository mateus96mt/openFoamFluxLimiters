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
    Foam::TOPUSLimiter

Description
    Class with limiter function which returns the limiter for the
    TOPUS differencing scheme based on r obtained from the LimiterFunc
    class.

    Used in conjunction with the template class LimitedScheme.

SourceFiles
    TOPUS.C

\*---------------------------------------------------------------------------*/

#ifndef TOPUS_H
#define TOPUS_H

#include "vector.H"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace Foam
{

/*---------------------------------------------------------------------------*\
                           Class TOPUSLimiter Declaration
\*---------------------------------------------------------------------------*/

template<class LimiterFunc>
class TOPUSLimiter
:
    public LimiterFunc
{

public:

    TOPUSLimiter(Istream&)
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
        const scalar r = max
        (
            LimiterFunc::r(faceFlux, phiP, phiN, gradcP, gradcN, d), 0
        );
        
        double alpha = 2.0;
        
        double topus = (
                        ( (0.5*(abs(r)+r)) * 
                            ((-0.5*alpha + 1.0)*r*r + (alpha + 4.0)*r + (-0.5*alpha +3.0) ) 
                        )/
                        ( (1 + abs(r))*(1 + abs(r))*(1 + abs(r)) )
                    );
        
        return max(topus, 0.0);
    }
};


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace Foam

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
