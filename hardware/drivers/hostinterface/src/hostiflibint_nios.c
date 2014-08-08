/**
********************************************************************************
\file   hostiflibint_nios.c

\brief  Host Interface Library - Driver Implementation for Nios II

The file contains the high level driver for the host interface library for
Nios II targets.

\ingroup module_hostiflib
*******************************************************************************/

/*------------------------------------------------------------------------------
Copyright (c) 2014, Bernecker+Rainer Industrie-Elektronik Ges.m.b.H. (B&R)
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:
    * Redistributions of source code must retain the above copyright
      notice, this list of conditions and the following disclaimer.
    * Redistributions in binary form must reproduce the above copyright
      notice, this list of conditions and the following disclaimer in the
      documentation and/or other materials provided with the distribution.
    * Neither the name of the copyright holders nor the
      names of its contributors may be used to endorse or promote products
      derived from this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL COPYRIGHT HOLDERS BE LIABLE FOR ANY
DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
------------------------------------------------------------------------------*/

/**
********************************************************************************
\defgroup   module_hostiflib    Host Interface Library
\ingroup    libraries

The host interface library provides a software interface for using the host
interface IP-Core. It provides several features like queues and linear memory
modules.
*******************************************************************************/

//------------------------------------------------------------------------------
// includes
//------------------------------------------------------------------------------
#include "hostiflib.h"
#include "hostiflib_target.h"
#include "hostiflibint.h"

#include <sys/alt_irq.h>

//============================================================================//
//            G L O B A L   D E F I N I T I O N S                             //
//============================================================================//

//------------------------------------------------------------------------------
// const defines
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// module global vars
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// global function prototypes
//------------------------------------------------------------------------------

//============================================================================//
//            P R I V A T E   D E F I N I T I O N S                           //
//============================================================================//

//------------------------------------------------------------------------------
// const defines
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// local types
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// local vars
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// local function prototypes
//------------------------------------------------------------------------------

//============================================================================//
//            P U B L I C   F U N C T I O N S                                 //
//============================================================================//

//------------------------------------------------------------------------------
/**
\brief  Register interrupt service routine

This function registers the interrupt service routine in the host processor
interrupt services.

\param  pfnIrqCb_p              The interrupt service routine callback
\param  pArg_p                  Argument pointer provided to the callback

\return The function returns a tHostifReturn error code.
\retval kHostifSuccessful       The interrupt service routine was registered
                                successfully.

\ingroup module_hostiflib
*/
//------------------------------------------------------------------------------
tHostifReturn hostif_sysIrqRegHandler(tHostifIrqCb pfnIrqCb_p, void* pArg_p)
{
    int ret;

    ret = alt_ic_isr_register(HOSTIF_IRQ_IC_ID, HOSTIF_IRQ, pfnIrqCb_p, pArg_p, NULL);

    if (ret == 0)
        return kHostifSuccessful;
    else
        return kHostifNoResource;
}

//------------------------------------------------------------------------------
/**
\brief  Enable interrupt for host interface driver

This function enables the interrupt for the host interface driver instance.

\param  fEnable_p   Determines if the interrupt must be enabled (TRUE) or
                    disabled (FALSE)

\return The function returns a tHostifReturn error code.
\retval kHostifSuccessful       Interrupt enable/disable failed

\ingroup module_hostiflib
*/
//------------------------------------------------------------------------------
tHostifReturn hostif_sysIrqEnable(BOOL fEnable_p)
{
    int ret;

    if (fEnable_p)
    {
        ret = alt_ic_irq_enable(HOSTIF_IRQ_IC_ID, HOSTIF_IRQ);
    }
    else
    {
        ret = alt_ic_irq_disable(HOSTIF_IRQ_IC_ID, HOSTIF_IRQ);
    }

    if (ret == 0)
        return kHostifSuccessful;
    else
        return kHostifNoResource;
}
