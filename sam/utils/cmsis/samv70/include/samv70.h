/**
 * \file
 *
 * Copyright (c) 2015 - 2017 Atmel Corporation. All rights reserved.
 *
 * \asf_license_start
 *
 * \page License
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 *
 * 3. The name of Atmel may not be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * 4. This software may only be redistributed and used in connection with an
 *    Atmel microcontroller product.
 *
 * THIS SOFTWARE IS PROVIDED BY ATMEL "AS IS" AND ANY EXPRESS OR IMPLIED
 * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT ARE
 * EXPRESSLY AND SPECIFICALLY DISCLAIMED. IN NO EVENT SHALL ATMEL BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
 * STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
 * ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 * \asf_license_stop
 *
 */
/*
 * Support and FAQ: visit <a href="http://www.atmel.com/design-support/">Atmel Support</a>
 */
#ifndef _SAMV70_
#define _SAMV70_

#if defined (__SAMV70J19B__)
  #include "samv70j19b.h"
#elif defined (__SAMV70J20B__)
  #include "samv70j20b.h"
#elif defined (__SAMV70N19B__)
  #include "samv70n19b.h"
#elif defined (__SAMV70N20B__)
  #include "samv70n20b.h"
#elif defined (__SAMV70Q19B__)
  #include "samv70q19b.h"
#elif defined (__SAMV70Q20B__)
  #include "samv70q20b.h"
#elif defined (__SAMV70J19__)
#include "samv70j19.h"
#elif defined (__SAMV70J20__)
#include "samv70j20.h"
#elif defined (__SAMV70N19__)
#include "samv70n19.h"
#elif defined (__SAMV70N20__)
#include "samv70n20.h"
#elif defined (__SAMV70Q19__)
#include "samv70q19.h"
#elif defined (__SAMV70Q20__)
#include "samv70q20.h"
#else
  #error Library does not support the specified device.
#endif

#endif /* _SAMV70_ */
